#include "../weather_station_app_i.h"
#include <stdio.h>

typedef enum {
    WeatherLabPhaseInit = 0,
    WeatherLabPhaseRx,
    WeatherLabPhaseQuiet,
} WeatherLabPhase;

static WeatherLabPhase lab_phase = WeatherLabPhaseInit;
static uint32_t lab_ui_tick = 0U;
static uint32_t lab_led_tick = 0U;
static bool lab_led_on = false;

static void weather_lab_draw(WeatherStationApp* app) {
    if(!app || !app->widget) return;
    widget_reset(app->widget);
    char text[256];
    const char* phase = "PRZYGOTOWANIE...";
    if(lab_phase == WeatherLabPhaseRx) phase = "NASLUCH 5 s";
    else if(lab_phase == WeatherLabPhaseQuiet) phase = "CISZA 1 s";
    snprintf(
        text,
        sizeof(text),
        "\e#AUTO LAB\n\nCzujniki: %u/10\nTX: 0.0 C / 0 %%\n\n%s\nRunda: %lu\nTX OK: %u/%u\n\nBACK = koniec sesji",
        app->lab_sensor_count,
        phase,
        (unsigned long)app->lab_round,
        app->lab_last_tx_ok,
        app->lab_sensor_count);
    widget_add_text_scroll_element(app->widget, 0, 0, 128, 64, text);
}

static void weather_lab_rx_led(WeatherStationApp* app, uint32_t now) {
    if(!app || lab_phase != WeatherLabPhaseRx || (int32_t)(now - lab_led_tick) < 0) return;
    notification_message(
        app->notifications, lab_led_on ? &sequence_reset_rgb : &sequence_set_only_green_255);
    lab_led_on = !lab_led_on;
    lab_led_tick = now + furi_ms_to_ticks(500U);
}

void weather_station_scene_lab_run_on_enter(void* context) {
    WeatherStationApp* app = context;
    if(!app || !app->lab_unlocked || !weather_station_ensure_widget(app)) {
        if(app) scene_manager_previous_scene(app->scene_manager);
        return;
    }

    /* Fixed test values requested for AUTO LAB. The heavy RX/LAB objects are
       deliberately created only after the old PIN view has been released. */
    app->lab_target_temperature_tenths = 0;
    app->lab_target_humidity = 0;
    lab_phase = WeatherLabPhaseInit;
    lab_ui_tick = 0U;
    lab_led_tick = 0U;
    lab_led_on = false;
    app->lab_phase_started_tick = furi_get_tick();
    weather_lab_draw(app);
    view_dispatcher_switch_to_view(app->view_dispatcher, WeatherStationViewWidget);
    weather_station_release_inactive_gui_views(app, WeatherStationViewWidget);
}

bool weather_station_scene_lab_run_on_event(void* context, SceneManagerEvent event) {
    WeatherStationApp* app = context;
    if(!app) return false;
    if(event.type == SceneManagerEventTypeTick) {
        const uint32_t now = furi_get_tick();

        if(lab_phase == WeatherLabPhaseInit) {
            /* GUI cleanup uses ten 100-ms ticks. Wait slightly longer before
               allocating the RX core and FlipperFormat used by LAB. */
            if((now - app->lab_phase_started_tick) >= furi_ms_to_ticks(1300U)) {
                if(!weather_lab_prepare(app) || !weather_lab_start_rx(app)) {
                    furi_string_set(app->editor_result_text, "Brak pamieci / RX LAB");
                    weather_lab_release(app, true);
                    notification_message(app->notifications, &sequence_reset_rgb);
                    scene_manager_previous_scene(app->scene_manager);
                    return true;
                }
                lab_phase = WeatherLabPhaseRx;
                app->lab_phase_started_tick = furi_get_tick();
                lab_led_tick = 0U;
                lab_led_on = false;
            }
        } else if(lab_phase == WeatherLabPhaseRx) {
            weather_lab_rx_led(app, now);
            if((now - app->lab_phase_started_tick) >= furi_ms_to_ticks(5000U)) {
                notification_message(app->notifications, &sequence_reset_rgb);
                lab_led_on = false;
                if(app->lab_sensor_count > 0U) {
                    (void)weather_lab_send_burst(app);
                    lab_phase = WeatherLabPhaseQuiet;
                    app->lab_phase_started_tick = furi_get_tick();
                } else {
                    app->lab_phase_started_tick = now;
                }
            }
        } else if((now - app->lab_phase_started_tick) >= furi_ms_to_ticks(1000U)) {
            if(weather_lab_start_rx(app)) {
                lab_phase = WeatherLabPhaseRx;
                app->lab_phase_started_tick = furi_get_tick();
                lab_led_tick = 0U;
                lab_led_on = false;
            }
        }

        if((now - lab_ui_tick) >= furi_ms_to_ticks(500U)) {
            lab_ui_tick = now;
            weather_lab_draw(app);
        }
        return true;
    }
    return false;
}

void weather_station_scene_lab_run_on_exit(void* context) {
    WeatherStationApp* app = context;
    if(!app) return;
    notification_message(app->notifications, &sequence_reset_rgb);
    weather_lab_release(app, true);
    if(app->widget) widget_reset(app->widget);
}

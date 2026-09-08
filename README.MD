Program przechwytuje sygnały od stacji pogodowych, umożliwia ich edycję i wysłanie.
## 🎥 Film

[![Weather Editor - Flipper Zero](https://img.youtube.com/vi/APE-WFhoZ-o/hqdefault.jpg)](https://www.youtube.com/watch?v=APE-WFhoZ-o)


Funkcje
Odbiera sygnały z bezprzewodowych czujników pogodowych.
Automatycznie rozpoznaje 26 protokołów RX.
Obsługuje edycję i nadawanie dla 25 protokołów TX.
Prowadzi ciągłe skanowanie sygnałów pogodowych.
Wyświetla nazwę protokołu oraz ID czujnika.
Wyświetla temperaturę, wilgotność, kanał i stan baterii.
Obsługuje temperaturę w stopniach Celsjusza i Fahrenheita.
Pozwala ustawić temperaturę dodatnią lub ujemną.
Obsługuje rozszerzony zakres temperatury do ±999.
Pozwala edytować wilgotność w zakresie 0–900%.
Pozwala edytować kanał oraz stan baterii.
Obsługuje wewnętrzne radio Flippera i zewnętrzny CC1101.
Pozwala wybierać częstotliwość i modulację odbiornika.
Przechowuje historię 20 odebranych czujników.
Pozwala otworzyć szczegóły wybranego czujnika.
Zapisuje odebrane czujniki jako profile .ws.
Zachowuje oryginalne dane i przebieg RAW.
Zapisuje przebieg radiowy jako plik .sub.
Pozwala wczytywać wcześniej zapisane stacje i czujniki.
Pozwala edytować odebrany sygnał i wysłać nowe wartości.
Zawiera Symulację do tworzenia sygnału bez wcześniejszego odbioru.
W Symulacji można wybrać protokół, ID i pozostałe dane czujnika.
Obsługuje ręczne wysyłanie sygnału.
Obsługuje automatyczne cykliczne nadawanie Auto TX.
Pozwala ustawić odstęp Auto TX od 1 do 3600 sekund.
Testuje kolejno wszystkie 25 protokołów TX.
Zawiera ukryty tryb Weather AUTO LAB.
AUTO LAB przechwytuje do 10 czujników w jednej sesji.
AUTO LAB pozwala wybrać czujnik, zmienić jego wartości i wysłać sygnał.
Obsługuje wartości testowe, np. 0°C i 0% wilgotności.
Ma polski i angielski interfejs.
Może być kompilowany dla ARF i Momentum.
Protokoły stacji pogodowych
inFactory-TH
ThermoPRO-TX4
Nexus-TH
GT-WT02
GT-WT03
Acurite 5n1
Acurite 592TXR
Acurite-606TX
Acurite-609TXC
Acurite-986
LaCrosse_TX
TX141THBv2
Oregon-v1 — tylko RX
Oregon2
Oregon3
AmbientWeather
Auriol HG06061
TX8300
Wendox W6276
Auriol AHFL
Kedsum-TH/Conrad-S3318P
EMOS E601x
Vauno EN8822C
Solight TE44
BL999
Bresser-3CH

W naszej wersji jest więc 26 protokołów odbioru i 25 formatów edycji/TX — Oregon-v1 pozostaje protokołem tylko do odbioru

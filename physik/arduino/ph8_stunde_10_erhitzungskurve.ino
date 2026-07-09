// Ph8 Stunde 10: Automatisierte Temperaturaufzeichnung beim Erhitzen
// Sensor: wasserdichter Temperatursensor DS18B20 (1-Wire-Bus)
//
// Pinbelegung:
//   VCC (rot)    -> 5V
//   GND (schwarz) -> GND
//   Daten (gelb) -> Digitalpin 2
//   Zusaetzlich: Pull-up-Widerstand 4,7 kOhm zwischen Datenpin und 5V
//
// Benoetigte Bibliotheken (ueber den Bibliotheksverwalter der Arduino-IDE
// installieren):
//   "OneWire"
//   "DallasTemperature"
//
// Funktionsweise:
// Der Sensor misst alle 5 Sekunden die Temperatur in Grad Celsius und gibt
// sie zusammen mit der seit Programmstart verstrichenen Zeit aus. Aus diesen
// Wertepaaren entsteht die Erhitzungskurve mit den charakteristischen
// Plateaus beim Schmelzen (um 0 Grad Celsius) und beim Sieden (um 100 Grad
// Celsius).

#include <OneWire.h>
#include <DallasTemperature.h>

const int datenPin = 2;
const unsigned long messintervallMs = 5000;

OneWire oneWireBus(datenPin);
DallasTemperature sensoren(&oneWireBus);

unsigned long letzteMessungMs = 0;

void setup() {
  Serial.begin(9600);
  sensoren.begin();
  Serial.println("Erhitzungskurve bereit.");
  Serial.println("Sensor vollstaendig ins Eiswasser eintauchen, dann erst erwaermen.");
  Serial.println("Zeit in s ; Temperatur in C");
}

void loop() {
  unsigned long jetztMs = millis();

  if (jetztMs - letzteMessungMs >= messintervallMs) {
    letzteMessungMs = jetztMs;

    sensoren.requestTemperatures();
    float temperaturC = sensoren.getTempCByIndex(0);

    if (temperaturC == DEVICE_DISCONNECTED_C) {
      Serial.println("Sensor nicht gefunden. Verkabelung und Pull-up-Widerstand pruefen.");
    } else {
      Serial.print(jetztMs / 1000);
      Serial.print(" ; ");
      Serial.println(temperaturC);
    }
  }
}

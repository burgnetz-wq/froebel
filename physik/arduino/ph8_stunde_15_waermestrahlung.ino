// Ph8 Stunde 15: Vergleich der Erwaermung einer schwarzen und einer weissen
// Oberflaeche unter Waermestrahlung
// Sensoren: zwei wasserdichte Temperatursensoren DS18B20 am selben 1-Wire-Bus
//
// Pinbelegung:
//   Beide VCC (rot)     -> 5V (gemeinsam)
//   Beide GND (schwarz) -> GND (gemeinsam)
//   Beide Daten (gelb)  -> Digitalpin 2 (gemeinsam, ueber Seriennummer unterschieden)
//   Zusaetzlich: Pull-up-Widerstand 4,7 kOhm zwischen Datenpin und 5V
//
// Benoetigte Bibliotheken (wie in den Stunden 12 und 13):
//   "OneWire"
//   "DallasTemperature"
//
// Funktionsweise:
// Je ein Sensor wird auf einer schwarzen und einer weissen Oberflaeche
// befestigt, beide im gleichen Abstand und Winkel zu einer Waermelampe. Der
// Sketch misst alle 5 Sekunden beide Temperaturen gleichzeitig, sodass der
// Einfluss der Oberflaechenfarbe auf die Absorption von Waermestrahlung
// verglichen werden kann.

#include <OneWire.h>
#include <DallasTemperature.h>

const int datenPin = 2;
const unsigned long messintervallMs = 5000;

OneWire oneWireBus(datenPin);
DallasTemperature sensoren(&oneWireBus);

DeviceAddress sensorSchwarz, sensorWeiss;
bool zweiSensorenGefunden = false;

unsigned long letzteMessungMs = 0;

void setup() {
  Serial.begin(9600);
  sensoren.begin();

  int anzahlGefunden = sensoren.getDeviceCount();
  Serial.print("Gefundene Sensoren: ");
  Serial.println(anzahlGefunden);

  if (anzahlGefunden >= 2 &&
      sensoren.getAddress(sensorSchwarz, 0) &&
      sensoren.getAddress(sensorWeiss, 1)) {
    zweiSensorenGefunden = true;
    Serial.println("Beide Sensoren erfolgreich erkannt.");
    Serial.println("Sensor 1 = schwarze Oberflaeche, Sensor 2 = weisse Oberflaeche (je nach Befestigung).");
  } else {
    Serial.println("Achtung: Es wurden nicht zwei Sensoren gefunden. Verkabelung pruefen.");
  }

  Serial.println("Zeit in s ; Temperatur schwarz in C ; Temperatur weiss in C");
}

void loop() {
  unsigned long jetztMs = millis();

  if (zweiSensorenGefunden && (jetztMs - letzteMessungMs >= messintervallMs)) {
    letzteMessungMs = jetztMs;

    sensoren.requestTemperatures();

    float temperaturSchwarz = sensoren.getTempC(sensorSchwarz);
    float temperaturWeiss = sensoren.getTempC(sensorWeiss);

    Serial.print(jetztMs / 1000);
    Serial.print(" ; ");
    Serial.print(temperaturSchwarz);
    Serial.print(" ; ");
    Serial.println(temperaturWeiss);
  }
}

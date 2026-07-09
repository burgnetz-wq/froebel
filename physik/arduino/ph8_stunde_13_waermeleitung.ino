// Ph8 Stunde 13: Vergleich der Waermeleitfaehigkeit zweier Materialstaebe
// Sensoren: zwei wasserdichte Temperatursensoren DS18B20 am selben 1-Wire-Bus
//
// Pinbelegung:
//   Beide VCC (rot)     -> 5V (gemeinsam)
//   Beide GND (schwarz) -> GND (gemeinsam)
//   Beide Daten (gelb)  -> Digitalpin 2 (gemeinsam, ueber Seriennummer unterschieden)
//   Zusaetzlich: Pull-up-Widerstand 4,7 kOhm zwischen Datenpin und 5V
//
// Benoetigte Bibliotheken (wie in Stunde 12):
//   "OneWire"
//   "DallasTemperature"
//
// Funktionsweise:
// Je ein Sensor wird in gleichem Abstand von der Waermequelle an einem
// Metallstab und an einem Stab aus einem schlechteren Leiter (Holz oder
// Kunststoff) befestigt. Der Sketch misst alle 5 Sekunden beide Temperaturen
// gleichzeitig, sodass die unterschiedliche Ausbreitungsgeschwindigkeit der
// Waerme in beiden Materialien verglichen werden kann.

#include <OneWire.h>
#include <DallasTemperature.h>

const int datenPin = 2;
const unsigned long messintervallMs = 5000;

OneWire oneWireBus(datenPin);
DallasTemperature sensoren(&oneWireBus);

DeviceAddress sensorMetall, sensorAnderesMaterial;
bool zweiSensorenGefunden = false;

unsigned long letzteMessungMs = 0;

void setup() {
  Serial.begin(9600);
  sensoren.begin();

  int anzahlGefunden = sensoren.getDeviceCount();
  Serial.print("Gefundene Sensoren: ");
  Serial.println(anzahlGefunden);

  if (anzahlGefunden >= 2 &&
      sensoren.getAddress(sensorMetall, 0) &&
      sensoren.getAddress(sensorAnderesMaterial, 1)) {
    zweiSensorenGefunden = true;
    Serial.println("Beide Sensoren erfolgreich erkannt.");
    Serial.println("Sensor 1 = Metallstab, Sensor 2 = anderer Stab (je nach Befestigung).");
  } else {
    Serial.println("Achtung: Es wurden nicht zwei Sensoren gefunden. Verkabelung pruefen.");
  }

  Serial.println("Zeit in s ; Temperatur Stab 1 in C ; Temperatur Stab 2 in C");
}

void loop() {
  unsigned long jetztMs = millis();

  if (zweiSensorenGefunden && (jetztMs - letzteMessungMs >= messintervallMs)) {
    letzteMessungMs = jetztMs;

    sensoren.requestTemperatures();

    float temperaturStab1 = sensoren.getTempC(sensorMetall);
    float temperaturStab2 = sensoren.getTempC(sensorAnderesMaterial);

    Serial.print(jetztMs / 1000);
    Serial.print(" ; ");
    Serial.print(temperaturStab1);
    Serial.print(" ; ");
    Serial.println(temperaturStab2);
  }
}

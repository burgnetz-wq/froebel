// Ph8 Stunde 12: Gleichzeitige Temperaturmessung zweier Stoffe (Wasser und Oel)
// Sensor: zwei wasserdichte Temperatursensoren DS18B20 am selben 1-Wire-Bus
//
// Pinbelegung:
//   Beide VCC (rot)     -> 5V (gemeinsam)
//   Beide GND (schwarz) -> GND (gemeinsam)
//   Beide Daten (gelb)  -> Digitalpin 2 (gemeinsam, ueber Seriennummer unterschieden)
//   Zusaetzlich: Pull-up-Widerstand 4,7 kOhm zwischen Datenpin und 5V
//
// Benoetigte Bibliotheken (wie in Stunde 10):
//   "OneWire"
//   "DallasTemperature"
//
// Funktionsweise:
// Beide Sensoren teilen sich denselben 1-Wire-Bus und werden ueber ihre
// eindeutige Geraeteadresse unterschieden. Der Sketch liest beim Start die
// Adressen beider gefundenen Sensoren aus und misst danach alle 5 Sekunden
// beide Temperaturen gleichzeitig, sodass Wasser und Oel unter identischen
// Zeitbedingungen verglichen werden koennen.

#include <OneWire.h>
#include <DallasTemperature.h>

const int datenPin = 2;
const unsigned long messintervallMs = 5000;

OneWire oneWireBus(datenPin);
DallasTemperature sensoren(&oneWireBus);

DeviceAddress sensorAdresse1, sensorAdresse2;
bool zweiSensorenGefunden = false;

unsigned long letzteMessungMs = 0;

void setup() {
  Serial.begin(9600);
  sensoren.begin();

  int anzahlGefunden = sensoren.getDeviceCount();
  Serial.print("Gefundene Sensoren: ");
  Serial.println(anzahlGefunden);

  if (anzahlGefunden >= 2 &&
      sensoren.getAddress(sensorAdresse1, 0) &&
      sensoren.getAddress(sensorAdresse2, 1)) {
    zweiSensorenGefunden = true;
    Serial.println("Beide Sensoren erfolgreich erkannt.");
  } else {
    Serial.println("Achtung: Es wurden nicht zwei Sensoren gefunden. Verkabelung pruefen.");
  }

  Serial.println("Zeit in s ; Temperatur Sensor 1 in C ; Temperatur Sensor 2 in C");
}

void loop() {
  unsigned long jetztMs = millis();

  if (zweiSensorenGefunden && (jetztMs - letzteMessungMs >= messintervallMs)) {
    letzteMessungMs = jetztMs;

    sensoren.requestTemperatures();

    float temperatur1 = sensoren.getTempC(sensorAdresse1);
    float temperatur2 = sensoren.getTempC(sensorAdresse2);

    Serial.print(jetztMs / 1000);
    Serial.print(" ; ");
    Serial.print(temperatur1);
    Serial.print(" ; ");
    Serial.println(temperatur2);
  }
}

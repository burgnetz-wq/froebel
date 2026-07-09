/*
  Klasse 9 – Kraft als Wechselwirkung und physikalische Größe
  Funktion: Kraft mit Wägezelle und HX711 nach Kalibrierung messen
  Sensor/Aktor: Wägezelle mit HX711
  Messgröße/Rohwert: kalibrierte Kraft in N oder zunächst Rohwert

  Sicherheit:
  - Nur Schutzkleinspannung verwenden.
  - Aufbau vor dem Anschließen des USB-Kabels kontrollieren.
  - Motoren, Spulen und Relais niemals direkt aus einem I/O-Pin versorgen.
*/

#include <HX711.h>
const byte DOUT_PIN = 3;
const byte SCK_PIN = 2;
HX711 waage;
const float KALIBRIERFAKTOR = -7050.0f; // am eigenen Aufbau bestimmen

void setup() {
  Serial.begin(9600);
  waage.begin(DOUT_PIN, SCK_PIN);
  waage.set_scale(KALIBRIERFAKTOR);
  waage.tare();
  Serial.println(F("Zeit_ms;Messwert_kalibriert"));
}

void loop() {
  if (waage.is_ready()) {
    Serial.print(millis()); Serial.print(';'); Serial.println(waage.get_units(5), 3);
  }
  delay(200);
}

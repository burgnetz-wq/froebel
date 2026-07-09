/*
  Klasse 9 – Erdmagnetfeld und Kompass
  Funktion: Magnetische Raumrichtungen mit QMC5883L-Modul erfassen
  Sensor/Aktor: QMC5883L-Dreiachsen-Magnetometer
  Messgröße/Rohwert: relative x-, y- und z-Komponenten; Richtung nach Kalibrierung

  Sicherheit:
  - Nur Schutzkleinspannung verwenden.
  - Aufbau vor dem Anschließen des USB-Kabels kontrollieren.
  - Motoren, Spulen und Relais niemals direkt aus einem I/O-Pin versorgen.
*/

#include <Wire.h>
#include <QMC5883LCompass.h>
QMC5883LCompass kompass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  kompass.init();
  Serial.println(F("x_raw;y_raw;z_raw;Azimut_Grad"));
}

void loop() {
  kompass.read();
  Serial.print(kompass.getX()); Serial.print(';');
  Serial.print(kompass.getY()); Serial.print(';');
  Serial.print(kompass.getZ()); Serial.print(';');
  Serial.println(kompass.getAzimuth());
  delay(250);
}

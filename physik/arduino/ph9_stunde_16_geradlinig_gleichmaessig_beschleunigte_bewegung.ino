/*
  Klasse 9 – Geradlinig gleichmäßig beschleunigte Bewegung
  Funktion: Beschleunigungsdaten mit MPU6050 aufzeichnen und mitteln
  Sensor/Aktor: MPU6050
  Messgröße/Rohwert: Beschleunigungs-Rohwerte und kalibrierter Mittelwert

  Sicherheit:
  - Nur Schutzkleinspannung verwenden.
  - Aufbau vor dem Anschließen des USB-Kabels kontrollieren.
  - Motoren, Spulen und Relais niemals direkt aus einem I/O-Pin versorgen.
*/

#include <Wire.h>
const byte MPU = 0x68;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU); Wire.write(0x6B); Wire.write(0); Wire.endTransmission(true);
  Serial.begin(9600);
  Serial.println(F("ax_raw;ay_raw;az_raw"));
}

void loop() {
  Wire.beginTransmission(MPU); Wire.write(0x3B); Wire.endTransmission(false);
  Wire.requestFrom(MPU, (byte)6, (byte)true);
  int16_t ax = Wire.read()<<8 | Wire.read();
  int16_t ay = Wire.read()<<8 | Wire.read();
  int16_t az = Wire.read()<<8 | Wire.read();
  Serial.print(ax); Serial.print(';'); Serial.print(ay); Serial.print(';'); Serial.println(az);
  delay(50);
}

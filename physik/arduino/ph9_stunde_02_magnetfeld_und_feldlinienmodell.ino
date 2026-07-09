/*
  Klasse 9 – Magnetfeld und Feldlinienmodell
  Funktion: Magnetfeld an Messpunkten mit Hall-Sensor kartieren
  Sensor/Aktor: analoger Hall-Sensor A0
  Messgröße/Rohwert: Hall-Rohwert relativ zum Nullwert

  Sicherheit:
  - Nur Schutzkleinspannung verwenden.
  - Aufbau vor dem Anschließen des USB-Kabels kontrollieren.
  - Motoren, Spulen und Relais niemals direkt aus einem I/O-Pin versorgen.
*/

const byte HALL_PIN = A0;
const byte LED_PIN = 8;
int nullwert = 512;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println(F("Zeit_ms;Hall_Rohwert;Abweichung"));
}

void loop() {
  int rohwert = analogRead(HALL_PIN);
  int abweichung = rohwert - nullwert;
  digitalWrite(LED_PIN, abs(abweichung) > 20 ? HIGH : LOW);
  Serial.print(millis()); Serial.print(';'); Serial.print(rohwert); Serial.print(';'); Serial.println(abweichung);
  delay(100);
}

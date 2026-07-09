/*
  Klasse 9 – Relais und elektromagnetischer Türöffner
  Funktion: Relaismodul mit Taster und Status-LED steuern
  Sensor/Aktor: Taster D2, Relaismodul D8, Status-LED D13
  Messgröße/Rohwert: digitale Zustände EIN/AUS

  Sicherheit:
  - Nur Schutzkleinspannung verwenden.
  - Aufbau vor dem Anschließen des USB-Kabels kontrollieren.
  - Motoren, Spulen und Relais niemals direkt aus einem I/O-Pin versorgen.
*/

const byte TASTER_PIN = 2;
const byte RELAIS_PIN = 8;
const byte STATUS_LED = 13;

void setup() {
  pinMode(TASTER_PIN, INPUT_PULLUP);
  pinMode(RELAIS_PIN, OUTPUT); pinMode(STATUS_LED, OUTPUT);
}

void loop() {
  bool gedrueckt = digitalRead(TASTER_PIN) == LOW;
  digitalWrite(RELAIS_PIN, gedrueckt ? HIGH : LOW);
  digitalWrite(STATUS_LED, gedrueckt ? HIGH : LOW);
}

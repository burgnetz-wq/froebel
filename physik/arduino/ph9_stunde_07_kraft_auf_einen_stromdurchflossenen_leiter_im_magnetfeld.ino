/*
  Klasse 9 – Kraft auf einen stromdurchflossenen Leiter im Magnetfeld
  Funktion: Kurze definierte Stromimpulse über MOSFET ausgeben
  Sensor/Aktor: MOSFET-Treiber, Taster, Spule oder Leiterschaukel
  Messgröße/Rohwert: Impulsdauer und Schaltzustand

  Sicherheit:
  - Nur Schutzkleinspannung verwenden.
  - Aufbau vor dem Anschließen des USB-Kabels kontrollieren.
  - Motoren, Spulen und Relais niemals direkt aus einem I/O-Pin versorgen.
*/

const byte SPULEN_PIN = 9; // MOSFET-Gate, Spule niemals direkt anschließen
const byte TASTER_PIN = 2;
const byte HALL_PIN = A0;

void setup() {
  pinMode(SPULEN_PIN, OUTPUT); pinMode(TASTER_PIN, INPUT_PULLUP);
  digitalWrite(SPULEN_PIN, LOW);
  Serial.begin(9600);
  Serial.println(F("Zeit_ms;Hall_Rohwert;Spule"));
}

void loop() {
  bool an = digitalRead(TASTER_PIN) == LOW;
  analogWrite(SPULEN_PIN, an ? 160 : 0); // begrenzte PWM-Stufe
  int hall = analogRead(HALL_PIN);
  Serial.print(millis()); Serial.print(';'); Serial.print(hall); Serial.print(';'); Serial.println(an ? 1 : 0);
  delay(100);
}

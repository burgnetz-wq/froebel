/*
  Klasse 9 – Geschwindigkeit messen und berechnen
  Funktion: Geschwindigkeit aus zwei Ultraschall-Abstandswerten bestimmen
  Sensor/Aktor: HC-SR04
  Messgröße/Rohwert: Abstand in cm, Zeitintervall in s, berechnete Geschwindigkeit

  Sicherheit:
  - Nur Schutzkleinspannung verwenden.
  - Aufbau vor dem Anschließen des USB-Kabels kontrollieren.
  - Motoren, Spulen und Relais niemals direkt aus einem I/O-Pin versorgen.
*/

const byte TRIG_PIN = 8;
const byte ECHO_PIN = 9;
const byte LED_PIN = 5;
const byte PIEZO_PIN = 6;

float abstandCm() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long dauer = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (dauer == 0) return -1.0f;
  return dauer * 0.0343f / 2.0f;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT); pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT); pinMode(PIEZO_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println(F("Zeit_ms;Abstand_cm"));
}

void loop() {
  float d = abstandCm();
  if (d > 0) {
    Serial.print(millis()); Serial.print(';'); Serial.println(d, 1);
    bool warnung = d < 20.0f;
    digitalWrite(LED_PIN, warnung);
    if (warnung) tone(PIEZO_PIN, 1200, 80); else noTone(PIEZO_PIN);
  }
  delay(100);
}

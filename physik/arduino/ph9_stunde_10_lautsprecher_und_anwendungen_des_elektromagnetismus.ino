/*
  Klasse 9 – Lautsprecher und Anwendungen des Elektromagnetismus
  Funktion: Töne mit einstellbarer Frequenz erzeugen
  Sensor/Aktor: Piezo-Summer oder Kleinlautsprecher über Treiber D9, Potentiometer A0
  Messgröße/Rohwert: eingestellte Frequenz in Hz und Potentiometer-Rohwert

  Sicherheit:
  - Nur Schutzkleinspannung verwenden.
  - Aufbau vor dem Anschließen des USB-Kabels kontrollieren.
  - Motoren, Spulen und Relais niemals direkt aus einem I/O-Pin versorgen.
*/

const byte TON_PIN = 9;
const byte POTI_PIN = A0;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Poti_Rohwert;Frequenz_Hz"));
}

void loop() {
  int rohwert = analogRead(POTI_PIN);
  int frequenz = map(rohwert, 0, 1023, 200, 2000);
  tone(TON_PIN, frequenz);
  Serial.print(rohwert); Serial.print(';'); Serial.println(frequenz);
  delay(100);
}

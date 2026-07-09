/*
  Klasse 9 – Freier Fall als beschleunigte Bewegung
  Funktion: Fallzeit mit zwei Lichtschranken bzw. Photogates messen
  Sensor/Aktor: zwei Lichtschranken an D2 und D3
  Messgröße/Rohwert: Zeitdifferenz in Mikrosekunden und Fallzeit in s

  Sicherheit:
  - Nur Schutzkleinspannung verwenden.
  - Aufbau vor dem Anschließen des USB-Kabels kontrollieren.
  - Motoren, Spulen und Relais niemals direkt aus einem I/O-Pin versorgen.
*/

const byte START_PIN = 2;
const byte STOP_PIN = 3;
volatile unsigned long startUs = 0;
volatile unsigned long fallzeitUs = 0;

void startSignal() { startUs = micros(); }
void stopSignal()  { if (startUs > 0) fallzeitUs = micros() - startUs; }

void setup() {
  pinMode(START_PIN, INPUT_PULLUP); pinMode(STOP_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(START_PIN), startSignal, FALLING);
  attachInterrupt(digitalPinToInterrupt(STOP_PIN), stopSignal, FALLING);
  Serial.begin(9600);
  Serial.println(F("Fallzeit_s"));
}

void loop() {
  noInterrupts(); unsigned long t = fallzeitUs; fallzeitUs = 0; interrupts();
  if (t > 0) Serial.println(t / 1000000.0f, 6);
  delay(50);
}

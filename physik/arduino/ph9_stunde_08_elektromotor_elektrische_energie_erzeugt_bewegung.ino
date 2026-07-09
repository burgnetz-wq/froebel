/*
  Klasse 9 – Elektromotor – elektrische Energie erzeugt Bewegung
  Funktion: Gleichstrommotor über Transistortreiber oder H-Brücke steuern
  Sensor/Aktor: Motortreiber TB6612/L298N, Kleinmotor, Potentiometer A0
  Messgröße/Rohwert: PWM-Wert und Drehrichtung; Drehzahl nur qualitativ

  Sicherheit:
  - Nur Schutzkleinspannung verwenden.
  - Aufbau vor dem Anschließen des USB-Kabels kontrollieren.
  - Motoren, Spulen und Relais niemals direkt aus einem I/O-Pin versorgen.
*/

const byte PWM_PIN = 9;
const byte IN1_PIN = 7;
const byte IN2_PIN = 8;
const byte POTI_PIN = A0;

void setup() {
  pinMode(PWM_PIN, OUTPUT); pinMode(IN1_PIN, OUTPUT); pinMode(IN2_PIN, OUTPUT);
  digitalWrite(IN1_PIN, HIGH); digitalWrite(IN2_PIN, LOW);
  Serial.begin(9600);
  Serial.println(F("Poti_Rohwert;PWM"));
}

void loop() {
  int rohwert = analogRead(POTI_PIN);
  int pwm = map(rohwert, 0, 1023, 0, 255);
  analogWrite(PWM_PIN, pwm);
  Serial.print(rohwert); Serial.print(';'); Serial.println(pwm);
  delay(200);
}

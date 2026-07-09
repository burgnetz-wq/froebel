// Ph7 Stunde 22: Helligkeitsvergleich zweier Leuchtmittel (LED und Gluehlampe)
// Sensor: Fotowiderstand (LDR) als Spannungsteiler am analogen Eingang A0
//
// Pinbelegung:
//   LDR, ein Anschluss  -> 5V
//   LDR, zweiter Anschluss -> gemeinsame Steckbrettreihe mit:
//       - Widerstand 10 kOhm (zweiter Anschluss -> GND)
//       - Messkabel -> A0
//
// Funktionsweise:
// Der Analogeingang liefert einen Rohwert zwischen 0 (dunkel) und 1023
// (sehr hell). Dieser Rohwert ist dimensionslos und keine physikalische
// Groesse mit Einheit. Er wird hier verwendet, um die Helligkeit zweier
// Leuchtmittel bei gleichem Abstand und gleicher Ausrichtung miteinander
// zu vergleichen.

const int lichtSensor = A0;

void setup() {
  pinMode(lichtSensor, INPUT);
  Serial.begin(9600);
  Serial.println("Helligkeitsvergleich Leuchtmittel bereit.");
  Serial.println("Leuchtmittel einschalten und Sensor im festen Abstand halten.");
}

void loop() {
  int rohwert = analogRead(lichtSensor);

  Serial.print("Sensorrohwert: ");
  Serial.println(rohwert);

  delay(500); // Messintervall 500 ms
}

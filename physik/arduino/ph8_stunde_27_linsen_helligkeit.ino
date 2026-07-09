// Ph8 Stunde 27: Helligkeitsmessung an unterschiedlichen Positionen hinter
// einer Sammellinse
// Sensor: Fotowiderstand (LDR) als Spannungsteiler am analogen Eingang A0
// (identischer Aufbau wie beim Leuchtmittelvergleich in Klasse 7)
//
// Pinbelegung:
//   LDR, ein Anschluss     -> 5V
//   LDR, zweiter Anschluss -> gemeinsame Steckbrettreihe mit:
//       - Widerstand 10 kOhm (zweiter Anschluss -> GND)
//       - Messkabel -> A0
//
// Funktionsweise:
// Der Analogeingang liefert einen Rohwert zwischen 0 (dunkel) und 1023
// (sehr hell). Der Sensor wird entlang der optischen Achse hinter der
// Sammellinse verschoben; im Brennpunkt sollte der groesste Rohwert
// gemessen werden, da dort das Licht am staerksten gebuendelt ist.

const int lichtSensor = A0;

void setup() {
  pinMode(lichtSensor, INPUT);
  Serial.begin(9600);
  Serial.println("Helligkeitsmessung hinter der Sammellinse bereit.");
  Serial.println("Sensor entlang der optischen Achse verschieben und Werte vergleichen.");
}

void loop() {
  int rohwert = analogRead(lichtSensor);

  Serial.print("Sensorrohwert: ");
  Serial.println(rohwert);

  delay(500); // Messintervall 500 ms
}

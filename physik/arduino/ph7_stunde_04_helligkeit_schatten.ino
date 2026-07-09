// ============================================================
// Helligkeitsmessung in Schattenzonen
// Physik Klasse 7, Stunde 04: Licht und Schatten
// Thueringer Regelschule
// ------------------------------------------------------------
// Aufbau (Spannungsteiler):
//   Fotowiderstand (LDR): ein Anschluss an 5 V,
//     der zweite Anschluss in eine freie Steckbrettreihe.
//   Widerstand 10 kOhm: ein Anschluss in dieselbe Reihe wie der
//     zweite LDR-Anschluss, der andere an die Minusleitung (GND).
//   Messkabel: von der gemeinsamen Reihe (zwischen LDR und
//     Widerstand) zum analogen Eingang A0.
//   Minusleitung des Steckbretts an GND des Arduino.
// ------------------------------------------------------------
// Wichtig fuer den Unterricht:
//   analogRead liefert einen dimensionslosen Rohwert von 0 bis 1023.
//   Das ist KEINE physikalische Groesse mit Einheit. Erst eine
//   Kalibrierung wuerde daraus z. B. eine Beleuchtungsstaerke in Lux
//   machen. Viel Licht -> grosser Rohwert, wenig Licht -> kleiner Rohwert.
// ============================================================

// Pinbelegung
const int lichtSensor = A0;   // Messpunkt des Spannungsteilers an A0

// Messintervall in Millisekunden
const unsigned long messIntervall = 500;

void setup() {
  Serial.begin(9600);
  Serial.println("Helligkeitsmessung gestartet.");
  Serial.println("Rohwert 0 bis 1023 (dimensionslos, keine Einheit).");
  Serial.println("---------------------------------------------------");
}

void loop() {
  // Rohwert einlesen
  int lichtwert = analogRead(lichtSensor);

  // Rohwert ausgeben
  Serial.print("Sensorwert: ");
  Serial.print(lichtwert);

  // Einfache Balkenanzeige fuer den Beamer:
  // pro 100 Rohwert-Einheiten ein Zeichen
  Serial.print("   ");
  int balken = lichtwert / 100;
  for (int i = 0; i < balken; i = i + 1) {
    Serial.print("#");
  }
  Serial.println();

  delay(messIntervall);
}

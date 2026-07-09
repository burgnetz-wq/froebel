// Ph8 Stunde 20: Messung der induzierten Spannung einer Spule
// Sensor: Analogeingang A0 mit Spannungsteiler und Schutzdioden
//
// Pinbelegung:
//   Ein Spulenanschluss -> Widerstand R1 (10 kOhm) -> A0
//   A0 -> Widerstand R2 (10 kOhm) -> GND (Spannungsteiler, halbiert die Spannung)
//   zweiter Spulenanschluss -> GND
//   Schutzdiode 1 (z. B. 1N4148): Anode an A0, Kathode an 5V (leitet nur bei Ueberspannung)
//   Schutzdiode 2 (z. B. 1N4148): Anode an GND, Kathode an A0 (leitet nur bei negativer Spannung)
//
// WICHTIG: Der Spannungsteiler halbiert die tatsaechliche Spulenspannung,
// damit sie im sicheren Bereich des Analogeingangs (0 bis 5 V) bleibt. Die
// Schutzdioden fangen zusaetzlich kurze Spannungsspitzen ab.
//
// Funktionsweise:
// Der Sketch liest fortlaufend den Analogwert an A0 und merkt sich innerhalb
// eines Messfensters von 3 Sekunden den groessten aufgetretenen Wert (den
// Spitzenwert). Nach Ablauf des Messfensters wird der Spitzenwert ausgegeben
// und die Messung beginnt von neuem.

const int analogPin = A0;
const unsigned long messfensterMs = 3000;
const float spannungsteilerFaktor = 2.0; // Ausgleich fuer den Spannungsteiler (R1 = R2)

int spitzenwert = 0;
unsigned long fensterStartMs = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Induktionsmessung bereit.");
  Serial.println("Magnet durch die Spule bewegen, Spitzenwert wird alle 3 Sekunden ausgegeben.");
  fensterStartMs = millis();
}

void loop() {
  int rohwert = analogRead(analogPin);

  if (rohwert > spitzenwert) {
    spitzenwert = rohwert;
  }

  if (millis() - fensterStartMs >= messfensterMs) {
    float spannungAmPin = (spitzenwert / 1023.0) * 5.0;
    float geschaetzteSpulenspannung = spannungAmPin * spannungsteilerFaktor;

    Serial.print("Spitzenwert (Rohwert): ");
    Serial.print(spitzenwert);
    Serial.print("   geschaetzte Spulenspannung: ");
    Serial.print(geschaetzteSpulenspannung);
    Serial.println(" V");

    spitzenwert = 0;
    fensterStartMs = millis();
  }
}

// Ph8 Stunde 23: Automatisierte Gesamtwiderstandsmessung (Reihe und Parallel)
//
// Messprinzip: identisch zu Stunde 22. Anstelle eines einzelnen
// Testwiderstands wird die jeweilige Schaltung (Reihen- oder
// Parallelschaltung zweier Widerstaende) vor den Shunt-Widerstand
// geschaltet. Der Sketch berechnet den GESAMTWIDERSTAND dieser Schaltung,
// unabhaengig davon, ob es sich um eine Reihen- oder Parallelschaltung
// handelt - das haengt nur vom aeusseren Aufbau ab, nicht vom Sketch.
//
// Pinbelegung:
//   5V -> [Testschaltung: Reihe oder Parallel] -> Verbindungspunkt (= A0)
//        -> Shunt-Widerstand -> GND
//
// WICHTIG: Der Wert des Shunt-Widerstands muss exakt mit dem tatsaechlich
// verbauten Bauteil uebereinstimmen.

const int messPin = A0;
const float versorgungsspannung = 5.0;
const float shuntWiderstandOhm = 100.0; // ANPASSEN an den tatsaechlich verbauten Shunt-Widerstand

void setup() {
  Serial.begin(9600);
  Serial.println("Gesamtwiderstandsmessung bereit.");
  Serial.println("Reihen- oder Parallelschaltung anschliessen und Wert ablesen.");
}

void loop() {
  int rohwert = analogRead(messPin);
  float spannungShunt = (rohwert / 1023.0) * versorgungsspannung;

  if (spannungShunt < 0.01) {
    Serial.println("Zu geringe Spannung gemessen - Verkabelung pruefen.");
  } else {
    float stromstaerke = spannungShunt / shuntWiderstandOhm;
    float spannungSchaltung = versorgungsspannung - spannungShunt;
    float gesamtwiderstandOhm = spannungSchaltung / stromstaerke;

    Serial.print("Spannung Shunt: ");
    Serial.print(spannungShunt);
    Serial.print(" V   Stromstaerke: ");
    Serial.print(stromstaerke, 4);
    Serial.print(" A   Gesamtwiderstand: ");
    Serial.print(gesamtwiderstandOhm);
    Serial.println(" Ohm");
  }

  delay(1000); // Messintervall 1 Sekunde
}

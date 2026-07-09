// Ph8 Stunde 24: Automatisierte Berechnung der elektrischen Leistung
//
// Messprinzip: Ein Bauteil (LED mit Vorwiderstand, Widerstand oder kleiner
// Motor) liegt in Reihe mit einem bekannten Shunt-Widerstand zwischen
// Versorgungsspannung (5V) und GND. A0 misst die Spannung am Shunt (fuer die
// Stromstaerke), A2 misst die Spannung direkt am Pluspol des Bauteils
// gegenueber GND (fuer die Spannung ueber dem Bauteil). Aus beiden Werten
// wird die elektrische Leistung P = U * I des Bauteils berechnet.
//
// Pinbelegung:
//   5V -> Bauteil -> Messpunkt A2 -> Verbindung zum Shunt -> A0 -> Shunt -> GND
//   (A2 liegt am Uebergang zwischen Bauteil und Shunt, entspricht der
//    Spannung ueber dem Shunt PLUS der Spannung ueber dem Bauteil bis GND;
//    in diesem einfachen Aufbau wird A2 daher direkt am Pluspol des
//    Bauteils gegenueber GND gemessen, siehe Tiddler fuer den genauen Aufbau)
//
// WICHTIG: Der Wert des Shunt-Widerstands muss exakt mit dem tatsaechlich
// verbauten Bauteil uebereinstimmen. Bei LEDs ist ein passender
// Vorwiderstand zwingend erforderlich.

const int shuntMessPin = A0;
const int bauteilMessPin = A2;
const float versorgungsspannung = 5.0;
const float shuntWiderstandOhm = 100.0; // ANPASSEN an den tatsaechlich verbauten Shunt-Widerstand

void setup() {
  Serial.begin(9600);
  Serial.println("Leistungsmessung bereit.");
  Serial.println("Bauteil einsetzen und Leistung ablesen.");
}

void loop() {
  int rohwertShunt = analogRead(shuntMessPin);
  int rohwertBauteil = analogRead(bauteilMessPin);

  float spannungShunt = (rohwertShunt / 1023.0) * versorgungsspannung;
  float spannungBauteil = (rohwertBauteil / 1023.0) * versorgungsspannung;

  if (spannungShunt < 0.01) {
    Serial.println("Zu geringe Spannung gemessen - Verkabelung pruefen.");
  } else {
    float stromstaerke = spannungShunt / shuntWiderstandOhm;
    float leistungWatt = spannungBauteil * stromstaerke;

    Serial.print("Spannung Bauteil: ");
    Serial.print(spannungBauteil);
    Serial.print(" V   Stromstaerke: ");
    Serial.print(stromstaerke, 4);
    Serial.print(" A   Leistung: ");
    Serial.print(leistungWatt, 4);
    Serial.println(" W");
  }

  delay(1000); // Messintervall 1 Sekunde
}

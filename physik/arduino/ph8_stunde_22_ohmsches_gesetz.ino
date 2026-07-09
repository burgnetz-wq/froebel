// Ph8 Stunde 22: Automatisierte Widerstandsbestimmung ueber einen Shunt-Widerstand
//
// Messprinzip: Testwiderstand und Shunt-Widerstand (bekannter Wert) liegen
// in Reihe zwischen der Versorgungsspannung (5V) und GND. Die Spannung am
// Verbindungspunkt (A0) entspricht der Spannung ueber dem Shunt-Widerstand.
// Daraus wird die Stromstaerke berechnet, und aus Versorgungsspannung minus
// Shunt-Spannung ergibt sich die Spannung ueber dem Testwiderstand.
//
// Pinbelegung:
//   5V -> Testwiderstand -> Verbindungspunkt (= A0) -> Shunt-Widerstand -> GND
//
// WICHTIG: Der Wert des Shunt-Widerstands (shuntWiderstandOhm) muss exakt
// mit dem tatsaechlich verbauten Bauteil uebereinstimmen, sonst verfaelscht
// sich das Ergebnis systematisch.

const int messPin = A0;
const float versorgungsspannung = 5.0;
const float shuntWiderstandOhm = 100.0; // ANPASSEN an den tatsaechlich verbauten Shunt-Widerstand

void setup() {
  Serial.begin(9600);
  Serial.println("Widerstandsmessung bereit.");
  Serial.println("Testwiderstand einsetzen und Wert ablesen.");
}

void loop() {
  int rohwert = analogRead(messPin);
  float spannungShunt = (rohwert / 1023.0) * versorgungsspannung;

  if (spannungShunt < 0.01) {
    Serial.println("Zu geringe Spannung gemessen - Verkabelung pruefen.");
  } else {
    float stromstaerke = spannungShunt / shuntWiderstandOhm; // I = U/R am Shunt
    float spannungTestwiderstand = versorgungsspannung - spannungShunt;
    float testwiderstandOhm = spannungTestwiderstand / stromstaerke;

    Serial.print("Spannung Shunt: ");
    Serial.print(spannungShunt);
    Serial.print(" V   Stromstaerke: ");
    Serial.print(stromstaerke, 4);
    Serial.print(" A   Testwiderstand: ");
    Serial.print(testwiderstandOhm);
    Serial.println(" Ohm");
  }

  delay(1000); // Messintervall 1 Sekunde
}

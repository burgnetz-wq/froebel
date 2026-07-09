// Ph8 Stunde 04: Fortlaufende Positionsmessung zur Beschleunigungsberechnung
// Sensor: Ultraschallsensor HC-SR04, am unteren Ende der geneigten Bahn montiert
//
// Pinbelegung:
//   VCC  -> 5V
//   GND  -> GND
//   Trig -> Digitalpin 9
//   Echo -> Digitalpin 10
//
// Funktionsweise:
// Der Sensor misst alle 100 Millisekunden die Entfernung zum Wagen (engeres
// Messintervall als in Stunde 2, da sich die Geschwindigkeit hier schneller
// aendert). Aus den ersten beiden und den letzten beiden Wertepaaren
// (Zeit, Entfernung) berechnen die Schueler von Hand zunaechst zwei
// Geschwindigkeiten und daraus die Beschleunigung a = (v2 - v1) / (t2 - t1).

const int trigPin = 9;
const int echoPin = 10;
const unsigned long messintervallMs = 100;

unsigned long letzteMessungMs = 0;

long entfernungMessenCm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long laufzeitMikrosekunden = pulseIn(echoPin, HIGH, 30000);

  if (laufzeitMikrosekunden == 0) {
    return -1; // kein gueltiges Echo empfangen
  }

  long entfernungCm = laufzeitMikrosekunden / 58;
  return entfernungCm;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.println("Beschleunigungsmessung bereit.");
  Serial.println("Wagen oben festhalten, Messung laeuft bereits mit.");
  Serial.println("Zeit in ms ; Entfernung in cm");
}

void loop() {
  unsigned long jetztMs = millis();

  if (jetztMs - letzteMessungMs >= messintervallMs) {
    letzteMessungMs = jetztMs;

    long entfernung = entfernungMessenCm();

    if (entfernung > 0) {
      Serial.print(jetztMs);
      Serial.print(" ; ");
      Serial.println(entfernung);
    } else {
      Serial.println("kein gueltiger Messwert");
    }
  }
}

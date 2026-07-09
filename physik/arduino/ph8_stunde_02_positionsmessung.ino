// Ph8 Stunde 02: Fortlaufende Positionsmessung eines rollenden Wagens
// Sensor: Ultraschallsensor HC-SR04, am Ende der Bahn montiert
//
// Pinbelegung:
//   VCC  -> 5V
//   GND  -> GND
//   Trig -> Digitalpin 9
//   Echo -> Digitalpin 10
//
// Funktionsweise:
// Der Sensor misst alle 200 Millisekunden die Entfernung zum Wagen und gibt
// sie zusammen mit der seit Programmstart verstrichenen Zeit aus. Aus diesen
// Wertepaaren (Zeit, Entfernung) laesst sich ein Weg-Zeit-Diagramm erstellen:
// Der zurueckgelegte Weg ergibt sich aus der Differenz zwischen der
// Startentfernung und der jeweils aktuellen Entfernung.

const int trigPin = 9;
const int echoPin = 10;
const unsigned long messintervallMs = 200;

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
  Serial.println("Positionsmessung bereit.");
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

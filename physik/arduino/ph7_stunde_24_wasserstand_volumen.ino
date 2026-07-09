// Ph7 Stunde 24: Automatisierte Wasserstandsmessung zur Volumenbestimmung
// Sensor: Ultraschallsensor HC-SR04, senkrecht ueber dem Standzylinder montiert
//
// Pinbelegung:
//   VCC  -> 5V
//   GND  -> GND
//   Trig -> Digitalpin 9
//   Echo -> Digitalpin 10
//
// Funktionsweise:
// Der Sensor misst fortlaufend die Entfernung zwischen sich und der
// Wasseroberflaeche im Standzylinder. Sinkt die Entfernung (weil der
// Wasserstand durch einen eingetauchten Koerper ansteigt), kann die
// Wasserstandsaenderung aus der Differenz zweier Messungen bestimmt
// werden. Aus der Wasserstandsaenderung und der bekannten Grundflaeche
// des Standzylinders laesst sich das Volumen des eingetauchten Koerpers
// berechnen: V = Grundflaeche * Hoehenaenderung.
//
// Hinweis: Die Berechnung des Volumens erfolgt bewusst nicht im Sketch,
// sondern von den Schuelern selbst mit der bekannten Grundflaeche des
// verwendeten Standzylinders - der Sketch liefert nur den Rohwert der
// Entfernung.

const int trigPin = 9;
const int echoPin = 10;

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
  Serial.println("Wasserstandsmessung bereit.");
  Serial.println("Erst Nullmessung ohne Koerper, danach Koerper eintauchen.");
}

void loop() {
  long entfernung = entfernungMessenCm();

  if (entfernung > 0) {
    Serial.print("Entfernung zur Wasseroberflaeche: ");
    Serial.print(entfernung);
    Serial.println(" cm");
  } else {
    Serial.println("Kein gueltiger Messwert - Sensorausrichtung pruefen.");
  }

  delay(500); // Messintervall 500 ms, damit die Wasseroberflaeche sich beruhigen kann
}

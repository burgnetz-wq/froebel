// Ph7 Stunde 20: Automatische Zeitmessung eines Hubvorgangs
// Sensor: Ultraschallsensor HC-SR04, oberhalb der Hubstrecke montiert
//
// Pinbelegung:
//   VCC  -> 5V
//   GND  -> GND
//   Trig -> Digitalpin 9
//   Echo -> Digitalpin 10
//
// Funktionsweise:
// Der Sensor misst fortlaufend die Entfernung zwischen sich und dem
// zu hebenden Gewicht. Sobald die Entfernung die Startschwelle
// unterschreitet (Gewicht hat sich vom Boden gelöst), beginnt die
// Zeitmessung. Sobald die Entfernung die Zielschwelle unterschreitet
// (Gewicht hat die markierte Zielhöhe erreicht), wird die Zeitmessung
// gestoppt und die verstrichene Zeit in Millisekunden ausgegeben.
//
// Wichtig: Die Schwellenwerte muessen vor dem Unterricht am realen
// Aufbau (Sensorhoehe, Hubstrecke) kalibriert werden.

const int trigPin = 9;
const int echoPin = 10;

// Schwellenwerte in Zentimetern - vor dem Einsatz am eigenen Aufbau anpassen
const int startSchwelleCm = 140;  // Entfernung, ab der der Hub beginnt
const int zielSchwelleCm  = 90;   // Entfernung an der Zielhoehe

bool messungLaeuft = false;
unsigned long startZeit = 0;

long entfernungMessenCm() {
  // Trigger-Impuls erzeugen (10 Mikrosekunden HIGH)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Laufzeit des Echo-Signals messen (Timeout nach 30 ms)
  long laufzeitMikrosekunden = pulseIn(echoPin, HIGH, 30000);

  if (laufzeitMikrosekunden == 0) {
    return -1; // kein gueltiges Echo empfangen
  }

  // Schallgeschwindigkeit ca. 343 m/s -> Entfernung in cm = Laufzeit / 58
  long entfernungCm = laufzeitMikrosekunden / 58;
  return entfernungCm;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.println("Zeitmessung Hubvorgang bereit.");
  Serial.println("Gewicht an die Startmarke halten, dann anheben.");
}

void loop() {
  long entfernung = entfernungMessenCm();

  if (entfernung > 0) {
    Serial.print("Entfernung: ");
    Serial.print(entfernung);
    Serial.println(" cm");

    // Start der Zeitmessung: Entfernung faellt unter die Startschwelle
    if (!messungLaeuft && entfernung <= startSchwelleCm && entfernung > zielSchwelleCm) {
      messungLaeuft = true;
      startZeit = millis();
      Serial.println(">>> Start der Zeitmessung <<<");
    }

    // Stopp der Zeitmessung: Entfernung faellt unter die Zielschwelle
    if (messungLaeuft && entfernung <= zielSchwelleCm) {
      unsigned long dauer = millis() - startZeit;
      Serial.print(">>> Ziel erreicht. Gemessene Zeit: ");
      Serial.print(dauer);
      Serial.println(" ms <<<");
      messungLaeuft = false;
    }
  }

  delay(50); // Messintervall ca. 50 ms
}

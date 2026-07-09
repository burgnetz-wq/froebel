// ============================================================
// Reaktionszeitmesser
// Physik Klasse 7, Stunde 02: Messen und Protokollieren
// Thueringer Regelschule
// ------------------------------------------------------------
// Aufbau:
//   LED:    Anode (langes Bein) ueber 220-Ohm-Widerstand an Pin 8,
//           Kathode (kurzes Bein) an die Minusleitung (GND).
//   Taster: ein Beinpaar an Pin 2, das andere an die Minusleitung (GND).
//           Es wird der interne Pull-up-Widerstand benutzt,
//           darum ist der Taster im Ruhezustand HIGH und beim
//           Druecken LOW.
//   Minusleitung des Steckbretts an GND des Arduino.
// ------------------------------------------------------------
// Ablauf:
//   1. Zufaellige Wartezeit (2 bis 5 Sekunden).
//   2. LED geht an -> Startsignal.
//   3. Schueler drueckt den Taster so schnell wie moeglich.
//   4. Die Reaktionszeit wird in Millisekunden ausgegeben.
//   Wird der Taster zu frueh gedrueckt, gilt der Versuch nicht.
// ============================================================

// Pinbelegung
const int ledPin = 8;      // LED an Digitalpin 8
const int tasterPin = 2;   // Taster an Digitalpin 2

// Variablen fuer die Zeitmessung
unsigned long startZeit = 0;      // Zeitpunkt, an dem die LED angeht
unsigned long reaktionsZeit = 0;  // gemessene Reaktionszeit in ms

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(tasterPin, INPUT_PULLUP); // interner Pull-up-Widerstand

  Serial.begin(9600);
  Serial.println("Reaktionszeitmesser bereit.");
  Serial.println("Warte auf die LED und druecke dann sofort den Taster!");
  Serial.println("------------------------------------------------------");

  randomSeed(analogRead(A5)); // Zufallszahlen aus Rauschen des freien Pins
}

void loop() {
  digitalWrite(ledPin, LOW);          // LED aus: Ruhephase

  // Zufaellige Wartezeit zwischen 2000 ms und 5000 ms
  unsigned long wartezeit = random(2000, 5001);
  unsigned long warteStart = millis();

  // Waehrend der Wartezeit auf Fruehstart pruefen
  bool fruehstart = false;
  while (millis() - warteStart < wartezeit) {
    if (digitalRead(tasterPin) == LOW) {   // Taster zu frueh gedrueckt
      fruehstart = true;
      break;
    }
  }

  if (fruehstart) {
    Serial.println("Zu frueh gedrueckt! Dieser Versuch zaehlt nicht.");
    delay(1500);                    // kurze Pause
    while (digitalRead(tasterPin) == LOW) {
      // warten, bis der Taster losgelassen wurde
    }
    return;                         // neuer Durchlauf
  }

  // Startsignal: LED an, Zeit merken
  digitalWrite(ledPin, HIGH);
  startZeit = millis();

  // Auf den Tastendruck warten
  while (digitalRead(tasterPin) == HIGH) {
    // warten
  }

  // Reaktionszeit berechnen und ausgeben
  reaktionsZeit = millis() - startZeit;
  digitalWrite(ledPin, LOW);

  Serial.print("Reaktionszeit: ");
  Serial.print(reaktionsZeit);
  Serial.println(" ms");
  Serial.println("Naechster Versuch startet gleich ...");
  Serial.println("------------------------------------------------------");

  delay(2000); // Pause, dann neuer Durchlauf
}

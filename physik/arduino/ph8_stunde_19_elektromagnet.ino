// Ph8 Stunde 19: Gesteuerter Elektromagnet ueber Transistor
// Aktor: Elektromagnet (selbstgewickelte Spule mit Eisenkern),
//        angesteuert ueber einen NPN-Transistor (z. B. BC547)
//
// Pinbelegung:
//   Digitalpin 8 -> Basiswiderstand 1 kOhm -> Basis des Transistors
//   Emitter des Transistors -> GND (Arduino)
//   Kollektor des Transistors -> ein Anschluss der Elektromagnet-Spule
//   zweiter Anschluss der Spule -> Pluspol einer SEPARATEN Batterie/Netzteil
//   Freilaufdiode (z. B. 1N4007) parallel zur Spule, Kathode am Pluspol
//   Minuspol der separaten Spannungsquelle -> GND (Arduino, gemeinsame Masse)
//
// WICHTIG: Die Spule wird NICHT direkt vom Arduino versorgt, da der
// Stromverbrauch die Belastbarkeit eines Arduino-Pins ueberschreiten wuerde.
// Die Freilaufdiode ist zwingend erforderlich, um den Transistor vor
// Spannungsspitzen beim Abschalten zu schuetzen.
//
// Funktionsweise:
// Ueber den seriellen Monitor kann der Elektromagnet ein- und ausgeschaltet
// werden. Eingabe "1" schaltet ein, Eingabe "0" schaltet aus. Zusaetzlich
// schaltet sich der Magnet nach einer festen Zeit automatisch wieder ab,
// damit die Spule nicht ueberhitzt.

const int steuerPin = 8;
const unsigned long maximaleEinschaltdauerMs = 10000; // Sicherheitsabschaltung nach 10 s

bool eingeschaltet = false;
unsigned long einschaltzeitpunktMs = 0;

void setup() {
  pinMode(steuerPin, OUTPUT);
  digitalWrite(steuerPin, LOW);
  Serial.begin(9600);
  Serial.println("Elektromagnet-Steuerung bereit.");
  Serial.println("Eingabe '1' zum Einschalten, '0' zum Ausschalten senden.");
}

void loop() {
  if (Serial.available() > 0) {
    char eingabe = Serial.read();

    if (eingabe == '1') {
      digitalWrite(steuerPin, HIGH);
      eingeschaltet = true;
      einschaltzeitpunktMs = millis();
      Serial.println("Elektromagnet EIN.");
    } else if (eingabe == '0') {
      digitalWrite(steuerPin, LOW);
      eingeschaltet = false;
      Serial.println("Elektromagnet AUS.");
    }
  }

  // Sicherheitsabschaltung, falls vergessen wird, manuell auszuschalten
  if (eingeschaltet && (millis() - einschaltzeitpunktMs >= maximaleEinschaltdauerMs)) {
    digitalWrite(steuerPin, LOW);
    eingeschaltet = false;
    Serial.println("Automatische Sicherheitsabschaltung nach 10 Sekunden.");
  }
}

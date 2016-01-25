#include <PinChangeInt.h>

#define UMSCHALTDAUER 1000
#define NACHTDAUER 500
#define GELBTIME 500

boolean power = true; //Aktuellen Status
boolean changed = false; //Wenn es eine Änderung gab
long starttime; //Startzeit der aktuellen Phase
long teststarttime; //Startzeit des Tests
boolean ampel1rot = true; //Status der 1. Ampel
boolean testac = false;
boolean tag = true;
boolean interrupted = false;
boolean ampelrot = false;

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(4, INPUT); //Pin 4 als Input
  digitalWrite(4, HIGH); //Pullup auf Pin 4 aktivieren
    pinMode(5, INPUT); //Pin 5 als Input
  digitalWrite(5, HIGH); //Pullup auf Pin 5 aktivieren
    pinMode(6, INPUT); //Pin 6 als Input
  digitalWrite(6, HIGH); //Pullup auf Pin 6 aktivieren
    PCintPort::attachInterrupt(5, test,FALLING); //Interrupt von Pin 5 sensitiv auf fallende Flanke mit der funktion powerswitch verknüpfen
  PCintPort::attachInterrupt(6, tagnacht,FALLING); //Interrupt von Pin 6 sensitiv auf fallende Flanke mit der funktion powerswitch verknüpfen
  PCintPort::attachInterrupt(4, powerswitch,FALLING); //Interrupt von Pin 4 sensitiv auf fallende Flanke mit der funktion powerswitch verknüpfen
  starttime = millis();
}

void loop() { //Hauptprogramm
interrupted = false;
  if(testac) { //Wenn ein Test angefordert wurde
    teststarttime = millis(); // Startzeit des Tests in die variable
    while(millis() - teststarttime < 5000) { //Während der Test aktiv ist
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      digitalWrite(A4, HIGH);
      digitalWrite(A5, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
    }
    allesaus();
    testac= false; //Test abgeschlossen
  } //Test angefordet Abfrage ende
  if(power) { //Wenn die Ampel aktiv sein soll
    if(tag) { //Wenn Ampel im Tagmodus
      if(millis() - starttime > UMSCHALTDAUER) { //Wenn länger als Umschaltdauer
        if(ampel1rot) { //Ampel 1 war Rot, also Ampel 1 wird grün
          for (int i = 0; i < GELBTIME; i++) {
            allesaus();
            digitalWrite(A1, HIGH);
            digitalWrite(A5, HIGH);
            delay(1);
            if(interrupted)
              break;
            }
            for (int i = 0; i < 3*GELBTIME; i++) {
              allesaus();
              digitalWrite(A5, HIGH);
              digitalWrite(A2, HIGH);
              delay(1);
              if(interrupted)
                break; 
              }
           for (int i = 0; i < 3*GELBTIME; i++) {
              allesaus();
              digitalWrite(A4, HIGH);
              digitalWrite(A0, HIGH);
              delay(1);
              if(interrupted)
                break; 
              }
          } 
        else { //Ampel 1 war grün, also auf Rot schalten
          for (int i = 0; i < GELBTIME; i++) {
            allesaus();
            digitalWrite(A1, HIGH);
            delay(1);
            if(interrupted)
              break; 
            }
            for (int i = 0; i < GELBTIME; i++) {
              allesaus();
           digitalWrite(A2, HIGH);
              delay(1);
              if(interrupted)
                break; 
              }
        }
        ampelrot = !ampelrot; //Zustandsänderung schreiben
        starttime = millis(); //Startzeit der aktuellen Phase auf die aktuelle Zeit setzen
      }
    } 
    else { //Wenn Ampel im Nachtmodus
      if(millis() - starttime > NACHTDAUER) { //Wenn länger als Nachtdauer
        digitalWrite(A0, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
        digitalWrite(A1, !digitalRead(A1)); //Gelb 1 umschalten
        digitalWrite(9, !digitalRead(9)); //Gelb 2 umschalten
        starttime = millis(); //Startzeit der aktuellen Phase auf die aktuelle Zeit setzen
      }
    }

  } 
  else { //Wenn  die Ampel nicht aktiv sein soll
    allesaus(); //Alles ausschalten
  } //Ende der Power Abfrage

}

void allesaus() { //Funktion um alle LEDs auszuschalten
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void tagnacht() { //Wird durch Interrupt aufgerufen
  tag = !tag;  //Tag umschalten
} //Ende Interrupt

void test() { //Wird durch Interrupt aufgerufen
  testac = true; //Testmodus aktivieren 
} //Ende test

void powerswitch() { //Wird durch Interrupt aufgerufen
  power = !power; //Power umschalten
} //Ende powerswitch



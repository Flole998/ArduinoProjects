#include <MD5.h> //MD5 Bibliotghek importieren
#include <LiquidCrystal.h> //Bibliothek für das LCD importieren
#include <EEPROM.h> //EEprom Bibliothek importieren

int numfail = 0; //Anzahl der fehlgeschlagenen Versuche speichern
int code = 0; //Aktuellen Code speichern
int dig1,dig2,dig3; //Status der Schalter 1, 2 und 3
boolean pushed; //Status des Tasters an der Innenseite
LiquidCrystal lcd(A0, A1, A4, A2, A3, A5); //LCD Pindefinitionen
String salt = "gjhk7786nghdfzr6"; //Salt für den Hashwert definieren
const char* codehash = "bc6cd9de0e5f4d3ecb5aa4b9bacec35a"; //Gesalted und Gehashten Code um das knacken zu Erschweren
String currentcodehash = ""; //Gesalted und Gehashte codeeingabe

void setup() {
  pinMode(3, OUTPUT); //Pin für das Relay auf Output     
  pinMode(2, INPUT); //Taster an der Innenseite als Input
  digitalWrite(2, HIGH);  //Pullup aktivieren
  pinMode(6, INPUT); //Taster 1 als Input
  digitalWrite(6, HIGH);  //Pullup aktivieren
  pinMode(7, INPUT);  //Taster 2 als Input
  digitalWrite(7, HIGH);  //Pullup aktivieren
  pinMode(8, INPUT); //Taster 3 als Input
  digitalWrite(8, HIGH);  //Pullup aktivieren
  pinMode(4, INPUT);  //Bestätigungstaser als Input
  digitalWrite(4, HIGH); //Pullup aktivieren
  pinMode(9, OUTPUT);   //LED Rot als Output
  pinMode(10, OUTPUT);  //LED Grün als Output
  digitalWrite(10, HIGH); //LED Grün aus
  Serial.begin(9600); //Fürs Debugging UART auf 9600 stellen
  lcd.begin(16, 2); //LCD Zeilen und Spalten setzen
  int waittime = EEPROM.read(0); //Eventuelle gespeicherte Wartezeit einlesen 
  if(waittime > 0) { //Wenn eine Wartezeit gespeichert wurde
    while (waittime > 0) { //Während wir noch eine Wartezeit haben
      lcd.clear(); //Display leeren
      lcd.setCursor(0, 0); //Erste Zeile anwählen
      lcd.print("FAIL"); //Fehlermeldung ausgeben
      lcd.setCursor(0, 1); //Zweite Zeile anwählen
      lcd.print(waittime); //Restzeit anzeigen
      delay(1000); //Eine Sekunde warten
      waittime--; //Restzeit runterzählen
    } //Wartezeit beendet
    EEPROM.write(0, 0); //0 Als verbleibende Wartezeit einspeichern
  }
  lcd.clear(); //Display leeren
  lcd.setCursor(0, 0); //Erste Zeile anwählen
  lcd.print("Code eingeben:"); //Codeabfrage anzeigen
}

void loop(){
  if (digitalRead(2)) {     //Wenn Taster auf der Innenseite gedrückt
    digitalWrite(3, HIGH);  //Relay schließen
    digitalWrite(10, HIGH);  //Rote LED aus
    digitalWrite(9, LOW); //Grüne LED an
  } 
  else { //Wenn Taster auf der Innenseite nicht gedrückt
    digitalWrite(3, LOW);  //Relay aus
    digitalWrite(10, LOW);  //Grüne LED aus
    digitalWrite(9, HIGH);  //Rote LED an
  } //Ende Taster Innenseite If

  if(!digitalRead(6)){ //Wenn Taster 1 gedrückt
    if(!pushed){ //Wenn Taster vorher nicht gedrückt war
      dig1++; //Ziffer 1 hochzählen
      if(dig1==10){ //Wenn Ziffer 1 = 10
        dig1 = 0; //Ziffer 1 = 0
      } //Ende Ziffer 1 If
    } //Ende taster war gedrückt
    pushed = true; //Einer der Taster war gedrückt
  } //Ende Taster 1 gedrückt
  else if(!digitalRead(7)){ //Wenn Taster 2 gedrückt
    if(!pushed){ //Wenn Taster vorher nicht gedrückt war
      dig2++; //Ziffer 2 hochzählen
      if(dig2==10){ //Wenn Ziffer 2 = 10
        dig2 = 0;//Ziffer 2 = 0
      } //Ende Ziffer 2 If
    }//Ende taster war gedrückt
    pushed = true;//Einer der Taster war gedrückt
  } //Ende Taster 2 gedrückt
  else if(!digitalRead(8)){//Wenn Taster 3 gedrückt
    if(!pushed){ //Wenn Taster vorher nicht gedrückt war
      dig3++; //Ziffer 3 hochzählen
      if(dig3==10){ //Wenn Ziffer 3 = 10
        dig3 = 0;//Ziffer 3 = 0
      }//Ende Ziffer 3 If
    }//Ende taster war gedrückt
    pushed = true;//Einer der Taster war gedrückt
  } //Ende Taster 3 gedrückt
  else { //Kein Taster gedrückt
    pushed = false; //Kein Taster gedrückt
  } //Ende Tasterabfrage

    lcd.setCursor(0, 1); //Folgende zeilen in die Zweite Zeile des LCD Schreiben
  lcd.print(dig1); //Ziffer 1 ausgeben
  lcd.print(dig2); //Ziffer 2 ausgeben
  lcd.print(dig3); //Ziffer 3 ausgeben

  if(!digitalRead(4)) { //Wenn bestätigungstaster gedrückt
    char charBuf[50]; //Temporären Puffer für das chararray
    currentcodehash = salt; //salt in den aktuellen Hash kopieren
    currentcodehash.concat(dig1*100); //Erste Ziffer anhängen
    currentcodehash.concat(dig2*10); // 2. Auch
    currentcodehash.concat(dig3); //3. Auch
    currentcodehash.toCharArray(charBuf, 50); //Aktuellen Code in den puffer kopieren
    unsigned char* hash=MD5::make_hash(charBuf); //hash erstellen
    if(strcmp(MD5::make_digest(hash, 16), codehash) == 0 ) { //digest des hashed mit dem codehash vergleichen
      lcd.setCursor(0, 1); //Cursor in die Zweite Zeile
      lcd.print("OK "); //OK ausgeben
      numfail = 0; //Anzahl Fehlversuche auf 0
      EEPROM.write(0, 0); //-1 Als verbleibende Wartezeit einspeichern
      digitalWrite(3, LOW); // Relai an
      digitalWrite(10, LOW); //Grüne LED an
      digitalWrite(9, HIGH);  // Rote LED aus
      delay(1000); //Eine Sekunde warten
      digitalWrite(3, HIGH); //Relai wieder aus
      digitalWrite(10, HIGH);  //Grüne LED aus
      digitalWrite(9, LOW);  //Rote LED an
    } 
    else { //Code war falsch
      numfail++; //Fehlversuche hochzählen
      int waittime = pow(numfail, 2); //Wartezeit ausrechnen
      EEPROM.write(0, waittime); //An Adresse 0 des EEProm schreiben um Rücksetzen durch Fehlversuche zu vermeiden
      while (waittime > 0) { //Für jede sekunde
        lcd.clear(); //Display leeren
        lcd.setCursor(0, 0); //Erste Zeile anwählen
        lcd.print("FAIL"); //Fehlermeldung ausgeben
        lcd.setCursor(0, 1); //Zweite Zeile anwählen
        lcd.print(waittime); //Restzeit anzeigen
        delay(1000); //Eine Sekunde warten
        waittime--; //Restzeit runterzählen
      } //Sperrzeit beendet
      lcd.clear(); //Bildschirm leeren
      lcd.setCursor(0, 0); //Erste Zeile anwählen
      lcd.print("Code eingeben:"); //Abfrage anzeigen
    } //Ende Codeabfrage
    dig1 =0; //Ziffern zurücksetzen
    dig2 =0; //Ziffern zurücksetzen
    dig3 =0; //Ziffern zurücksetzen

  } //Ende Taster gedrückt
}

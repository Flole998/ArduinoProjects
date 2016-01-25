// I got asked how many LCDs can possibly connected to an Arduino. This Sketch is able to control 5 LCDs.
#include <LiquidCrystal.h>

LiquidCrystal lcd(14,2,15,16,17,18);
LiquidCrystal lcd1(14,3,15,16,17,18);
LiquidCrystal lcd2(14,4,15,16,17,18);
LiquidCrystal lcd3(14,5,15,16,17,18);
LiquidCrystal lcd4(14,6,15,16,17,18);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Das ist Display1");
    lcd1.begin(16, 2);
  lcd1.print("Das ist Display2");
  
      lcd2.begin(16, 2);
  lcd2.print("Das ist Display3");
  
        lcd3.begin(16, 2);
  lcd3.print("Das ist Display4");
  
          lcd4.begin(16, 2);
  lcd4.print("Das ist Display5");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() );
    lcd1.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd1.print(millis());
  
      lcd2.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd2.print(millis());
  
        lcd3.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd3.print(millis());
  
          lcd4.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd4.print(millis());
}

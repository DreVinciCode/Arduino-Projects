#include <LiquidCrystal.h>
#include <IRremote.h>
IRsend irsend;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(5, 4, 9, 10, 11, 12);
const int ledPin = 13;

void setup()
{
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
}

void loop()
{
  digitalWrite(ledPin, HIGH);
  irsend.sendNEC(0xFFA25D, 32);
  lcd.setCursor(0,0);
  lcd.print("IRcode:");
  lcd.setCursor(0,1);
  lcd.print("  0xFFA25D      ");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("                ");
  digitalWrite(ledPin, LOW);
  delay(1000);
}

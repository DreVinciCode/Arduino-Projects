#include <LiquidCrystal.h>
#include "encoder.h"
#include <EEPROM.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
ENCODER encoder;
#define setKey 5
#define temPin  A0 //the thermistor attach to 
#define relayPin 6
#define relayLed 13
float upperTem = 0.00;
#define beta 4090 //the beta of the thermistor
#define resistance 10 //the value of the pull-down resistor
float hysteresis = 0.25;
void setup()
{
  pinMode(relayPin, OUTPUT);
  pinMode(relayLed, OUTPUT);
  digitalWrite(relayPin, HIGH); 
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("  Thermostatic  ");
  lcd.setCursor(0, 1);
  lcd.print("   water tank   ");
  encoder.Init(2, 3, 4); 
  pinMode(setKey, INPUT);
  upperTem = EEPROM.read(0);
  delay(1000);
}

void loop()
{
  if(digitalRead(setKey) == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    Set Mode    ");
    lcd.setCursor(0, 1);
    lcd.print("    start...    ");
    delay(500);
    lcd.clear();
    while(1)
    {          
      lcd.setCursor(0, 0);
      lcd.print("Adjust: ");
      float change = encoder.turnSettle();
      upperTem = upperTem + change;
      lcd.print(upperTem);
      if(encoder.pressed())
      {
        EEPROM.write(0, upperTem);
        delay(100);
        lcd.setCursor(0, 1);
        lcd.print("Upper Tem: ");
        lcd.print((float) EEPROM.read(0));
        delay(1000);
        lcd.clear();
        break;
      }
    }
  }
  else
  {
     //read thermistor value 
     long a = 1024 - analogRead(temPin);
     //the calculating formula of temperature
     float tempC = beta /(log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
     float tempF = tempC + 273.15;
     // Print a message of "Temp: "to the LCD.
     // set the cursor to column 0, line 0  
     lcd.setCursor(0, 0);
     lcd.print("Temp: ");
     // Print a centigrade temperature to the LCD.
     lcd.print(tempC);
     // Print the unit of the centigrade temperature to the LCD.
     lcd.print("  C");
     // set the cursor to column 0, line 1
     // (note: line 1 is the second row, since counting begins with 0):
     lcd.setCursor(0, 1);
     lcd.print("Fahr: ");
     // Print a Fahrenheit temperature to the LCD.
     lcd.print(tempF);
     // Print the unit of the Fahrenheit temperature to the LCD.
     lcd.print(" F");
     delay(100); //wait for 100 milliseconds 
     if(tempC > upperTem + hysteresis)
     {
       digitalWrite(relayPin, LOW); 
       digitalWrite(relayLed, LOW);
     }
     else if(tempC <= upperTem - hysteresis)
     {
       digitalWrite(relayPin, HIGH); 
       digitalWrite(relayLed, HIGH);
     }
   }
}


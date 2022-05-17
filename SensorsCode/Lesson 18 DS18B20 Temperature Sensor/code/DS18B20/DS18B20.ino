#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
LiquidCrystal lcd(4, 5,9, 10, 11, 12);

void setup(void)
{
  lcd.begin(16, 2);
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  // Start up the library
  sensors.begin();
}
void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  lcd.setCursor(0, 0);
  lcd.print("Tem: ");
  lcd.print(sensors.getTempCByIndex(0));//print the temperature on lcd1602
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Tem: ");
  lcd.print(sensors.getTempCByIndex(0) + 273.15);//print the temperature on lcd1602
  lcd.print(" F");
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensors.getTempCByIndex(0));  //print the temperature on serial monitor
}

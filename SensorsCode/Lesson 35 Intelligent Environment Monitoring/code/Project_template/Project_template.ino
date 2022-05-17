#include <IRremote.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>

LiquidCrystal lcd(12, 11,10, 9, 8, 7);
dht DHT;

const int irReceiverPin = 3;  
const int ledPin = 13;
#define ONE_WIRE_BUS 2  
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define DHT11_PIN 4
#define soundPin A0
#define lightPin A1
#define hallPin A2

IRrecv irrecv(irReceiverPin); 
decode_results results;   
float temValue = 0;
#define irDelay  300
int lightVal = 0;
int hallVal = 0;

void setup()
{
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);  
  irrecv.enableIRIn();  
  lcd.begin(16, 2);
  sensors.begin();  //DS18B20
}

void loop() 
{
  if (irrecv.decode(&results)) 
  {
    irrecv.resume();   
  }  
  delay(irDelay); 
  if(results.value == 0xFFA25D) 
  {
    Serial.println(results.value);
    while(1)
    {
      lcd.setCursor(0, 0);
      lcd.print("   Environment  ");
      lcd.setCursor(0,1);
      lcd.print("Monitor begin...");
      if (irrecv.decode(&results)) 
      {
          irrecv.resume();    
      } 
      delay(irDelay);
      if(results.value != 0xFFA25D && results.value != 0xFFFFFFFF)
      {
        Serial.println(results.value);
        break;
      }
    }
    while(1)
    {
      if(results.value == 0xFF30CF)  
      {
        lcd.clear();
        while(1)
        {
          lcd.setCursor(0, 0);
          lcd.print("     DS18B20    ");
          temValue = readTem();
          lcd.setCursor(0, 1);
          lcd.print("Tem: ");
          lcd.print(temValue);
          lcd.print(" C");
          if (irrecv.decode(&results)) 
          {
            irrecv.resume();    
          }
          delay(irDelay);
          if(results.value != 0xFF30CF && results.value != 0xFFFFFFFF)
          {
            break;
          }
        }
      }
      else if(results.value == 0xFF18E7) 
      {
        lcd.clear();
        while(1)
        {
          int chk = DHT.read11(DHT11_PIN);
          lcd.setCursor(0, 0);
          lcd.print("     DHT11      ");
          lcd.setCursor(0, 1);
          lcd.print("Hum: ");
          lcd.print(DHT.humidity,1);
          lcd.print(" %");
          if (irrecv.decode(&results)) 
          {
            irrecv.resume();   
          }
          delay(irDelay);
          if(results.value != 0xFF18E7 && results.value != 0xFFFFFFFF)
          {
            break;
          }
        }
      }
      else if(results.value == 0xFF7A85)  
      {
        lcd.clear();
        while(1)
        {
          lcd.setCursor(0, 0);
          lcd.print("   Big Sound    ");
          lcd.setCursor(0, 1);
          lcd.print("Sound: ");
          lcd.print(readSound());
          if (irrecv.decode(&results)) 
          {
            irrecv.resume();    
          }
          delay(irDelay);
          if(results.value != 0xFF7A85 && results.value != 0xFFFFFFFF)
          {
            break;
          }
        }
      }
      else if(results.value == 0xFF10EF)  
      {
        lcd.clear();
        while(1)
        {
          lightVal = readLight();
          lcd.setCursor(0, 0);
          lcd.print("  Light Sensor  ");
          lcd.setCursor(0, 1);
          lcd.print("Light: ");
          lcd.print(lightVal);
          if (irrecv.decode(&results)) 
          {
            irrecv.resume();    
          }
          delay(irDelay);
          if(results.value != 0xFF10EF && results.value != 0xFFFFFFFF)
          {
            break;
          }
        }
      }
      else if(results.value == 0xFF38C7)  
      {
        lcd.clear();
        while(1)
        {
          hallVal = analogRead(hallPin);
          hallVal = map(hallVal, 0, 1023, 0, 255);
          lcd.setCursor(0, 0);
          lcd.print("  Analog Hall   ");
          lcd.setCursor(0, 1);
          lcd.print("Magnetic: ");
          lcd.print(hallVal);
          if (irrecv.decode(&results)) 
          {
            irrecv.resume();    
          }
          delay(irDelay);
          if(results.value != 0xFF38C7 && results.value != 0xFFFFFFFF)
          {
            break;
          }
        }
      }
      else
      {
        lcd.clear();
        break;
      }
    }
  }
}

float readTem()
{
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

int readSound()
{
  int soundTemp[10];
  int soundMax = 0;
  for(int i = 0; i < 10; i ++)
  {
     soundTemp[i] = analogRead(soundPin);
     soundMax = max(soundMax, soundTemp[i]);
  } 
  return soundMax;
}

int readLight()
{
  int lightAverage,lightTemp[10];
  int lightMax = 0;
  int lightMin = 1024;
  for(int i = 0; i < 10; i ++)
  {
    lightTemp[i] = analogRead(lightPin);
    lightMax = max(lightMax, lightTemp[i]);
    lightMin = min(lightMin, lightTemp[i]);
  }
  lightAverage = (lightMax + lightMin)/2;
  lightAverage = map(lightAverage, 0, 1023, 0, 255);
  return lightAverage;
}

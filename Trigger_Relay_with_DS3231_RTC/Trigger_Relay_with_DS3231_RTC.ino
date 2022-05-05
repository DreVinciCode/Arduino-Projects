#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

int Relay = 4;

RTC_DS3231 rtc;

const int OnHour = 10;
const int OnMin = 03;
const int OffHour = 10;
const int OffMin = 04;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() 
{
  Serial.begin(9600);
  delay(3000);
  rtc.begin();
  if (! rtc.begin()) 
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) 
  {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE, BLACK);
  display.drawRect(117,25,3,3,WHITE);
  draw_text(0,25, "TEMPERATURE =", 1);
  draw_text(122, 25, "C", 1);
}

void draw_text(byte x_pos, byte y_pos, char *text, byte text_size) 
{
  display.setCursor(x_pos, y_pos);
  display.setTextSize(text_size);
  display.print(text);
  display.display();
}

void loop() 
{
  //t = rtc.getTime();
  DateTime now = rtc.now();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print(daysOfTheWeek[now.dayOfTheWeek()]);

  char currentDate [16];
  uint8_t thisDay, thisMonth;
  thisDay = now.day();
  thisMonth = now.month();
  
  sprintf(currentDate, "%02d/%02d/", thisDay, thisMonth);

  display.setTextSize(1);
  display.setCursor(62,0);
  display.print(currentDate);

  display.setTextSize(1);
  display.setCursor(102,0);
  display.print(now.year(), DEC);

  char buffer [16];
  uint8_t thisSec, thisMin, thisHour;
  thisSec = now.second();
  thisMin = now.minute();
  thisHour = now.hour();
  sprintf(buffer, "%02d:%02d:%02d", thisHour, thisMin, thisSec);
  display.setTextSize(2);
  display.setCursor(15,9);
  display.print(buffer);

  display.setTextSize(1);
  display.setCursor(82,25);
  display.print(rtc.getTemperature());
  display.display();

  
  if(t.hour == OnHour && t.min == OnMin)
  {
    digitalWrite(Relay,HIGH);
    Serial.println("LIGHT ON");  
  }
  else if(t.hour == OffHour && t.min == OffMin)
  {
    digitalWrite(Relay,LOW);
    Serial.println("LIGHT OFF");
  }
    
    
}

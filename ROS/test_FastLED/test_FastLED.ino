/*****************************
arduino_ros_robotstate_LED_STIRP.ino
SENSAR
Andre Cleaver
Tufts University
*****************************/

#include <FastLED.h>

#define LED_PIN 2
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];

float led_scale = 255.0 / NUM_LEDS;
bool messageRecieved;
bool initialState = true;
bool continuous_LED = false;

void RGB_LED_Off()
{
  for(int i=0;i<NUM_LEDS;i++)
  {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

void RGB_change_delay(float red_light_value, float green_light_value, float blue_light_value)
{
  for(int i=0;i<NUM_LEDS;i++)
  {
    leds[i] = CRGB(red_light_value,green_light_value,blue_light_value);
    FastLED.setBrightness(60);
    FastLED.show();
    delay(10);
  }
}

void Diminish()
{
  for(int i=0;i<NUM_LEDS;i++)
  {
    leds[i] = CRGB(255, 0,0);
    FastLED.setBrightness(i);
  }
  
}

void RGB_change_comet(float red_light_value, float green_light_value, float blue_light_value)
{
  for(int i=3;i<NUM_LEDS + 3;i++)
  {
      leds[i % NUM_LEDS] = CRGB(red_light_value,green_light_value,blue_light_value);
      leds[i-1 % NUM_LEDS] = CRGB(red_light_value,green_light_value,blue_light_value);
      leds[i-2 % NUM_LEDS] = CRGB(red_light_value,green_light_value,blue_light_value);
      leds[i-3 % NUM_LEDS] = CRGB::Black;   

      FastLED.setBrightness(60);
      FastLED.show();
      delay(20);  
  }
}

void RGB_Single_Ring(float red_light_value, float green_light_value, float blue_light_value)
{
   for(int i=0; i<=NUM_LEDS; i++)   
   {   
      leds[i] = CRGB(red_light_value,green_light_value,blue_light_value);
      FastLED.show();
      leds[i] = CRGB::Black;   
      delay(20);   
   }
}   

 

void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
}

void loop()
{  
  Diminish();
}

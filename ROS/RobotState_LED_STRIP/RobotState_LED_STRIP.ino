/*****************************
arduino_ros_robotstate_LED_STIRP.ino
SENSAR
Andre Cleaver
Tufts University
*****************************/

#include <FastLED.h>
#include <ros.h>
#include <std_msgs/ColorRGBA.h>

#define LED_PIN 2
#define NUM_LEDS 60
#define SCROLL_SPEED 50

CRGB leds[NUM_LEDS];
CRGBArray<NUM_LEDS> led_array;

ros::NodeHandle  nh;

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

void RGBA_action(float red_light_value, float green_light_value, float blue_light_value, float action_value)
{
  int action = (int)action_value;
  switch(action)
  {
    case 0: //Turn off
      RGB_LED_Off();
      break;
      
    case 1: //comet effect
      
      RGB_change_comet(red_light_value,green_light_value,blue_light_value);
      break;
      
    case 2: //Change all leds with delay
      RGB_change_delay(red_light_value,green_light_value,blue_light_value);
      break;
      
    default:
      break;
  }
  
  messageRecieved = false;
}

void RGBLEDcolorMessageReceiver( const std_msgs::ColorRGBA& color_msg)
{
   initialState = false;
   RGBA_action(color_msg.r, color_msg.g, color_msg.b, color_msg.a);
   messageRecieved = true;
}    
ros::Subscriber<std_msgs::ColorRGBA> colorSub("/SENSAR/robotstate_color", RGBLEDcolorMessageReceiver);

void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
  
  nh.initNode();
  nh.subscribe(colorSub);
}

void loop()
{  
   if(initialState)
   {
      RGB_change_comet(255,255,255);
   }

   nh.spinOnce();
}

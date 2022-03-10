/*****************************
arduino_ros_robotstate.ino
SENSAR
Andre Cleaver
Tufts University
*****************************/

#include <ros.h>
#include <std_msgs/ColorRGBA.h>

ros::NodeHandle  nh;

int red_light_pin = 11;
int green_light_pin = 10;
int blue_light_pin = 9;

void RGBLEDcolorMessageReceiver( const std_msgs::ColorRGBA& color_msg)
{
  RGB_color(color_msg.r, color_msg.g, color_msg.b);
}

void RGB_color(float red_light_value, float green_light_value, float blue_light_value)
{
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

ros::Subscriber<std_msgs::ColorRGBA> colorSub("/SENSAR/robotstate_color", RGBLEDcolorMessageReceiver);

void setup()
{
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(colorSub);

  RGB_color(255, 0, 0); // Start out red

}

void loop()
{  
  nh.spinOnce();
  delay(50);
}

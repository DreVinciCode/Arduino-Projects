/*****************************
arduino_ros_robotstate.ino
SENSAR
Andre Cleaver
Tufts University
*****************************/

#include <ros.h>
#include <std_msgs/ColorRGBA.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;
std_msgs::String str_msg;

char hello[13] = "hello world!";
int red_light_pin = 11;
int green_light_pin = 10;
int blue_light_pin = 9;

void messageCb( const std_msgs::Empty& toggle_msg)
{
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

void RGBLEDcolorMessage( const std_msgs::ColorRGBA& color_msg)
{
  RGB_color(color_msg.r, color_msg.g, color_msg.b);
}

void RGB_color(float red_light_value, float green_light_value, float blue_light_value)
{
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

ros::Publisher chatter("chatter", &str_msg);
ros::Subscriber<std_msgs::Empty> sub("toggle_led", messageCb);
ros::Subscriber<std_msgs::ColorRGBA> colorSub("/SENSAR/robotstate_color", RGBLEDcolorMessage);

void setup()
{
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
  nh.subscribe(colorSub);
}


void loop()
{  
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(500);
}

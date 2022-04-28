/*
 * Andre Cleaver
 * LED Strip PRoject
 * Tufts University
 * April 27, 2022
 * 
 * Example of ROS sub and pub with custom message
 */

#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/ColorRGBA.h>
#include <sensar_ros/SingleColorLED.h>

ros::NodeHandle  nh;

sensar_ros::SingleColorLED message;
ros::Publisher SingleColorLED("singleColorLED", &message);

void publishMessage()
{
  
  int value[5] = {1,2,4,8,16};
  std_msgs::Int16MultiArray testarray;
  testarray.data = value;
  testarray.data_length = 5;
  
  std_msgs::ColorRGBA ledColor;
  
  ledColor.r = 255;
  ledColor.g = 150;
  ledColor.b = 14;

  message.color = ledColor;
  message.repeating = true; 
  message.duration = 5.2;
  message.leds = value;
  message.leds_length = 5;
  

  SingleColorLED.publish(&message);
}

void singleColorLEDMessageReceiver(const sensar_ros::SingleColorLED led_msg)
{
    digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

ros::Subscriber<sensar_ros::SingleColorLED> ledSub("singleColorLED",  singleColorLEDMessageReceiver);

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(SingleColorLED);
  nh.subscribe(ledSub);
}

void loop()
{
  publishMessage();
  nh.spinOnce();
  delay(500);
}

/*
 * Andre Cleaver
 * Trigger_Relay_with_ROStopic.ino
 * April 17th, 2022
 * Control Relay state wity ROSTopic commands
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;

void EmptyMessageCallback( const std_msgs::Empty& toggle_msg)
{
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

void messageCb( const std_msgs::Bool& toggle_msg)
{
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

ros::Subscriber<std_msgs::Bool> sub("toggle_led1", messageCb);
ros::Subscriber<std_msgs::Empty> Empty_Sub("empty_1", EmptyMessageCallback);


std_msgs::String str_msg;
ros::Publisher chatter("chatter1", &str_msg);

char hello[13] = "hello world!";

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
  nh.subscribe(Empty_Sub);
}

void loop()
{
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(500);
}

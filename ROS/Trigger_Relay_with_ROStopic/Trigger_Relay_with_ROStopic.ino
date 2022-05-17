/*
 * Andre Cleaver
 * Trigger_Relay_with_ROStopic.ino
 * April 17th, 2022
 * Control Relay state wity ROSTopic commands
 */

#include <ros.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;

int Relay1 = 10;

void EmptyMessageCallback( const std_msgs::Empty& toggle_msg)
{
  digitalWrite(Relay1, HIGH-digitalRead(Relay1));   // Toggle Relay
}

ros::Subscriber<std_msgs::Empty> Empty_Sub1("AR_Device1", EmptyMessageCallback);
//ros::Subscriber<std_msgs::Empty> Empty_Sub2("AR_Device2", EmptyMessageCallback);
//ros::Subscriber<std_msgs::Empty> Empty_Sub3("AR_Device3", EmptyMessageCallback);


void setup()
{
  pinMode(Relay1, OUTPUT);
  nh.initNode();
  nh.subscribe(Empty_Sub1);
  //nh.subscribe(Empty_Sub2);
  //nh.subscribe(Empty_Sub3);

  digitalWrite(Relay1, LOW);

}

void loop()
{
  nh.spinOnce();
  delay(500);
}

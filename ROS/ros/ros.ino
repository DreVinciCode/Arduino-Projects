#include <ros.h>
#include <std_msgs/Int8.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;

std::msgs::String msg;

ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello";

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
}

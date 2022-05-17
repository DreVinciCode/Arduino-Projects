#include <DS3231.h>
#include <ros.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;
int Relay = 2;

DS3231  rtc(SDA, SCL);
Time t;

const int OnHour = 10;
const int OnMin = 03;
const int OffHour = 10;
const int OffMin = 04;

void EmptyMessageCallback( const std_msgs::Empty& toggle_msg)
{
  //digitalWrite(13, HIGH-digitalRead(13));  
  digitalWrite(Relay,HIGH-digitalRead(Relay));
}

ros::Subscriber<std_msgs::Empty> Empty_Sub("empty_1", EmptyMessageCallback);

void setup() {
  //Serial.begin(115200);
  nh.initNode();
  rtc.begin();
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, HIGH);
  nh.subscribe(Empty_Sub);

}

void loop() {
  t = rtc.getTime();
  Serial.print(t.hour);
  Serial.print(" hour(s), ");
  Serial.print(t.min);
  Serial.print(" minute(s)");
  Serial.println(" ");
  delay (1000);

  nh.spinOnce();
  if(t.hour == OnHour && t.min == OnMin){
    digitalWrite(Relay,HIGH);
    Serial.println("LIGHT ON");
    }
    
    else if(t.hour == OffHour && t.min == OffMin){
      digitalWrite(Relay,LOW);
      Serial.println("LIGHT OFF");
    }
}

const int analogInPin = A0;
const int digitalInPin = 8;
const int ledPin = 13;
#
const int mq2Pin = A1;
void setup()
{
  pinMode(digitalInPin,INPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int val;
  val=analogRead(mq2Pin);
  Serial.println(val);
  int analogVal = analogRead(analogInPin);
  boolean stat = digitalRead(digitalInPin);
  if(stat == HIGH & val > 58)
  { 
    digitalWrite(ledPin,HIGH);
    tone(3, 358);
    delay(100);
   }
   else
   {
     digitalWrite(ledPin,LOW);
     noTone(3);
   } 
}

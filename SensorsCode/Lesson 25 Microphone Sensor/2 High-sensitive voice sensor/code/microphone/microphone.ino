
const int ledPin = 13;
const int soundPin = A0;

void setup()
{
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int value = analogRead(soundPin);
  Serial.println(value);
  if(value > 25)
  {
    digitalWrite(ledPin,HIGH);
    delay(20000);
  }
  else
  {
    digitalWrite(ledPin,LOW);
  }
}

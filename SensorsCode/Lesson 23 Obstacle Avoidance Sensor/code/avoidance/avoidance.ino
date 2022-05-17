#define ledPin 13
#define avoidPin 8

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(avoidPin, INPUT);
}

void loop()
{
  int avoidVal = digitalRead(avoidPin);
  if(avoidVal == LOW)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
}

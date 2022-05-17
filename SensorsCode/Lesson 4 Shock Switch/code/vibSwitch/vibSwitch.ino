const int vibswPin = 8; //the Vibration Switch attach to 
const int ledPin = 13; //the led attach to
int val = 0; //initialize the variable val as 0
/******************************************/
void setup()
{
  pinMode(vibswPin,INPUT); //initialize vibration switch as an input
  pinMode(ledPin,OUTPUT); //initialize ledPin switch as an output
}
/*******************************************/
void loop()
{
  val = digitalRead(vibswPin); //read the value from vibration switch
  if(val == HIGH)  //without vibration signal
  {
    digitalWrite(ledPin,LOW); //turn off the led
  }
  else
  {
    digitalWrite(ledPin,HIGH); //turn on the led
  }
}
/*********************************************/

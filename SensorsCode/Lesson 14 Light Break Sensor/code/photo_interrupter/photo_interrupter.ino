/***************************************************/
const int ledPin = 13; //the number of the led pin
int val = 0; //variable to store the value from photo interrupter
/***************************************************/
void setup()
{
  pinMode(ledPin,OUTPUT); //initialize led as an output
  Serial.begin(9600);
  
}
/***************************************************/
void loop()
{
  val = analogRead(0);  //read the value from photo interrupter
  Serial.println(val);
  if(val > 400) //when interrupted
  {
    digitalWrite(ledPin,HIGH); //turn the led on
  }
  else
  {
    digitalWrite(ledPin,LOW); //turn the led off
  }
}
/******************************************************/

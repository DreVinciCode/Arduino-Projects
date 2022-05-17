int redPin = 11;    // select the pin for the red LED
int greenPin = 10;    // select the pin for the blueLED
int val = 0;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(9600);
}
/******************************************************/
void loop() 
{
  for(val=255; val>0; val--)
  {
   analogWrite(redPin, val);
   analogWrite(greenPin, 255-val);
   Serial.println(val, DEC);
   delay(15); 
  }
for(val=0; val<255; val++)
  {
   analogWrite(redPin, val);
   analogWrite(greenPin, 255-val);
   Serial.println(val, DEC);
   delay(15); 
  }
}
/********************************************************/

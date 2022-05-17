const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the miniReed pin as an input:
  pinMode(buttonPin, INPUT);     
}

void loop(){
  // read the state of the mini reed :
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {     
    // turn LED off:    
    digitalWrite(ledPin, LOW);  
  } 
  else {
    // turn LED on:
    digitalWrite(ledPin, HIGH); 
  }
}

const int buttonPin = 2;     // the number of the tilt switch pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the tilt switch status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the tilt switch pin as an input:
  pinMode(buttonPin, INPUT);     
}

void loop(){
  // read the state of the tilt switch value:
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}

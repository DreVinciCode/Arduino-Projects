 
int Relay1 = 13;
int Relay2 = 7;
int Relay3 = 4;
int Relay4 = 2;

void toggleRelay1()
{
    digitalWrite(Relay1, HIGH-digitalRead(Relay1));   // Toggle input 
    digitalWrite(Relay2, HIGH-digitalRead(Relay2));   // Toggle input 
    digitalWrite(Relay3, HIGH-digitalRead(Relay3));   // Toggle input 
    digitalWrite(Relay4, HIGH-digitalRead(Relay4));   // Toggle input 
}

void setup() 
{
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);

  digitalWrite(Relay1, LOW);
  digitalWrite(Relay2, LOW);
  digitalWrite(Relay3, LOW);
  digitalWrite(Relay3, LOW);
  
}

void loop() 
{
  toggleRelay1();
  delay (1000);
}

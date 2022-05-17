/*******************************************/
const int buzzerPin = 3;//the buzzer pin attach to
int fre;//set the variable to store the frequence value
/*******************************************/
void setup()
{
  pinMode(buzzerPin,OUTPUT);
}
/*******************************************/ 
void loop()
{
  for(int i = 200;i <= 800;i++)   //frequence loop from 200 to 800
  {
    tone(3,i);   //turn the buzzer on
    delay(5);    //wait for 5 milliseconds   
  }
  delay(4000);   //wait for 4 seconds on highest frequence
  for(int i = 800;i >= 200;i--)//frequence loop from 800 downto 200
  {
    tone(3,i);
    delay(10);
  }
}


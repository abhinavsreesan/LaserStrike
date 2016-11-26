#define highLed A4
#define flashBtn A3
#define timeForFlash 2000
#define timeFlashed 4000
int read=0;
int flag=0;
//long time=0;
//int debounce=200;
void setup() {
  // put your setup code here, to run once:
  pinMode(flashBtn,INPUT);
  pinMode(highLed,OUTPUT);
  digitalWrite(flashBtn,HIGH);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  read=digitalRead(flashBtn);
  if(read==LOW && flag==0)
    {
      delay(2000);
      digitalWrite(highLed,HIGH);
      delay(4000);
      digitalWrite(highLed,LOW);
      flag=1;
    }
}

#include <IRLib.h>0
#define ldrPin A2
#define highLed A4
#define btn A0
#define flashBtn A3
#define ldrPin A5
#define timeForFlash 2000
#define timeFlashed 4000
#define ldrThreshold 200
#define buzz A1
int RECV_PIN = 2;
int flag=0;
int btncnt=0;//no. of bullets
int read2=0;
long time=0;
int read;
int disableSend=0;
long l=0;

int hpin=4;//health bargraph start count 
long debounce=200;

int dth=0;
int led=1;
long t1=0;
int t3=0;


IRrecv My_Receiver(RECV_PIN);
IRsend My_Sender;

IRdecode My_Decoder;
unsigned int Buffer[RAWBUF];
int oldValue=0;
void setup()
{
  Serial.begin(9600);
  pinMode(flashBtn,INPUT);//flash button
  pinMode(highLed,OUTPUT);//flash led
  pinMode(ldrPin,OUTPUT);
  pinMode(flashBtn,LOW);
  digitalWrite(flashBtn,HIGH);
  digitalWrite(highLed,LOW);

  //trigger
  pinMode(btn,INPUT);
  pinMode(A1,OUTPUT);
  digitalWrite(A1,LOW);
  oldValue=analogRead(ldrPin);
  //healthbar
  for(int i=4;i<8;i++)
  {
    pinMode(i,OUTPUT);
  }
  for(int i=4;i<9;i++)
  {
    digitalWrite(i,HIGH);
  }
  
  //bulletcount

  
  My_Receiver.enableIRIn(); // Start the receiver
  My_Decoder.UseExtnBuf(Buffer);
}

void checkForInput(){
    if (My_Receiver.GetResults(&My_Decoder)) {
    //Restart the receiver so it can be capturing another code
    //while we are working on decoding this one.
    My_Decoder.decode();
    TIMSK2 = 0;
    if(My_Decoder.value == 3021 && dth<10)
    {
    dth++;
    digitalWrite(A1,HIGH);
    delay(500);
    digitalWrite(A1,LOW);
    Serial.println("inside receiver loop");
    if(led%2==0)
    {
    digitalWrite(hpin,LOW);
    if(hpin<9)
    {
      hpin++;
    }
    }
    led++;
    Serial.println(My_Decoder.value,HEX);
    delay(100); 
    }
    My_Receiver.resume();
    My_Receiver.enableIRIn();
  //  My_Receiver.resume();
  }
 }
   
   void loop() 
   {
   read2=digitalRead(flashBtn);
   /*if(read2==LOW){
    if(flag==0){
      delay(50);
      if(digitalRead(flashBtn)==LOW){
      digitalWrite(highLed,HIGH);
      t1=millis();
      flag=1;
      }
    }
   }
   int timePassedLed=millis()-t1;
   if(timePassedLed>=timeForFlash)
   digitalWrite(highLed,LOW);
  int ldr=analogRead(ldrPin);
  if(ldr>=ldrThreshold){
    disableSend=1;
    t3=millis();
    }
    int timeLdr=millis()-t3;
    if(timeLdr>=timeFlashed)
    disableSend=0;*/
 
    read=digitalRead(btn);
    if(read==LOW && millis()-time > debounce)
    {
    
    //send a code  every time a character is received from the serial port
    //Sony, DVD power A8BCA
    //if(!disableSend)
    if(btncnt<50)
    {
      Serial.println("send loop");
      My_Sender.send(RC5,0xbcb,20);//data to be sent
      btncnt++;
     }
     My_Receiver.enableIRIn();
 
    checkForInput();
    My_Receiver.enableIRIn();
    time=millis();
    }
    checkForInput();
}

//LASER TAG MARK 5
/*CONNECTIONS
 * TRIGGER A0
 * Receive pin 2
 * Transmit pin 3
 * Buzzer A1
 */
 
/*LCD DISPLAY  
 *Rs pin 13
 *Enable pin 12
 *D4 pin 7  
 *D5 pin 8
 *D6 pin 9
 *D7 pin 10
 *R/W to GND
 *led+&- to +5V and ground
 */

#include <IRLib.h>
#include <LiquidCrystal.h>
#define ldrPin A2
#define highLed A4
#define btn A0
#define flashBtn A3
#define ldrPin A5
#define timeForFlash 2000
#define timeFlashed 4000
#define ldrThreshold 200
#define buzz A1
#define estimate -4
int rumble_time=0;
int RECV_PIN = 2;
int flag=0;
int btncnt=0;//no. of bullets
int read2=0;
long time=0;
int read;
int disableSend=0;
long l=0;
LiquidCrystal lcd(12,11,7,8,9,10);
long debounce=200;
int dth=0;
int led=1;
long t1=0;
int t3=0;
int rumble=5;
int flag1=0;
int oldValue=0;
int ttime=0;

IRrecv My_Receiver(RECV_PIN);
IRsend My_Sender;

IRdecode My_Decoder;
unsigned int Buffer[RAWBUF];
void setup()
{
  Serial.begin(9600);
  //Flashang
  pinMode(flashBtn,INPUT);//flash button
  pinMode(highLed,OUTPUT);//flash led
  pinMode(ldrPin,OUTPUT);//
  pinMode(flashBtn,LOW);
  digitalWrite(flashBtn,HIGH);
  digitalWrite(highLed,LOW);

  //LCD
   lcd.begin(16, 2);

  //Rumble
  pinMode(rumble,OUTPUT); 
  digitalWrite(rumble,LOW);

  //trigger
  pinMode(btn,INPUT);
  pinMode(A1,OUTPUT);
  digitalWrite(A1,LOW);
  digitalWrite(btn,HIGH); 
  oldValue=analogRead(ldrPin);
  My_Receiver.enableIRIn(); // Start the receiver
  My_Decoder.UseExtnBuf(Buffer);
}

void checkForInput(){
    if (My_Receiver.GetResults(&My_Decoder)) {
    My_Decoder.decode();
    TIMSK2 = 0;
    //Value 
    if(My_Decoder.value == 3021 && dth<20)
    {
    if(led%4==0)
    {
      dth++;
    }
    led++;
    digitalWrite(A1,HIGH);
    delay(500);
    digitalWrite(A1,LOW);
    Serial.println("inside receiver loop");
    Serial.println(My_Decoder.value,HEX);
    delay(100); 
    }
    My_Receiver.resume();
    My_Receiver.enableIRIn();
  //  My_Receiver.resume();
  }
 }
   
void loop()
{  if(dth<20)
  {
    lcd.setCursor(2,0);
    lcd.print("RED TEAM");
    lcd.setCursor(0,1);
    lcd.print("AMMO:");
    lcd.setCursor(5,1);
    if((90-btncnt)>=10)
    {lcd.print((500-btncnt));}
    else
     if((500-btncnt)<10)
     {lcd.print("0");
      lcd.setCursor(6,1);
      lcd.print((500-btncnt));
     } 
    lcd.setCursor(9,1);
    lcd.print("LIFE:");
    lcd.setCursor(13,1);
    if((20-dth)>=10)
    {
    lcd.print((20-dth));
    }
    else
     if((20-dth)<10)
     {
      lcd.print("0");
      lcd.setCursor(14,1);
      lcd.print((20-dth));   
     }
    }
   if(dth>=20)
   {
   lcd.clear();
   lcd.setCursor(2,0);
   flag1==1; 
   } 
  
  /*FLASH
  int newValue=analogRead(A5);
  //Serial.println(newValue);
  int diff=newValue-oldValue;
  //Serial.print(diff);Serial.print("  ");
  Serial.println(newValue);
  oldValue=newValue;
  if(diff<=estimate)
  Serial.println("change detected");
  delay(200);*/

  
  read=digitalRead(btn);
  if(read==LOW && millis()-time > debounce)
  {
  //if(!disableSend)
  if(btncnt<500)
  {
    Serial.println("send loop");
    My_Sender.send(RC5,0xbcb,20);//data to be sent
    digitalWrite(rumble,HIGH);
    rumble_time=millis();
    btncnt++;
   }
  My_Receiver.enableIRIn();
  checkForInput();
  My_Receiver.enableIRIn();
  time=millis();
  if(flag1==1)
  {lcd.print("GAME OVER!!!");
  }
  }
  checkForInput();
}

#include <IRLib.h>
 
IRsend My_Sender;
int MAGZINE=30;
void setup()
{
  pinMode(6,INPUT);
 // Serial.begin(9600);
}
 
void loop() {
 // digitalWrite(3,HIGH);
  if (digitalRead(6)==LOW && MAGZINE>0) {
    //send a code every time a character is received from the serial port
    //Sony DVD power A8BCA
    My_Sender.send(RC5,0xffeeb, 20);
    MAGZINE--;
    delay(50);
  }
}

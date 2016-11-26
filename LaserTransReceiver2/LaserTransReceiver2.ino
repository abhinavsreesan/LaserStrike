/* Example program for from IRLib – an Arduino library for infrared encoding and decoding
 * Version 1.3   January 2014
 * Copyright 2014 by Chris Young http://cyborg5.com
 * Based on original example sketch for IRremuote library 
 * Version 0.11 September, 2009
 * Copyright 2009 Ken Shirriff
 * http://www.righto.com/
 */
/*
 * IRLib: IRrecvDump - dump details of IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 */

#include <IRLib.h>

int RECV_PIN = 2;
int btn=A0;
int inPin = A0; 
int hpin=4;//loopvariable
long time=0;
int read;
long debounce=200;

IRrecv My_Receiver(RECV_PIN);
IRsend My_Sender;

IRdecode My_Decoder;
unsigned int Buffer[RAWBUF];

void setup()
{
  Serial.begin(9600);
  pinMode(btn,INPUT);
  My_Receiver.enableIRIn(); // Start the receiver
  My_Decoder.UseExtnBuf(Buffer);
  for(int i=4;i<=14;i++)
  {
     pinMode(i,OUTPUT);
  }
  for(int i=4;i<=14;i++)
  {
     digitalWrite(i,HIGH);
  }
}

void checkForInput(){
    if (My_Receiver.GetResults(&My_Decoder)) {
    Serial.println("inside receiver loop");
    //Restart the receiver so it can be capturing another code
    //while we are working on decoding this one.
     
    My_Decoder.decode();
    My_Receiver.resume();
    TIMSK2 = 0;  
    //My_Decoder.DumpResults();
    if(My_Decoder.value==0xbcb)
    {
    Serial.println(My_Decoder.value,HEX);
    delay(100);
    digitalWrite(hpin,LOW);
    if(hpin<15)
    {
      hpin++;
    }} 
    My_Receiver.enableIRIn();
  //  My_Receiver.resume();
  }
  
  }
void loop() {

  
  //if (Serial.read() != -1) {
    read=digitalRead(btn);
    if(read==LOW && millis()-time > debounce)
    {
    Serial.println("send loop");
    //send a code  every time a character is received from the serial port
    //Sony DVD power A8BCA
    My_Sender.send(RC5,0xa8bcb, 20);
    My_Receiver.enableIRIn();
    checkForInput();
    My_Receiver.enableIRIn();
    time=millis();
  }
  checkForInput();
  
}








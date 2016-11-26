#include <IRLib.h>
#define interruptPin 2
//Create a receiver object to listen on pin 11
IRrecv My_Receiver(2);


//Create a decoder object
IRdecode My_Decoder;

void setup()
{
  Serial.begin(9600);

  My_Receiver.enableIRIn(); // Start the receiver
  pinMode(13,HIGH);
}

  
void loop() {
   if (My_Receiver.GetResults(&My_Decoder)) {
    My_Decoder.decode();    //Decode the data
    if(My_Decoder.value!=0)
      {
        digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW); 
      }
    Serial.println(My_Decoder.value,HEX);
    //My_Decoder.DumpResults(); //Show the results on serial monitor
    My_Receiver.resume();    //Restart the receiver
  
   } 
  }


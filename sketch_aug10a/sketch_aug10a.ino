int i=2;
int buttonState = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, HIGH);   
  digitalWrite(3, HIGH);
  digitalWrite(1, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState=digitalRead(1);
  Serial.println(buttonState);
  if(digitalRead==HIGH)
    {digitalWrite(i,LOW);
     i++;
    }     
}

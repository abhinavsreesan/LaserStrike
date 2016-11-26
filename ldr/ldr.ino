#define ldrPin A5
#define estimate -4
int oldValue=0;
void setup() {
  Serial.begin(9600);
  pinMode(A5,INPUT);
  oldValue=analogRead(A5);
  // put your setup code here, to run once:

}

void loop() {
  int newValue=analogRead(A5);
  //Serial.println(newValue);
  int diff=newValue-oldValue;
  //Serial.print(diff);Serial.print("  ");
  Serial.println(newValue);
  oldValue=newValue;
  if(diff<=estimate)
  Serial.println("change detected");
  delay(200);
  // put your main code here, to run repeatedly:

}

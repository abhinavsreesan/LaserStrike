  /*
 * 1-2,6
 * 2-3,2,11,8,10
 * 3-3,2,11,6,10
 * 4-7,11,2,6
 * 5-3,7,11,6,10
 * 6-7,8,10,6,11
 * 7-3,2,6
 * 8-3,2,6,10,8,7,11
 * 9-3,2,11,7,6,10
 * 0-3,2,6,10,8,7
 */
#define buzz A2
int a,b,c,d,e,f,g,h,one,two,three,dp,t1;
int flag,t,minute,second0,second1,time0=0,tBuzz=1000;
int read=0;
int read2=0;
int btn=A0;
int dbtn=A1;
int dbtnFlag=1;
int dbtnTime=0;
int time1=0;
int debounce=200;
int f1=0;
int dflag=0;
int buzzTime=700;
int tempBuzz;
int dbflg=0;
int eflag=0;

void setup() {
  minute=1;
  second0=9;
  second1=5;
  
 pinMode(buzz,OUTPUT);
 for(int i=1;i<=12;i++)
 {
  pinMode(i,OUTPUT);
  digitalWrite(i,LOW);
  pinMode(buzz,OUTPUT);
  digitalWrite(buzz,LOW);
  t=millis();
 }
 //Serial.begin(9600);
 sevenSegInit(1,2,3,4,5,6,7,8,9,10,11,12);
 time0=millis();
 pinMode(btn,INPUT);
 digitalWrite(btn,HIGH);
 pinMode(dbtn,INPUT);
 digitalWrite(dbtn,HIGH);
}
int sevenSegInit(int one1,int a1,int f1,int two1,int three1,int b1,int e1,int d1,int nc,int c1,int g1,int h1){
  one=one1;
  two=two1;
  three=three1;
  a=a1;b=b1;c=c1;d=d1;e=e1;f=f1;g=g1;h=h1;
  dp=nc;
  }
int reset()
{
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,LOW);
  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
  digitalWrite(h,LOW);
  digitalWrite(one,HIGH);
  digitalWrite(two,HIGH);
  digitalWrite(three,HIGH);
  digitalWrite(dp,LOW);
  return 0;
}
void disp(int i,int digit)
{
  //digitalWrite(h,HIGH);
  //digitalWrite(1,LOW);
  switch(digit)
  {
    case 1:digitalWrite(one,LOW);
           digitalWrite(9,HIGH);
            break;
    case 2:digitalWrite(two,LOW);
           digitalWrite(9,LOW);
           break;
    case 3:digitalWrite(three,LOW);
           digitalWrite(9,LOW);
           break;
    }
  digitalWrite(digit,LOW);
  switch(i)
  {
    case 1:digitalWrite(b,HIGH);
           digitalWrite(c,HIGH);
           break;
           
    case 2:digitalWrite(a,HIGH);
           digitalWrite(b,HIGH);
           digitalWrite(g,HIGH);
           digitalWrite(e,HIGH);
           digitalWrite(d,HIGH);
           break;
           
    case 3:digitalWrite(a,HIGH);
          digitalWrite(b,HIGH);
          digitalWrite(g,HIGH);
          digitalWrite(c,HIGH);
          digitalWrite(d,HIGH);
          break;
          
    case 4:digitalWrite(f,HIGH);
           digitalWrite(g,HIGH);
           digitalWrite(b,HIGH);
           digitalWrite(c,HIGH);
           break;
           
    case 5:digitalWrite(a,HIGH);
           digitalWrite(f,HIGH);
           digitalWrite(g,HIGH);
           digitalWrite(c,HIGH);
           digitalWrite(d,HIGH);
           break;
           
    case 6:digitalWrite(a,HIGH);
          digitalWrite(f,HIGH);
          digitalWrite(e,HIGH);
          digitalWrite(d,HIGH);
          digitalWrite(c,HIGH);
          digitalWrite(g,HIGH);
          break;
          
    case 7:digitalWrite(a,HIGH);
          digitalWrite(b,HIGH);
          digitalWrite(c,HIGH);
          break;
          
    case 8:digitalWrite(a,HIGH);
           digitalWrite(b,HIGH);
           digitalWrite(c,HIGH);
           digitalWrite(d,HIGH);
           digitalWrite(e,HIGH);
           digitalWrite(f,HIGH);
           digitalWrite(g,HIGH);
           break;
           
    case 9:digitalWrite(a,HIGH);
          digitalWrite(b,HIGH);
          digitalWrite(c,HIGH);
          digitalWrite(d,HIGH);
          digitalWrite(f,HIGH);
          digitalWrite(g,HIGH);
          break;
          
    case 0:digitalWrite(a,HIGH);
          digitalWrite(b,HIGH);
          digitalWrite(c,HIGH);
          digitalWrite(d,HIGH);
          digitalWrite(e,HIGH);
          digitalWrite(f,HIGH);
          break;
  }
}

void change_digital(){
  if(flag==1){
    digitalWrite(buzz,LOW);
    flag=0;
    }
  else {
  digitalWrite(buzz,HIGH);
  flag=1;
  }
}

void loop() {
  //Serial.println(buzzTime);
  read=digitalRead(btn);
  read2=digitalRead(dbtn);
    
   //buzzer
   if(minute==1 && second1<=5 && second1>3)
    {
      buzzTime=700;
    }

    else if(minute==0 && second1<=3 && second1>2)
    {
      buzzTime=500;
    }

    else if(minute ==0 && second1<=2 && second1>1)
    {
      buzzTime=300;
    }
    
    else if(minute==0 && second1==1)
    {
      buzzTime=50;
    }

    else if(minute==0 && second1==0 && second0>0)
    {
      buzzTime=50;
    }
    else if(minute<=0 && second1==0 && second0==0){
    buzzTime=0;
    }
    if(eflag==1)
    {
      digitalWrite(buzz,HIGH);
      
    }
    int a=millis()-tempBuzz;
  if(a>buzzTime && f1==1 )
  {
   change_digital();
   //Serial.println("checkk hua");
    tempBuzz=millis();
  }
  
    if(read==LOW)
    {
      f1=1;
    }
  if(read2==LOW){
    if(dbtnFlag==1){
    dbtnFlag=0;
    time1=millis();
    }
    
    if(dbtnFlag==0){
      dbtnTime=millis()-time1;
      
      if(dbtnTime>4999){
        dflag=1;
        dbflg=1;
        }
      }
      
  }
  if(read2==HIGH){
    dbtnFlag=1;
    }
  if(f1==1)
  {  
  if(flag==0){
  disp(minute,1);
  reset();
  disp(second1,2);
  reset();
  disp(second0,3);
  reset();
  }
  else
  reset();
  t=millis()-time0;
/*
  if(t>500){
  flag=0;
  }
  else {
  flag=1;
  }
  */
  if(dflag==0 && eflag==0)
  {
  if(t>=1000){  
    second0--;
    if(second0<0)
    {
      second1--;
      second0=9;
      if(second1<0){
        minute--;
        second1=5;
        if(minute<0)
        {
        eflag=1;
        second1=0;
        second0=0; 
        }       
        }
      }
      time0=millis();
    }
    }
  }
  if(dbflg==1)
  {
    digitalWrite(buzz,LOW);
  }
 }

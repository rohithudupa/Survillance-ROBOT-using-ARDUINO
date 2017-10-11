// Include the servo motor library
#include<Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial xbee(10, 11);
char buf;
//define pin numbers used for motors
int pir=21;
 const int m1=6;
 const int m2=7;
 const int m3=8;
 const int m4=9;
 const int gaspin=A6;
 
//define pin numbers used for ultrasonic sensor
 const int trig=4;
 const int echo=3;
//define name of the servo
Servo myservo;
Servo cam;
long distance,left_dist, right_dist,t,t1,t2;
void setup() {
//define pin number for servo


  myservo.attach(2);
  cam.attach(12);
 xbee.begin(9600);
 Serial.begin(9600);
//define pinmodes of declared pin numbers
 pinMode(m1, OUTPUT);
 pinMode(m2, OUTPUT);
 pinMode(m3, OUTPUT);
 pinMode(m4, OUTPUT);
 pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
pinMode(gaspin,INPUT);
pinMode(pir,INPUT);
for(int i=0;i<=180;i++){
  cam.write(i);
  delay(10);
  if(i==180){
    for(int i=180;i>=0;i--){
      cam.write(i);
      delay(10);// put your main code here, to run repeatedly:
    }
  }
 }
//delay isto set up ultrasonic sensor for accurate measurement
myservo.write(90);
cam.write(90);
delay(1000);
}

void loop() {
 //calculation distance of obstracle in front ways
if(analogRead(A6)>750){
  xbee.write('h');
  delay(1000);}
  else if(digitalRead(21)==HIGH){
    xbee.write('m');
    delay(1000);
  }
  else if(analogRead(A6)<=750 && digitalRead(21)== LOW){
xbee.write('l');
delay(1000);}

if(xbee.available()==0){
   
myservo.write(90);
cam.write(90);
digitalWrite(trig,LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);

t=pulseIn(echo,HIGH);
distance=(t/2)/29.1;

if(distance>10)//no obstracle
   farward();
if(distance<=10)//there is an obstracle
{
  halt();
delay(500);
findroute();//finds a route free of obstracle
}
}
while(xbee.available()>0)
{buf=xbee.read();
if(buf=='f')
farward();
else if(buf=='b')
backward();
else if(buf=='l')
left();
else if(buf=='r')
right();
else if(buf=='s')
halt();
delay(200);}
}
void findroute()
{//to calculate distance of obstracle along side ways
 myservo.write(0);//look right
delay(700);
  digitalWrite(trig,LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);

t1=pulseIn(echo,HIGH);
right_dist=(t1/2)/29.1;
delay(600);
myservo.write(180);//look left
delay(700);
digitalWrite(trig,LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);

t2=pulseIn(echo,HIGH);
left_dist=(t2/2)/29.1;
delay(600);
myservo.write(90);
  if(left_dist>right_dist & left_dist>15)
    go_left();
  if(right_dist>left_dist & right_dist>15)
    go_right();
  if(right_dist<=15 & left_dist<=15)
  {backward();
  delay(3000);
 halt();
findroute();}
  return 0;
}

void farward(void)
/*this code depends on the motor driver connection and pin assignment.
should be verified and tested before employment*/
{  digitalWrite(m1,LOW);
 digitalWrite(m2,HIGH);
 digitalWrite(m3,HIGH);
 digitalWrite(m4,LOW);
 return 0;}
 void backward(void)
 {  /*this code depends on the motor driver connection and pin assignment.
should be verified and tested before employment*/
digitalWrite(m2,LOW);
 digitalWrite(m1,HIGH);
 digitalWrite(m4,HIGH);
 digitalWrite(m3,LOW);
 return 0;}
 void halt(void)
 { /*this code depends on the motor driver connection and pin assignment.
should be verified and tested before employment*/
digitalWrite(m2,LOW);
 digitalWrite(m1,LOW);
 digitalWrite(m4,LOW);
 digitalWrite(m3,LOW);
 return 0;
 }
 void go_left(void){/*this code depends on the motor driver connection and pin assignment.
should be verified and tested before employment*/
   digitalWrite(m2,LOW);                                                                                                                                                                                                                                                                            
 digitalWrite(m1,HIGH);
 digitalWrite(m3,HIGH);
 digitalWrite(m4,LOW);
 delay(800);
 return 0;}
 void left(void){/*this code depends on the motor driver connection and pin assignment.
should be verified and tested before employment*/
   digitalWrite(m2,LOW);                                                                                                                                                                                                                                                                            
 digitalWrite(m1,HIGH);
 digitalWrite(m3,HIGH);
 digitalWrite(m4,LOW);
 return 0;}
 void go_right(void)
/*this code depends on the motor driver connection and pin assignment.
should be verified and tested before employment*/
{
   digitalWrite(m2,HIGH);
 digitalWrite(m1,LOW);
 digitalWrite(m3,LOW);
 digitalWrite(m4,HIGH);
 delay(800);
 return 0;}
 void right(void)
/*this code depends on the motor driver connection and pin assignment.
should be verified and tested before employment*/
{
   digitalWrite(m2,HIGH);
 digitalWrite(m1,LOW);
 digitalWrite(m3,LOW);
 digitalWrite(m4,HIGH);
 return 0;}


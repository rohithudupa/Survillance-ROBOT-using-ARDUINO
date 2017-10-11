#include <SoftwareSerial.h>
SoftwareSerial xbee(10, 11);
int x=A1;
char buf;
int gas=6;
int motion=7;
int y=A2;// RX, TX
void setup() {
Serial.begin(9600);
xbee.begin(9600);// put your setup code here, to run once:
pinMode(gas,OUTPUT);
pinMode(motion,OUTPUT);
}

void loop() {
  while(xbee.available()){
    buf=xbee.read();
    if(buf=='h'){
     digitalWrite(gas,HIGH);
    }
    if(buf=='m'){
      digitalWrite(motion,HIGH);
    }
   else if(buf=='l'){
    digitalWrite(gas,LOW);
    digitalWrite(motion,LOW);
   }
  }
  int xval=0;
  int yval=0;
  xval=analogRead(x);
  yval=analogRead(y);
 
  if(xval<300)
  xbee.write('b');// put your main code here, to run repeatedly:
 else if(xval>700)
  xbee.write('f');
  else if(yval<300)
  xbee.write('l');
  else if(yval>700)
  xbee.write('r');
  else
  xbee.write('s');
  delay(1000);}


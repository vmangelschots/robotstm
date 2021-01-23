#include <Arduino.h>
#include <Servo.h>




  Servo channels[8];
  PinName channelpins[8]{
    PA_2,
    PA_3,
    PA_1,
    PB_0,
    PA_0,
    PB_1,
    PA_7,
    PA_11
  };
  int pos = 0;

void setup() {
  Serial.begin(9600);
  uint8_t index;
  
  for(int i = 0; i<8;i++){
    Serial.print("setting up servo: ");
    Serial.print(i);
    index = channels[i].attach(channelpins[i]);
    Serial.print(" index: ");
    Serial.println(index);

  }

  pinMode(PA_8,OUTPUT);
  pinMode(PA_4,OUTPUT);
  pinMode(PA_5,OUTPUT);
  pinMode(PA_6,OUTPUT);
  pinMode(PC_6,OUTPUT);
  pinMode(PC_7,OUTPUT);
  pinMode(PC_8,OUTPUT);
}

void loop() {
    digitalWrite(PA_8,HIGH);
    //  digitalWrite(PA_4,HIGH);
    //  digitalWrite(PA_5,LOW);
    //  digitalWrite(PC_6,HIGH);
    //  digitalWrite(PC_8,LOW);
     //analogWrite(PA_6,100);
     //analogWrite(PC_7,100);
  delay(1000);
 
  digitalWrite(PA_8,LOW);
    //  digitalWrite(PA_4,LOW);
    //  digitalWrite(PA_5,HIGH);
    //  digitalWrite(PC_6,LOW);
    //  digitalWrite(PC_8,HIGH);
     //analogWrite(PA_6,100);
     //analogWrite(PC_7,100);
  delay(1000);
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
  for(int i = 0; i<8;i++){
    channels[i].write(pos);
  }
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  for(int i = 0; i<8;i++){
    channels[i].write(pos);
  }              // tell servo to go to position in variable 'pos'
    delay(15);           
  //put your main code here, to run repeatedly:
  }
}
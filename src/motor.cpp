#include "motor.h"

void Motor::stop(){
    digitalWrite(this->I1,LOW);
    digitalWrite(this->I2,LOW);
    digitalWrite(this->E,LOW);
}

Motor::Motor(PinName I1,PinName I2,PinName E){
    this->I1 = I1;
    this->I2 = I2;
    this->E = E;
    pinMode(I1,OUTPUT);
    pinMode(I2,OUTPUT);
    pinMode(E,OUTPUT);
    digitalWrite(I1,LOW);
    digitalWrite(I2,LOW);
    digitalWrite(E,LOW);
}

void Motor::setPos(int pos){
  if(pos==128){
      this->stop();
  }
  else{
    int motorpos = abs(pos-128); 
    analogWrite(this->E,motorpos*2);
    if(pos>128){
      digitalWrite(I1,HIGH);
      digitalWrite(I2,LOW);
    }
    else{
      digitalWrite(I1,LOW);
      digitalWrite(I2,HIGH);
    }
  }
}
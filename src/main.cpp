#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include "motor.h"

  Servo channels[10]; // contains the 8 servo channel values and 2 motor values 

  /*This array contains the pins connected to the servo channels*/
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

int pos[9];

Motor M1 = Motor(PA_4,PA_5,PA_6);
Motor M2 = Motor(PC_6,PC_8,PC_7);


void receiveEventdf(int howMany)
{
  char command;
  while(Wire.available()){
    command = Wire.read();
    if(command=='S'){
      for(int i = 0; i< 9; i++){
        pos[i] = Wire.read();
      }
    }
    else{
      command = Wire.read();
    }
  }
}



void setup() {
  /*setup serial*/
  Serial.begin(115200);
  Serial.println("Starting robot stm");
  /*set the resolution for the PWM to 8*/
  analogWriteResolution(8);
  uint8_t index;

  for(int i = 0; i<8;i++){
    Serial.print("setting up servo: ");
    Serial.print(i);
    index = channels[i].attach(channelpins[i]);
   }
  /*setup one wire (I2C)*/
  Wire.setSCL(PB_6);
  Wire.setSDA(PB_7);
  Wire.begin(0x03);
  Wire.onReceive(receiveEventdf);
  
  /* set the default servo positions*/
  for(int i = 0;i<9;i++){
    pos[i] = 128;
  }
}

void loop() {
  for(int i = 0;i<7;i++){

    channels[i].write(map(pos[i],0,255,0,180));
    
  }
  M1.setPos(pos[7]);
  M2.setPos(pos[8]);
  delay(100);
}

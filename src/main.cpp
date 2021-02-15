#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>


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
int pos[7];



void receiveEvent(int howMany)
{
  char command;
  int temppos;
  while(Wire.available()){
    Wire.read();
    // command = Wire.read();
    // if(command=='S'){
    //   for(int i = 0; i< 7; i++){
    //     temppos = Wire.read();
    //   }
    // }
    // else{
    //   command = Wire.read();
    // }
  }
}



void setup() {
  Serial.begin(115200);
  Serial.println("Starting robot stm");
  uint8_t index;
  //   Serial.println("setting output mode");
  // for(int i = 0;i<7;i++){
  //   pinMode(channelpins[i],OUTPUT);
  // }
  // for(int i = 0; i<8;i++){
  //   Serial.print("setting up servo: ");
  //   Serial.print(i);
  //   index = channels[i].attach(channelpins[i]);
  //   Serial.print(" index: ");
  //   Serial.println(index);

  // }

 channels[0].attach(channelpins[0]);
  // Wire.setSCL(PB_6);
  // Wire.setSDA(PB_7);
  // Wire.begin(0x03);
  // Wire.onReceive(receiveEvent);
  
  /* set the default servo positions*/
  for(int i = 0;i<7;i++){
    pos[i] = 128;
  }
}

void loop() {
  int pos;
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    channels[0].write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    channels[0].write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for(int i = 0;i<7;i++){
    // Serial.print("setting servo ");
    // Serial.print(i);
    // Serial.print(" to ");
    // Serial.println(map(pos[i],0,255,0,180));
    //channels[i].write(map(pos[i],0,255,0,180));
  }
}

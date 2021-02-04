#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <STM32FreeRTOS.h>
#include <STM32FreeRTOSConfig.h>

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

void UpdateServoPos(void *pvParameters){

  for(;;){
    for(int i = 0;i<7;i++){
      channels[i].write(map(pos[i],0,255,0,180));
    }
    vTaskDelay(10/portTICK_PERIOD_MS);
  
  }
}

void TaskStatus(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  Serial.println("STatus task started");
  // initialize digital pin PA_8 as an output.
  pinMode(PA_8,OUTPUT);
  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(PA_8, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(PA_8, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}

void receiveEvent(int howMany)
{
  char command;
  Serial.print("received");
  while(Wire.available()){
    command = Wire.read();
    if(command=='S'){
      for(int i = 0; i< 7; i++){
        pos[i] = Wire.read();
      }
    }
    else{
      command = Wire.read();
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting robot stm");
  uint8_t index;
  
  for(int i = 0; i<8;i++){
    Serial.print("setting up servo: ");
    Serial.print(i);
    index = channels[i].attach(channelpins[i]);
    Serial.print(" index: ");
    Serial.println(index);

  }
  Serial.println("setting up task");
  xTaskCreate(
    TaskStatus,
    "Status",   // A name just for humans
    128,  // Stack size
    NULL,
    tskIDLE_PRIORITY,  // priority
    NULL );
  Serial.println("setting output mode");
  pinMode(PA_4,OUTPUT);
  pinMode(PA_5,OUTPUT);
  pinMode(PA_6,OUTPUT);
  pinMode(PC_6,OUTPUT);
  pinMode(PC_7,OUTPUT);
  pinMode(PC_8,OUTPUT);
  /* set the default servo positions*/
  for(int i = 0;i<7;i++){
    pos[i] = 128;
  }
  xTaskCreate(
  UpdateServoPos,
  "updateServoPos",   // A name just for humans
  128,  // Stack size
  NULL,
  5,  // priority
  NULL );
  //   xTaskCreate(
  // receiveI2C,
  // "receiveI2C",   // A name just for humans
  // 1024,  // Stack size
  // NULL,
  // 3,  // priority
  // NULL );
  Serial.println("starting...");

  Wire.begin(3);
  Wire.setSCL(PB_6);
  Wire.setSDA(PB_7);
  Wire.onReceive(receiveEvent);

  vTaskStartScheduler();
}

void loop() {
  }

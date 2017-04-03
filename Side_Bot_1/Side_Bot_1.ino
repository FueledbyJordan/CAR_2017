#include "Sensor.h"
#include "Motor.h"
#include "Communication.h"

// * SIDEBOT 1

Sensor sensor;

void setup(){
  Serial.begin(9600);

  sensor.init();
  initMotors();
  initSB1();

}

void loop(){
  delay(1000);
  
  //wait for start
  while(!getStart()){
    delay(100);
  }
  // ACTUAL CODE
  
  pidForward(sensor, 40);

  drive(0);

  delay(50);

  accel(60, 0.2);

  int count = 0;
  
  while(!sensor.areBothPressed() || count < 50){
    sensor.setLeftTouch();
    sensor.setRightTouch();
    delay(100);
    count++;
  }

  //Serial.println("Exit");

  drive(0);

  
  //extend the arm
  //call these methods twice in order for full reach
  armForward();
  armForward();
  
  drive(30);

  
  //connection has been made, let's do some probing
  sensor.getCode();
  
  setDone(true); //when requested will transmit code
  
  while(1){
    delay(100);
  }

}

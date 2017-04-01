#include "Sensor.h"
#include "Motor.h"
#include "Communication.h"

// * SIDEBOT 2

Sensor sensor;

void setup(){
  Serial.begin(9600);

  sensor.init();
  //sensor.setFrontSensorPair();
  initMotors();
  initSB2();
  servoInit();

}

void loop(){
  while(!getStart()){
    delay(100);
  }
  // ACTUAL CODE
  pidForward(sensor, 40);

  drive(0);

  delay(50);

  accel(60, 0.2);

  while(!sensor.areBothPressed()){
    sensor.setLeftTouch();
    sensor.setRightTouch();
  }

  drive(0);

  setDest(true);

  armForward();
  lower();

  //turn sequence based on CO_ code from master

  setDone(true);

  while(1){

  }

}

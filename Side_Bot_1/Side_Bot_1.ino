#include "Sensor.h"
#include "Motor.h"

// * SIDEBOT 1

Sensor sensor;

void setup(){
  Serial.begin(9600);

  sensor.init();
  //sensor.setFrontSensorPair();
  initMotors();

}

void loop(){

  // ACTUAL CODE
  pidForward(sensor, 40);

  drive(0);

  delay(50);

  accel(30, 0.2);

  while(!sensor.areBothPressed()){
    sensor.setLeftTouch();
    sensor.setRightTouch();
  }

  drive(0);

  while(1){

  }

}

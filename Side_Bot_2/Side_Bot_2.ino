#include "Sensor.h"
#include "Motor.h"

// * SIDEBOT 2

Sensor sensor;

void setup(){
  Serial.begin(9600);

  sensor.init();
  initMotors();

}

void loop(){
  //Serial.println(sensor.getFrontDistance());

  delay(2000);

  pidForward(sensor, 100);

  drive(0);

  while(1){

  }

}

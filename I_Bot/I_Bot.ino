#include "Sensor.h"
#include "motor_control.h"
#include "Communication.h"

Sensor sensor;

void setup(){
    Serial.begin(9600);

    motorInit();
    sensor.init();
}

void loop(){
  delay(10000);
  move(-100,0,0);
  while(sensor.getFrontLeftDistance() > 5){
  }
  move(0,0,0);
  fire();
  while(1){

  }
}
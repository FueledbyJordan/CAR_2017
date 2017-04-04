#include "Sensor.h"
#include "Motor.h"
#include "Communication.h"

// * SIDEBOT 2

Sensor sensor;

void setup(){
  Serial.begin(9600);

  sensor.init();
  initMotors();
  initSB2();
  servoInit();

}

void loop(){
  while(!getStart()){
    delay(100);
  }
  // ACTUAL CODE

  accel(60, 0.2);

  int count = 0;

  while(!sensor.areBothPressed() || count < 5 0){
    sensor.setLeftTouch();
    sensor.setRightTouch();
    count++;
    delay(100);
  }

  drive(0);

  setDest(true);

  //armForward();
  armForward();
  
  lower();

  setDone(true);
  
  //turn sequence based on CO_ code from master
  //armReverse();
  //reset();
  

  rotate(sensor);

  
  

  while(1){
    //Serial.println(sensor.revolution());
    //Serial.println(digitalRead(49));
  }

}

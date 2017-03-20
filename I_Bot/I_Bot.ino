#include "Sensor.h"
#include "motor_control.h"

Sensor sensor;

void setup(){
    Serial.begin(9600);


    pinMode(M1DIR, OUTPUT);
    pinMode(M1SPD, OUTPUT);
    pinMode(M2DIR, OUTPUT);
    pinMode(M2SPD, OUTPUT);
    pinMode(M3DIR, OUTPUT);
    pinMode(M3SPD, OUTPUT);
    pinMode(M4DIR, OUTPUT);
    pinMode(M4SPD, OUTPUT);
    
    sensor.init();
}

void loop(){
  /*move(100,0,0);
  while(sensor.getFrontLeftDistance() > 10){
  }
  move(0,0,0);
  while(1){
    
  }*/
  Serial.println(sensor.getFrontRightDistance());
  delay(100);
}

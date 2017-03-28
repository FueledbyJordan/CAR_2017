#include "Sensor.h"
#include "motor_control.h"
#include "Communication.h"

Sensor sensor;

void setup(){
    Serial.begin(9600);

    motorInit();
    sensor.init();
    initMaster();
}

void loop(){
  delay(10000);

  startSideBots();

  delay(10000);
  //SEND START MESSAGE TO SIDEBOTS
  move(-100,0,0);
  while(sensor.getFrontLeftDistance() > 5){
  }
  move(0,0,0);
  //STAGE TWO
  //REQUEST CODE FROM SB1
  //SEND CODE TO SB2
  //REQUEST SB2 FINISHED
  //fire();
  while(1){

  }
}

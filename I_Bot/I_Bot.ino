#include "Sensor.h"
#include "motor_control.h"
#include "Communication.h"

Sensor sensor;

void setup(){
    Serial.begin(9600);

    startSwitchInit();
    motorInit();
    sensor.init();
    initMaster();

}

void loop(){
  //delay(10000);
  while(!getStartSwitch()){
    delay(100);
  }


  startSideBots();

  //SEND START MESSAGE TO SIDEBOTS
  move(-100,0,0);
  while(sensor.getFrontLeftDistance() >= 5){
  }
  move(0,0,0);

  //STAGE TWO
  for (int i = 0; i < 5; i++){
    getPulse(); //add a count and exit when count gets to a number using OR
    swing();
  }

  //REQUEST CODE FROM SB1
  while(getNetworkCode() == ""){ //add a count and exit when count gets to a number using OR
      masterRequest(SB1_ADDRESS);
      delay(100);
  }

  //SEND CODE TO SB2
  sendCode();

  //REQUEST SB2 FINISHED
  while(!getsb2Done()){ //add a count and exit when count gets to a number using OR
    masterRequest(SB2_ADDRESS);
    delay(100);
  }

  fire();

  while(1){

  }
}

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

  /*delay(10000);
  //SEND START MESSAGE TO SIDEBOTS
  move(-100,0,0);
  while(sensor.getFrontLeftDistance() > 5){
  }
  move(0,0,0);
  */
  //STAGE TWO
  /*for (int i = 0; i < 5; i++){
    getPulse();
    swing();
  }*/
  
  //REQUEST CODE FROM SB1
  while(getNetworkCode() == ""){
      masterRequest(SB1_ADDRESS);
      delay(100);
  }
    
  //SEND CODE TO SB2
  sendCode();

  //REQUEST SB2 FINISHED
  while(!getsb2Done()){
    masterRequest(SB2_ADDRESS);
    delay(100);
  }

  //fire();
  while(1){

  }
}


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
  
  int count = 0;
  while(!getStartSwitch()){
    delay(100);
  }
  
  startSideBots();

  delay(3000);
  
  //SEND START MESSAGE TO SIDEBOTS
  move(-100, 0, 0);
  
  while(sensor.getFrontDistance() >= 4){
   
  }
  
  move(0,0,0);

  delay(50);

  move(-100,0,0);

  delay(400);

  move(0,0,0);

  //STAGE TWO
  
  setFreeSpace();
  
  swing();

  for(int i = 0; i < 4; i++){
    getPulse();
    swing();
  }

  lightsaberOff();
  
  count = 0;
  move(-100, 0, 0);
  delay(600);
  move(0,0,0);
  
  //REQUEST CODE FROM SB1
  while((getNetworkCode() == "") || (count < 150)){ //add a count and exit when count gets to a number using OR
      masterRequest(SB1_ADDRESS);
      delay(100);
      count++;
  }

  //SEND CODE TO SB2
  
  sendCode();
  /*
  //REQUEST SB2 FINISHED
  count = 0;
  while(!getsb2Done() || count < 150){ //add a count and exit when count gets to a number using OR
    masterRequest(SB2_ADDRESS);
    delay(100);
    count++;
  }
  */
  //delay(5000);
  
  fire();

  while(1){

  }
}

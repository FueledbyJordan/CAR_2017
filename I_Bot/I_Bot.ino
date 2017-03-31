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

  delay(5000);

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
  count = 0;
  //REQUEST CODE FROM SB1
  while(getNetworkCode() == "" || count < 900){ //add a count and exit when count gets to a number using OR
      masterRequest(SB1_ADDRESS);
      delay(100);
      count++;
  }

  //SEND CODE TO SB2
  sendCode();

  //REQUEST SB2 FINISHED
  count = 0;
  while(!getsb2Done() || count < 90){ //add a count and exit when count gets to a number using OR
    masterRequest(SB2_ADDRESS);
    delay(100);
    count++;
  }

  fire();

  while(1){

  }
}

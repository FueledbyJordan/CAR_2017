#include "Communication.h"

LSM303 compass;

//SETTERS
void setMasterStart(bool start){
  masterStart = start;
}
/*
void setTask(bool task){
  bTask = task;
}

void setDone(bool done){
  bDone = done;
}

void setCode(String code){
  networkCode = code;
}
*/
//GETTERS
bool getMasterStart(){
  return masterStart;
}

bool getsb1Task(){
  return sb1Task;
}

bool getsb1Done(){
  return sb1Done;
}

bool getsb2Dest(){
  return sb2Dest;
}

bool getsb2Done(){
  return sb2Done;
}

void initMaster(){
  masterStart = false;
  sb1Task = false;
  sb1Done = false;

  sb2Dest = false;
  sb2Done = false;

  networkCode = "";

  Wire.begin();                // join i2c bus with address #8
  initMag();
}

void startSideBots(){
    Wire.beginTransmission(SB1_ADDRESS);
    Wire.write("START");
    Wire.endTransmission();

    delay(2000);

    Wire.beginTransmission(SB2_ADDRESS);
    Wire.write("START");
    Wire.endTransmission();
}

void masterRequest(int destination){
  Wire.requestFrom(destination, 8);
  String workingString = "";
  String message = "";
  int i = 0;
  while(Wire.available()){
    message += (char)Wire.read();
  }

  message += "&";

  switch(destination){  //begin John's spaghetti code
    case SB1_ADDRESS:
      if(message.charAt(0) == 'S' && message.charAt(1) == 'T'){
        while(message.charAt(i) != '&'){
          workingString += message.charAt(i);
          i++;
        }
        if(workingString.equals(TASK)){
          sb1Task = true;
        }else if(workingString.equals(DONE)){
          sb1Done = true;
        }
      }else if(message.charAt(0) == 'C' && message.charAt(1) == 'O'){
        i = 3;
        while(message.charAt(i) != '&'){
          networkCode += message.charAt(i);
          i++;
        }
      }
      break;

    case SB2_ADDRESS:
    if(message.charAt(0) == 'S' && message.charAt(1) == 'T'){
      while(message.charAt(i) != '&'){
        workingString += message.charAt(i);
        i++;
      }
      if(workingString.equals(DEST)){
        sb2Dest = true;
      }else if(workingString.equals(DONE)){
        sb2Done = true;
      }
    }
    break;
  }
}

void sendCode(){
  Wire.beginTransmission(SB2_ADDRESS);
  Wire.write(networkCode.c_str());
  Wire.endTransmission();
}

void initMag(){
  compass.init();
  compass.enableDefault();
}

void getPulse(){
  const float TOLERANCE = 0.01;

  compass.read();
  //should hard code the baseline value, do this at competition.
  //may adjust the TOLERANCE value
  //put a delay after pulse
  float baseLine = sqrt(compass.m.x * compass.m.x + compass.m.y * compass.m.y + compass.m.z * compass.m.z);
  float current = baseLine;
  while(baseLine <= current*(1+TOLERANCE) && baseLine >= current*(1-TOLERANCE)){
    compass.read();
    current = sqrt(compass.m.x * compass.m.x + compass.m.y * compass.m.y + compass.m.z * compass.m.z);
  }
}

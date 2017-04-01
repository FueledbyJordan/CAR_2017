#include "Communication.h"

Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

//SETTERS
void setMasterStart(bool start){
        masterStart = start;
}

String getNetworkCode(){
        return networkCode;
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

        Wire.begin();          // join i2c bus with address #8

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
        while(Wire.available()) {
                message += (char)Wire.read();
        }

        message += "&";

        switch(destination) { //begin John's spaghetti code
        case SB1_ADDRESS:
                if(message.charAt(0) == 'S' && message.charAt(1) == 'T') {
                        while(message.charAt(i) != '&') {
                                workingString += message.charAt(i);
                                i++;
                        }
                        if(workingString.equals(TASK)) {
                                sb1Task = true;
                        }else if(workingString.equals(DONE)) {
                                sb1Done = true;
                        }
                }else if(message.charAt(0) == 'C' && message.charAt(1) == 'O') {
                        i = 0;
                        while(message.charAt(i) != '&') {
                                networkCode += message.charAt(i);
                                i++;
                        }
                }
                break;

        case SB2_ADDRESS:
                if(message.charAt(0) == 'S' && message.charAt(1) == 'T') {
                        while(message.charAt(i) != '&') {
                                workingString += message.charAt(i);
                                i++;
                        }
                        if(workingString.equals(DEST)) {
                                sb2Dest = true;
                        }else if(workingString.equals(DONE)) {
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
    mag.begin();
}

void setFreeSpace(){
  sensors_event_t event;
  mag.getEvent(&event);
  FREESPACE = sqrt(pow(event.magnetic.x, 2) + pow(event.magnetic.y, 2) + pow(event.magnetic.z, 2));
}

float getFreeSpace(){
  return FREESPACE;
}

void getPulse()
{
  float magnitude = getFreeSpace() - 1;
  float TOLERANCE = 5;


  while(magnitude < getFreeSpace() + TOLERANCE){
    sensors_event_t event;
    mag.getEvent(&event);
    magnitude = sqrt(pow(event.magnetic.x, 2) + pow(event.magnetic.y, 2) + pow(event.magnetic.z, 2));
    if(magnitude == 0){
      magnitude = getFreeSpace();  //Filter out 0's
    }
  }
}

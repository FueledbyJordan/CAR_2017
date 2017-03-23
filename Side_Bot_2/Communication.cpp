#include "Communication.h"

//SETTERS
void setStart(bool start){
  bStart = start;
}

void setTask(bool dest){
  bDest = dest;
}

void setDone(bool done){
  bDone = done;
}

void setCode(String code){
  networkCode = code;
}

//GETTERS
bool getStart(){
  return bStart;
}

bool getDest(){
  return bDest;
}

bool getDone(){
  return bDone;
}

void initSB1(){
  bStart = false;
  bDest = false;
  bDone = false;
  networkCode = "";

  Wire.begin(SB2_ADDRESS);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);
  //Serial.begin(9600);           // start serial for output
}

void receiveEvent(int howMany) {
  String message = "";
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read();
    message += c;
        //Serial.println((char)Wire.read());
  }

  if(message.equals("START")){
    bStart = true;
  }else if(message.charAt(0) == 'C' && message.charAt(1) == 'O'){
    for(int i = 3; i < 8; i++){
      networkCode += message.charAt(i);
    }
  }
}

void requestEvent(){
  if(bStart == false){
    Wire.write(START.c_str());
  }else if(bDest == false){
    Wire.write(DEST.c_str());
  }else if(bDone == false){
    Wire.write(DONE.c_str());
  }
}

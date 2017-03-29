#include "Sensor.h"

void Sensor::init() {
    setFrontSensorPair();
    setSideSensor();
    setTouchSensorPair();
}

void Sensor::setFrontSensorPair() {
    frontLeft.begin(FLIR);
    frontRight.begin(FRIR);
}

void Sensor::setSideSensor() {
    side.begin(SIR);
}

int Sensor::getFrontRightDistance(){
  return frontRight.getDistanceCentimeter();
}

int Sensor::getFrontLeftDistance(){
  return frontLeft.getDistanceCentimeter();
}

int Sensor::getFrontDistance() {
    return (frontLeft.getDistanceCentimeter() + frontRight.getDistanceCentimeter()) / 2;
}

int Sensor::getFrontDifference(){
    return ((frontLeft.getDistanceCentimeter() - frontRight.getDistanceCentimeter()));
}

int Sensor::getSideDistance() {
    return side.getDistanceCentimeter();
}

void Sensor::setTouchSensorPair() {
    pinMode(FLT, INPUT);
    pinMode(FRT, INPUT);
}

void startSwitchInit(){
  pinMode(STARTSWITCH,INPUT);
}

bool getStartSwitch(){
  if(digitalRead(STARTSWITCH) == HIGH){
    return true;
  }else{
    return false;
  }
}

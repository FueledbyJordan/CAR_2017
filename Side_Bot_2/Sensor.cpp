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

int Sensor::getFrontDistance() {
    return (frontLeft.getDistanceCentimeter() + frontRight.getDistanceCentimeter()) / 2;
}

int Sensor::getFrontDifference(){
      int total;
      for (int i = 0; i < 5; i++){
        total+=(getFrontLeftDistance()-getFrontRightDistance());
        delay(50);
      }
    return total/5;
}

int Sensor::getSideDistance() {
    return side.getDistanceCentimeter();
}

void Sensor::setTouchSensorPair() {
    pinMode(FLT, INPUT);
    pinMode(FRT, INPUT);
}

int Sensor::getFrontLeftDistance() {
  return frontLeft.getDistanceCentimeter();
}

int Sensor::getFrontRightDistance() {
  return frontRight.getDistanceCentimeter();
}

boolean Sensor::areBothPressed() {
  return (rButtonPressed & lButtonPressed);
}

void Sensor::setLeftTouch() {
  if (digitalRead(FLT)) {
    lButtonPressed = true;
  }
}

void Sensor::setRightTouch() {
  if (digitalRead(FRT)) {
    rButtonPressed = true;
  }
}









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

int Sensor::getSideDistance() {
    return side.getDistanceCentimeter();
}

void Sensor::setTouchSensorPair() {
    pinMode(FLT, INPUT);
    pinMode(FRT, INPUT);
}

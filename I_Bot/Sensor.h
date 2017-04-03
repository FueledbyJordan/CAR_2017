#ifndef SENSOR_H
#define SENSOR_H

#include <DistanceGP2Y0A21YK.h>
#include "Arduino.h"

#define SIR A2  //Side IR Sensor
#define FLIR A1 //Front Left IR Sensor
#define FRIR A0 //Front Right IR Sensor

#define FRT 23  //Front Right Touch Sensor
#define FLT 25  //Front Left Touch Sensor

#define STARTSWITCH 3

class Sensor{
    public:
        void init();

        int getFrontDistance();
        int getSideDistance();
        int getFrontDifference();
        int getFrontLeftDistance();
        int getFrontRightDistance();

    private:
        DistanceGP2Y0A21YK frontLeft;
        DistanceGP2Y0A21YK frontRight;
        DistanceGP2Y0A21YK side;

        bool lButtonPressed = false;
        bool rButtonPressed = false;

        void setFrontSensorPair();
        void setSideSensor();
        void setTouchSensorPair();
};

void startSwitchInit();
bool getStartSwitch();

#endif //Sensor.h

#ifndef SENSOR_H
#define SENSOR_H

#include <DistanceGP2Y0A21YK.h>
#include "Arduino.h"

#define SIR A2  //Side IR Sensor
#define FLIR A1 //Front Left IR Sensor
#define FRIR A0 //Front Right IR Sensor

#define FRT 29  //Front Right Touch Sensor
#define FLT 31  //Front Left Touch Sensor

#define SCOUNT 49

class Sensor{
    public:
        void init();

        int getFrontLeftDistance();
        int getFrontRightDistance();
        
        int getFrontDistance();
        int getSideDistance();
        int getFrontDifference();

        void setLeftTouch();
        void setRightTouch();
        void setFrontSensorPair();
        void setSideSensor();
        void setTouchSensorPair();

        boolean areBothPressed();


    private:
        DistanceGP2Y0A21YK frontLeft;
        DistanceGP2Y0A21YK frontRight;
        DistanceGP2Y0A21YK side;

        bool lButtonPressed = false;
        bool rButtonPressed = false;
};
#endif //Sensor.h



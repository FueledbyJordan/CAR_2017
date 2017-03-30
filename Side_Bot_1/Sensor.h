#ifndef SENSOR_H
#define SENSOR_H

#include <DistanceGP2Y0A21YK.h>
#include "Communication.h"
#include "Arduino.h"

#define INDUCTOR 1020
#define SHORT 0

#define ACAPACITOR1 544
#define ACAPACITOR2 663

#define ARESISTOR 540
#define ADIODE 120

#define CCAPACITOR1 613
#define CCAPACITOR2 710

#define CRESISTOR 576
#define CDIODE 703

#define SIR A0  //Side IR Sensor
#define FLIR A1 //Front Left IR Sensor
#define FRIR A2 //Front Right IR Sensor

#define FRT 31  //Front Right Touch Sensor
#define FLT 29  //Front Left Touch Sensor

#define PROBE1 A5  //NORTH
#define PROBE2 A6  //NORTHEAST
#define PROBE3 A3  //SOUTHEAST
#define PROBE4 A7  //SOUTHWEST
#define PROBE5 A4  //NORTHWEST
#define ENABLEPROBE 8

class Sensor{
    public:
        void init();

        int getFrontLeftDistance();
        int getFrontRightDistance();

        int getFrontDistance();
        int getSideDistance();
        int getFrontDifference();
        void getCode();

        void setLeftTouch();
        void setRightTouch();
        void setFrontSensorPair();
        void setSideSensor();
        void setTouchSensorPair();
        void setProbe();


        boolean areBothPressed();


    private:
        DistanceGP2Y0A21YK frontLeft;
        DistanceGP2Y0A21YK frontRight;
        DistanceGP2Y0A21YK side;

        bool lButtonPressed = false;
        bool rButtonPressed = false;
};
#endif //Sensor.h

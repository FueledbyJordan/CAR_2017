#include "Sensor.h"

void Sensor::init() {
        setFrontSensorPair();
        setSideSensor();
        setTouchSensorPair();
        setProbe();
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
        for (int i = 0; i < 5; i++) {
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

void Sensor::setProbe(){
        pinMode(ENABLEPROBE, OUTPUT);
        digitalWrite(ENABLEPROBE,HIGH);
}

void Sensor::getCode(){
        const float INDUCTOR = 4.98;
        const float CAPACITOR = 1.74;
        const float RESISTOR = 1.42;
        const float DIODE = 0.56;
        const float SHORT = 0;

        const float TOLERANCE = .2;

        float reading[5];
        String code = "";

        reading[0] = analogRead(PROBE1) * 5.0/1023.0;
        delay(50);
        reading[1] = analogRead(PROBE2) * 5.0/1023.0;
        delay(50);
        reading[2] = analogRead(PROBE3) * 5.0/1023.0;
        delay(50);
        reading[3] = analogRead(PROBE4) * 5.0/1023.0;
        delay(50);
        reading[4] = analogRead(PROBE5) * 5.0/1023.0;
        delay(50);

        for (int i = 0; i < 5; i++) {
                if (reading[i] <= SHORT * (1 + TOLERANCE) && reading[i] >= SHORT * (1 - TOLERANCE)) {
                        code += '1';
                }else if(reading[i] <= RESISTOR * (1 + TOLERANCE) && reading[i] >= RESISTOR * (1 - TOLERANCE)) {
                        code += '2';
                }else if(reading[i] <= CAPACITOR * (1 + TOLERANCE) && reading[i] >= CAPACITOR * (1 - TOLERANCE)) {
                        code += '3';
                }else if(reading[i] <= INDUCTOR * (1 + TOLERANCE) && reading[i] >= INDUCTOR * (1 - TOLERANCE)) {
                        code += '4';
                }else if(reading[i] <= DIODE * (1 + TOLERANCE) && reading[i] >= DIODE * (1 - TOLERANCE)) {
                        code += '5';
                }
        }

        printCode(code);

        setCode(code);
}

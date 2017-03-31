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

        int storedValue[5][2];//[probe][readings]
        digitalWrite(ENABLEPROBE, LOW);
        delay(1000);
        digitalWrite(ENABLEPROBE,HIGH);
        String code = "";
        const float TOLERANCE = 0.1;

        for(int readings = 0; readings < 2; readings++) {
          storedValue[0][readings] = analogRead(PROBE1);
          storedValue[1][readings] = analogRead(PROBE2);
          storedValue[2][readings] = analogRead(PROBE3);
          storedValue[3][readings] = analogRead(PROBE4);
          storedValue[4][readings] = analogRead(PROBE5);
          delay(10);
        }
        digitalWrite(ENABLEPROBE,LOW);

//        Serial.print("Probe 1:\t");
//        Serial.println(storedValue[0][0]);
//        Serial.println(storedValue[0][1]);
//
//        Serial.println();
//
//        Serial.print("Probe 2:\t");
//        Serial.println(storedValue[1][0]);
//        Serial.println(storedValue[1][1]);
//
//        Serial.println();
//
//        Serial.print("Probe 3:\t");
//        Serial.println(storedValue[2][0]);
//        Serial.println(storedValue[2][1]);
//
//        Serial.println();
//
//                Serial.print("Probe 4:\t");
//        Serial.println(storedValue[3][0]);
//        Serial.println(storedValue[3][1]);
//
//        Serial.println();
//
//                Serial.print("Probe 5:\t");
//        Serial.println(storedValue[4][0]);
//        Serial.println(storedValue[4][1]);
//
//        Serial.println();

        for (int i = 0; i < 5; i++){
          if (storedValue[i][1] - storedValue[i][0] > 15){  //capacitor
            code += '3';
          }else if(storedValue[i][0] - storedValue[i][1] > 15){ //inductor
            code += '4';
          }else if(storedValue[i][1] <= SHORT * (1+TOLERANCE) && storedValue[i][1] >= SHORT * (1-TOLERANCE)){
            code += '1';
          }else if((storedValue[i][1] <= ARESISTOR * (1+TOLERANCE) && storedValue[i][1] >= ARESISTOR * (1-TOLERANCE)) || (storedValue[i][1] <= CRESISTOR * (1+TOLERANCE) && storedValue[i][1] >= CRESISTOR * (1-TOLERANCE))){
            code += '2';
          }else if((storedValue[i][1] <= ADIODE * (1+TOLERANCE) && storedValue[i][1] >= ADIODE * (1-TOLERANCE)) || (storedValue[i][1] <= CDIODE * (1+TOLERANCE) && storedValue[i][1] >= CDIODE * (1-TOLERANCE))){
            code += '5';
          }
        }
        
        printCode(code);

        setTask(true);

        setCode(code);

    }




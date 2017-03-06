#include "Motor.h"

void initMotors(){
    pinMode(M1DIR, OUTPUT);
    pinMode(M1SPD, OUTPUT);
    pinMode(M2DIR, OUTPUT);
    pinMode(M2SPD, OUTPUT);
    pinMode(M3DIR, OUTPUT);
    pinMode(M3SPD, OUTPUT);
    pinMode(M4DIR, OUTPUT);
    pinMode(M4SPD, OUTPUT);
}

void motor1(int speed) {
    if (speed >= 0) {
        digitalWrite(M1DIR, 0);
    } else {
        digitalWrite(M1DIR, 1);
        speed = -speed;
    }
    if (speed > 255) {
        speed = 255;
    }
    analogWrite(M1SPD, speed);
}

void motor2(int speed) {
    if (speed >= 0) {
        digitalWrite(M2DIR, 0);
    } else {
        digitalWrite(M2DIR, 1);
        speed = -speed;
    }
    if (speed > 255) {
        speed = 255;
    }
    analogWrite(M2SPD, speed);
}

void motor3(int speed) {
    if (speed >= 0) {
        digitalWrite(M3DIR, 0);
    } else {
        digitalWrite(M3DIR, 1);
        speed = -speed;
    }
    if (speed > 255) {
        speed = 255;
    }
    analogWrite(M3SPD, speed);
}

void motor4(int speed) {
    if (speed >= 0) {
        digitalWrite(M4DIR, 0);
    } else {
        digitalWrite(M4DIR, 1);
        speed = -speed;
    }
    if (speed > 255) {
        speed = 255;
    }
    analogWrite(M4SPD, speed);
}

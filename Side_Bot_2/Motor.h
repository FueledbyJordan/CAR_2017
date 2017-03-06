#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

    static const int M1DIR=40;
    static const int M1SPD=12;
    static const int M2DIR=38;
    static const int M2SPD=11;
    static const int M3DIR=36;
    static const int M3SPD=10;
    static const int M4DIR=34;
    static const int M4SPD=9;

    void initMotors();

    void motor1(int speed);
    void motor2(int speed);
    void motor3(int speed);
    void motor4(int speed);

#endif //Motor.h

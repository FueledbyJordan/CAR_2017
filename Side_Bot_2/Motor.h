#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include "Sensor.h"

#define PID_CONST 1

    static const int mFLa=9;    //MOTOR 1
    static const int mFLb=7;

    static const int mFRa=10;   //MOTOR 2
    static const int mFRb=6;

    static const int mBLa=12;   //MOTOR 3
    static const int mBLb=4;

    static const int mBRa=11;   //MOTOR 4
    static const int mBRb=5;



    void initMotors();

    void motor1(int speed);
    void motor2(int speed);
    void motor3(int speed);
    void motor4(int speed);

    void drive(int velocity);
    void pidForward(Sensor sensor, int velocity);
//    void rotate(int theta);


#endif //Motor.h

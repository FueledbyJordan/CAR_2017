#ifndef MOTOR_H
#define MOTOR_H

#include <AccelStepper.h>
#include <Servo.h>
#include <Stepper.h>
#include "Arduino.h"
#include "Sensor.h"
#include "Communication.h"


#define PID_CONST 1

    const int mFLa=9;    //MOTOR 1
    const int mFLb=4;

    const int mFRa=10;   //MOTOR 2
    const int mFRb=5;

    const int mBLa=12;   //MOTOR 3
    const int mBLb=7;

    const int mBRa=11;   //MOTOR 4
    const int mBRb=6;

    const int HEIGHT = 8;


    static const int STAGE3PIN = 2;
    static const int STEP = 41;
    static const int STEP_DIR = 43;
    const int stepsPerRev = 513;

    static int adjustedV = 1;

    void initMotors();

    void servoInit();

    void lower();

    void motor1(int speed);
    void motor2(int speed);
    void motor3(int speed);
    void motor4(int speed);

    void drive(int velocity);
    void pidForward(Sensor sensor, int velocity);
//    void rotate(int theta);
    int accel(int velocity, float accelRate);

    void armForward();
    void armReverse();
    void reset();

    void rotate(Sensor sensor);


#endif //Motor.h

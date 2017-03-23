#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "Arduino.h"

static const int M1DIR=28;  //mFL
static const int M1SPD=12;
static const int M2DIR=26;  //mFR
static const int M2SPD=11;
static const int M3DIR=22;  //mBL
static const int M3SPD=9;
static const int M4DIR=24;  //mBR
static const int M4SPD=10;

static const int GUNMOTOR = 5;
static const int GUNSOLENOID = 4;


void motorInit();

void fire();

void motor1(int speed);
void motor2(int speed);
void motor3(int speed);
void motor4(int speed);

void move(short speed, unsigned short theta, short rotation);

#endif // MOTOR_CONTROL_H

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "Arduino.h"

static const int M1DIR=28;
static const int M1SPD=12;
static const int M2DIR=26;
static const int M2SPD=11;
static const int M3DIR=24;
static const int M3SPD=10;
static const int M4DIR=22;
static const int M4SPD=9;





static const float X_AXIS_MOVE_VEL = 0.45;     // in m/s
static const float Y_AXIS_MOVE_VEL = 0.45;     // in m/s
static const int ARM_Y_REACH = 120;            // in mm
static const int ALIGN_SPEED = 140;

void move(short speed, unsigned short theta, short rotation);
void sideStep(short speed, unsigned short direction, int milliseconds);
void align(int x, int y, int z);

#endif // MOTOR_CONTROL_H

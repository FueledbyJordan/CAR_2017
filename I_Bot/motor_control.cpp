#include <math.h>
#include "motor_control.h"

static const float RAD45    = 0.78539816;   //  pi/4

/* Function Prototypes */



void move(short speed, unsigned short theta, short rotation) {
    // get argument for trig functions
    float arg = (theta * PI / 180) + RAD45;

    float rot = rotation * PI / 180;

    // Calculate the four motor's speeds
    int v [4];
    v[0] = speed * sin(arg) + rotation;
    v[1] = speed * cos(arg) - rotation;
    v[2] = speed * cos(arg) + rotation;
    v[3] = speed * sin(arg) - rotation;

    // normalize if speed commanded over max pwm speed
    int maximum = 0;
    for (int i = 0; i < 4; i++) {
        if (abs(v[i]) > maximum) {
            maximum = abs(v[i]);
        }
    }

    if (maximum > 255) {
        for (int i = 0; i < 4; i++) {
            v[i] = int(speed * float(v[i]) / maximum);
        }
    }


    // Set the motor speeds
    motor1(v[0]);
    motor2(v[1]);
    motor3(v[2]);
    motor4(v[3]);
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
        digitalWrite(M2DIR, 1);
    } else {
        digitalWrite(M2DIR, 0);
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
        digitalWrite(M4DIR, 1);
    } else {
        digitalWrite(M4DIR, 0);
        speed = -speed;
    }
    if (speed > 255) {
        speed = 255;
    }
    analogWrite(M4SPD, speed);
}

void motorInit(){
    pinMode(M1DIR, OUTPUT);
    pinMode(M1SPD, OUTPUT);
    pinMode(M2DIR, OUTPUT);
    pinMode(M2SPD, OUTPUT);
    pinMode(M3DIR, OUTPUT);
    pinMode(M3SPD, OUTPUT);
    pinMode(M4DIR, OUTPUT);
    pinMode(M4SPD, OUTPUT);

    pinMode(GUNMOTOR, OUTPUT);
    pinMode(GUNSOLENOID, OUTPUT);
}

void fire(){
    analogWrite(GUNMOTOR, 255);
    delay(10000);
  for(int i=0; i < 3; i++){
    analogWrite(GUNSOLENOID, 255);
    delay(200);
    analogWrite(GUNSOLENOID, 0);
    delay(1000);
  }
  analogWrite(GUNMOTOR, 0);
}

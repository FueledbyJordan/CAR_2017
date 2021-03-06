#include "Motor.h"

AccelStepper step_motor(1, STEP, STEP_DIR);

void initMotors(){
        pinMode(mFLa, OUTPUT);
        pinMode(mFLb, OUTPUT);
        pinMode(mFRa, OUTPUT);
        pinMode(mFRb, OUTPUT);
        pinMode(mBLa, OUTPUT);
        pinMode(mBLb, OUTPUT);
        pinMode(mBRa, OUTPUT);
        pinMode(mBRb, OUTPUT);

        
        step_motor.setMaxSpeed(20000);
        step_motor.setAcceleration(5000);
}

void drive(int velocity) {

        motor1(velocity);
        motor2(velocity);
        motor3(velocity);
        motor4(velocity);
}

void pidForward(Sensor sensor, int velocity){
        int diffVal = 0;
         
        accel(velocity, 0.1);
        
          while(sensor.getFrontDistance() > 10) {
                  diffVal = sensor.getFrontDifference();
  
                  if (diffVal > 0) {
                          motor1((velocity - (diffVal * PID_CONST)));
                          motor3((velocity - (diffVal * PID_CONST)));
                          //turn left delta
                  }else if(diffVal < 0) {
                          motor2((velocity - (diffVal * PID_CONST)));
                          motor4((velocity - (diffVal * PID_CONST)));
                          //turn right delta
                  }
          }
  
}

int accel(int velocity, float accelRate) {
  int current_velocity = 0;
  while(current_velocity <= velocity){
    current_velocity += velocity * accelRate;
    drive(current_velocity);
    delay(20);
  }
}

/*void rotate(int theta) {

    int M1;
    int M2;
    int M3;
    int M4;

    theta %= 360;

    M3 = theta * (R + L/2);
    M4 = -M3;
    M2 = 1/4 * M3;
    M1 = 1/4 * M4;

    motor1(M1);
    motor2(M2);
    motor3(M3);
    motor4(M4);

    //spin for a time, then stop
   }*/

void motor1(int speed) {
        if (speed >= 0) {
                analogWrite(mFLb, 0);
                analogWrite(mFLa, speed);
        } else {
                speed *= -1;
                analogWrite(mFLa, 0);
                analogWrite(mFLb, speed);
        }
}

void motor2(int speed) {
    speed *= -1;
        if (speed >= 0) {
                analogWrite(mFRb, 0);
                analogWrite(mFRa, speed);
        } else {
                speed *= -1;
                analogWrite(mFRa, 0);
                analogWrite(mFRb, speed);
        }
}

void motor3(int speed) {
        if (speed >= 0) {
                analogWrite(mBLb, 0);
                analogWrite(mBLa, speed);
        } else {
                speed *= -1;
                analogWrite(mBLa, 0);
                analogWrite(mBLb, speed);
        }
}

void motor4(int speed) {
    speed *= -1;
        if (speed >= 0) {
                analogWrite(mBRb, 0);
                analogWrite(mBRa, speed);
        } else {
                speed *= -1;
                analogWrite(mBRa, 0);
                analogWrite(mBRb, speed);
        }
}

void armForward(){
  //while()//daniel's board is not reading{
    step_motor.moveTo(32000);
    step_motor.run();
  //}
}

void armReverse(){
    step_motor.moveTo(-32000);
    step_motor.run();
}


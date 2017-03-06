#include "Sensor.h"
#include "Motor.h"

// * SIDEBOT 2

Sensor sensor;

void setup(){
  Serial.begin(9600);

  sensor.init();
  initMotors();

}

void loop(){
    //uncomment next 4 lines to test IR sensors
    /*
    Serial.println(sensor.getSideDistance());
    Serial.println(sensor.getFrontDistance());
    */

//uncomment next 4 lines to test motors
/*    motor1(100);
    motor2(100);
    motor3(100);
    motor4(100);*/

//uncomment next 4 lines to test motor directions
/*    motor1(-100);
    motor2(-100);
    motor3(-100);
    motor4(-100);*/

  //uncomment next 8 lines to test touch sensors
  /*if (digitalRead(FLT) && digitalRead(FRT)){
    Serial.println("Both");
  }else if(digitalRead(FLT)){
    Serial.println("Left");
  }else if(digitalRead(FRT)){
    Serial.println("Right");
  }else{
    Serial.println("None");
}*/

  delay(25);

}

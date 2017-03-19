#include "Sensor.h"
#include "motor_control.h"

Sensor sensor;

void setup(){
    Serial.begin(9600);

    sensor.init();
}

void loop(){
    sensor.getLeftDistance();
    delay(100);
}

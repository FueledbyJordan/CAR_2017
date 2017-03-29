#include "Motor.h"
#include "Sensor.h"


void setup()
{
  Serial.begin(9600);
  initMotors();
}

void loop()
{
  //armForward();
  armReverse();
}

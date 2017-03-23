#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <Wire.h>

#define SB1_ADDRESS 8

const String START = "ST_START";
const String TASK = "ST_TASK&";
const String DONE = "ST_DONE&";

static String networkCode;

static bool bStart;
static bool bTask;
static bool bDone;

void setStart(bool start);
void setTask(bool task);
void setDone(bool done);

bool getStart();
bool getTask();
bool getDone();

void setCode(String code);

void initSB1();

void receiveEvent(int howMany);

void requestEvent();

#endif //COMMUNICATION_H

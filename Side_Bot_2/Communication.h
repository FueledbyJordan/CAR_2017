#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <Wire.h>

#define SB2_ADDRESS 9

const String START = "ST_START";
const String DEST = "ST_DEST&";
const String DONE = "ST_DONE&";

static String networkCode;

static bool bStart;
static bool bDest;
static bool bDone;

void setStart(bool start);
void setDest(bool dest);
void setDone(bool done);

bool getStart();
bool getDest();
bool getDone();

void setCode(String code);

void initSB1();

void receiveEvent(int howMany);

void requestEvent();

#endif //COMMUNICATION_H

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <Wire.h>
#include <LSM303.h>

#define SB1_ADDRESS 8
#define SB2_ADDRESS 9

const String START = "ST_START";
const String TASK = "ST_TASK";
const String DEST = "ST_DEST";
const String DONE = "ST_DONE";

static String networkCode;

static bool masterStart;

static bool sb1Task;
static bool sb1Done;

static bool sb2Dest;
static bool sb2Done;

void setMasterStart(bool start);

void setsb1Task(bool task);
void setsb1Done(bool done);

void setsb2Dest(bool dest);
void setsb2Done(bool done);

bool getMasterStart();

bool getsb1Task();
bool getsb1Done();

bool getsb2Dest();
bool getsb2Done();

String getNetworkCode();

void setCode(String code);

void initMaster();

void startSideBots();

void masterRequest(int destination);

void sendCode();

void initMag();

void getPulse();

#endif //COMMUNICATION_H

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#define SB1_ADDRESS 8

static const int LCD_D = 42;
static const int LCD_G = 44;
static const int LCD_K = 38;
static const int LCD_L = 40;
static const int LCD_M = 36;
static const int LCD_N = 34;

static const String START = "ST_START";
static const String TASK = "ST_TASK&";
static const String DONE = "ST_DONE&";

static String networkCode;

static bool bStart;
static bool bTask;
static bool bDone;



void initSB1();
void initLCD();

void setStart(bool start);
void setTask(bool task);
void setDone(bool done);

bool getStart();
bool getTask();
bool getDone();

void setCode(String code);

void printCode(String code);

void receiveEvent(int howMany);

void requestEvent();

#endif //COMMUNICATION_H

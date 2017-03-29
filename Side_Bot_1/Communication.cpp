#include "Communication.h"

LiquidCrystal lcd(LCD_D, LCD_G, LCD_K, LCD_L, LCD_M, LCD_N);

//SETTERS
void setStart(bool start){
        bStart = start;
}

void setTask(bool task){
        bTask = task;
}

void setDone(bool done){
        bDone = done;
}

void setCode(String code){
        networkCode = code;
}

//GETTERS
bool getStart(){
        return bStart;
}

bool getTask(){
        return bTask;
}

bool getDone(){
        return bDone;
}

void initSB1(){
        bStart = false;
        bTask = false;
        bDone = false;
        networkCode = "";

        initLCD();
        if(Wire.available()) {
                Wire.begin(SB1_ADDRESS);  // join i2c bus with address #8
                Wire.onReceive(receiveEvent); // register event
                Wire.onRequest(requestEvent);
                //Serial.begin(9600);           // start serial for output
        }
}

void initLCD(){
        lcd.begin(16,2);
        lcd.setCursor(0,0);
}

void printCode(String code){
        int length = code.length() * 2;
        String lcdOutput = "";
        for(int i = 0; i < length; i++) {
                if(i & 1) {
                        lcdOutput += ' ';
                }
                else{
                        lcdOutput += code[i/2];
                }
        }
        lcd.print(lcdOutput);
}

void receiveEvent(int howMany) {
        String message = "";
        while (Wire.available()) { // loop through all but the last
                char c = Wire.read();
                message += c;
                //Serial.println((char)Wire.read());
        }

        if(message.equals("START")) {
                bStart = true;
        }
}

void requestEvent(){
        if(bStart == false) {
                Wire.write(START.c_str());
        }else if(bTask == false) {
                Wire.write(TASK.c_str());
        }else if(bDone == false) {
                Wire.write(DONE.c_str());
        }else if(bDone == true) {
                Wire.write(networkCode.c_str());
        }
}

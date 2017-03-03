#include "Message.h"
#include <string>
#include <iostream>

Message::Message(string text){
        if (isValidMessage(text)) {
                this->text = text;
        }else{
                cout << "ERROR, MESSAGE IS NOT VALID (CONSTRUCTOR)" << endl;
        }
};

bool Message::isValidMessage(string text){
        if (text[0] == START_DELIM && text[text.length() - 1] == END_DELIM) {
                if (text.find(TO_FROM_DELIM) != -1 && text.find(HDR_BODY_DELIM) != -1 && text.find(CMD_MSG_DELIM) != -1) {
                        return true;
                }
        }
        return false;
}

string Message::getSender(){
        return text.substr(text.find(START_DELIM) + 1, text.find(TO_FROM_DELIM) - (text.find(START_DELIM) + 1));
}
string Message::getRecipient(){
        return text.substr(text.find(TO_FROM_DELIM)+1, text.find(HDR_BODY_DELIM) - (text.find(TO_FROM_DELIM) + 1));
}
string Message::getCommand(){
        return text.substr(text.find(HDR_BODY_DELIM)+1, text.find(CMD_MSG_DELIM) - (text.find(HDR_BODY_DELIM) + 1));
}
string Message::getBody(){
        return text.substr(text.find(CMD_MSG_DELIM)+1, text.find(END_DELIM) - (text.find(CMD_MSG_DELIM) + 1));
}

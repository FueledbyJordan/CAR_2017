#include <string>
#include <iostream>
#ifndef MESSAGE_H
#define MESSAGE_H

using namespace std;

class Message {

public:
        Message(string text);

        string getSender();
        string getRecipient();
        string getCommand();
        string getBody();

private:
        static const char START_DELIM = '#';
        static const char TO_FROM_DELIM = '_';
        static const char HDR_BODY_DELIM = '@';
        static const char CMD_MSG_DELIM = ':';
        static const char END_DELIM = '$';

        string text;

        bool isValidMessage(string text);
};

#endif //MESSAGE_H

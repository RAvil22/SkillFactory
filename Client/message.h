#pragma once
#include <iostream>
#include <memory>
#include <chrono>
#include <fstream>

using namespace std;

class Message{
public:
    Message(void) = delete;
    Message(string text, unsigned int sender) : messageText_{text},
                messageSender_{sender}, messageSendTime_{1}, messageSendStatus{false} {}

    string getText(void){return this->messageText_;}
    unsigned int getMessageSender(void){return this->messageSender_;}
    time_t getMessageSendTime(void){return this->messageSendTime_;}
    bool getMessageSendStatus(void){return this->messageSendStatus;}

    unsigned int getUserID(void){return this->messageSender_;}
    friend ostream& operator<< (ostream &out, const Message &message);
protected:
    unsigned int messageSender_;
    time_t messageSendTime_;
    bool messageSendStatus;
    string messageText_;
};

/*class EncryptedMessage final : public Message{
public:
    EncryptedMessage() = delete;
    EncryptedMessage(string, unsigned int, unsigned int); //Текст сообщения, ID отправителя, открытый ключ шифрования
    EncryptedMessage(string, unsigned int, string, unsigned int); //Текст сообщения, ID отправителя, Адрес прилагаемого файла, открытый ключ шифрования
private:
    unsigned long long* encryptedText_;
};*/

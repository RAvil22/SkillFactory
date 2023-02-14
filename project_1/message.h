#pragma once
#include <iostream>
#include <memory>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

class Message{
public:
    Message(void) = delete;
    Message(std::string text, unsigned int sender) :
                messageSender_{sender}, messageSendTime_{0}, messageText_{text}  {this->messageSendTime_ = time(nullptr);}
    Message(std::string text, unsigned int sender, time_t sendTime) :
        messageSender_{ sender }, messageSendTime_{ sendTime }, messageText_{ text } {}

    string getText(void){return this->messageText_;}
    unsigned int getMessageSender(void){return this->messageSender_;}
    time_t getMessageSendTime(void){return this->messageSendTime_;}

protected:
    unsigned int messageSender_;
    time_t messageSendTime_;
    string messageText_;
};

/*class EncryptedMessage final : public Message{
public:
    EncryptedMessage() = delete;
    EncryptedMessage(string, unsigned int, unsigned int); //Текст сообщения, ID отправителя, ключ шифрования
private:
    unsigned long long* encryptedText_;
};*/

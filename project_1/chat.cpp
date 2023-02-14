#include "chat.h"

using namespace std;

/*Ìåòîäû ÀÁÊ Chat*/
Chat::Chat(const unsigned int chatID, const unsigned int chatType) : chatID_{chatID},  unreadMessages_{0}, lastUpdate_{time(nullptr)}, chatType_{chatType}  {}

const unsigned int Chat::getChatID(void) const{return this->chatID_;}

void Chat::setChatName(string chatName){
    if(chatName.size() >= 128)return;
    else{
        auto diff{128 - chatName.size()};
        if(diff){
            unsigned char plug = 127;
            for(int i{0}; i < diff; ++i)chatName += plug;
        }
    }

    fstream chatFile(this->fileName_, ios::in | ios::out);
    if(chatFile.is_open()){
        chatFile.seekp(sizeof(unsigned int) + sizeof(unsigned int) + sizeof(time_t),ios::beg);
        for(int i{0}; i < chatName.size(); ++i)chatFile.write(&chatName[i], sizeof(chatName[i]));
        chatFile.close();
    }
    else{throw NoOpen(this->fileName_);}
}

const string Chat::getChatName(void){return this->chatName_;}

string Chat::getMessageText(unsigned int num){
    if(num >= this->messages_.size()){throw -1;}
    auto iter = this->messages_.begin();
    advance(iter, num);
    return (*iter)->getText();
}

 unsigned int Chat::getMessageSender(unsigned int num){
    if(num >= this->messages_.size()){throw -1;}
    auto iter = this->messages_.begin();
    advance(iter, num);
    return (*iter)->getMessageSender();
}

 time_t Chat::getMessageSendTime(unsigned int num){
     if(num >= this->messages_.size()){throw -1;}
     auto iter = this->messages_.begin();
     advance(iter, num);
     return (*iter)->getMessageSendTime();
 }

unsigned int Chat::size(void){
    auto result{this->messages_.size()};
    return result;
}

shared_ptr<Message> Chat::getLastMessage() {
    bool emptyness{this->messages_.empty()};
    if(!emptyness){
        auto last = this->messages_.end();
        --last;
        return *last;
    }
    else return nullptr;

}

list<shared_ptr<Message>> Chat::getAllMessages(void){return this->messages_;}

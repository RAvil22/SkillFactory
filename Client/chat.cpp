#include "chat.h"

using namespace std;

/*Методы АБК Chat*/
Chat::Chat(const unsigned int chatID) : chatID_{chatID},  unreadMessages_{0} {}

const unsigned int Chat::getChatID(void) const{return this->chatID_;}

void Chat::setChatName(const string chatName){
    this->chatName_ = chatName;
}

const string Chat::getChatName(void){return this->chatName_;}

string Chat::getMessageText(unsigned int num){
    if(num >= this->messages_.size()){throw -1;}
    auto iter = this->messages_.begin();
    advance(iter, num);
    return iter->getText();
}

bool Chat::removeMessage(unsigned int num){
    if(num >= this->messages_.size() && num < 0){return false;}
    auto iter = this->messages_.begin();
    advance(iter, num);
    this->messages_.erase(iter);
    return true;
}

unsigned int Chat::size(void){
    return this->messages_.size();
}

/*Методы класса PublicChat*/
PublicChat::PublicChat(unsigned int chatID, unsigned int chatOwnerID) : Chat(chatID), chatOwnerID_{chatOwnerID} {}

void PublicChat::addMessage(Message mes){
    this->messages_.push_front(mes);
}

const unsigned int PublicChat::getPublicChatOwner(void){return this->chatOwnerID_;}








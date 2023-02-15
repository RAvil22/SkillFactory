#include "user.h"

bool User::sendMessageToChat(shared_ptr<Message> message, unsigned int chatID){
    auto iter = searchUserChat(chatID);
    if(iter != this->userChats_.end()){
        return (* iter)->addMessage(std::move(message));
    }
    else return false;
}

bool User::removeMessageFromChat(unsigned int messageNum, unsigned int chatID){
    auto iter{ searchUserChat(chatID) };
    if(iter != this->userChats_.end()){
        (*iter)->removeMessage(messageNum, this->userID_);
        return true;
    }
    else return false;
}

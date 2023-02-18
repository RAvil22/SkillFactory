#include "user.h"

bool User::createPublicChat(void){
    //???????? ??????? ? ?????? ????
    unsigned int freeChatNum{ this->getFreeChat() };
    shared_ptr<PublicChat> temp = make_shared<PublicChat>(freeChatNum, this->getUserID());
    time_t lastUpdate = temp->getChatLastUpdate();
    //?????????? ?????? ? ???? ????? ????????????
    ofstream userChats;
    string fileName{ "user_chats_" + std::to_string(this->userID_) + ".txt" };
    userChats.open(fileName, ios::app);
    userChats.write((char*)&freeChatNum, sizeof(freeChatNum));
    userChats.write((char*)&lastUpdate, sizeof(lastUpdate));
    userChats.close();

    //?????????? ??????? ???? ? ??????
    this->userChats_.push_back(std::move(temp));
    return true;
}

bool User::createPrivateChat(unsigned int calledUserID){
    unsigned int freeChatNum{ this->getFreeChat() };
    shared_ptr<PrivateChat> temp = make_shared<PrivateChat>(freeChatNum, this->userID_, calledUserID);
    time_t lastUpdate = temp->getChatLastUpdate();

    this->userChats_.push_back(std::move(temp));

    string firstUserChatsFileName{"user_chats_" + to_string(this->userID_) + ".txt"};
    string secondUserChatsFileName{"user_chats_" + to_string(calledUserID) + ".txt"};

    ofstream firstUserChatsFile{firstUserChatsFileName, ios::app};
    firstUserChatsFile.write((char*)&freeChatNum, sizeof(freeChatNum));
    firstUserChatsFile.write((char*)&lastUpdate, sizeof(lastUpdate));
    firstUserChatsFile.close();

    ofstream secondUserChatsFile{secondUserChatsFileName, ios::app};
    secondUserChatsFile.write((char*)&freeChatNum, sizeof(freeChatNum));
    secondUserChatsFile.write((char*)&lastUpdate, sizeof(lastUpdate));
    secondUserChatsFile.close();

    return true;
}

bool User::removeOwnedPublicChat(const unsigned int chatID){
    // ????? ??? ? ?????? ???????????????? ?????
    // ????????? ???????????? ?? ???????? ?????
    // ???? ???????????? ??????? ?????, ???????
    auto iter = searchUserChat(chatID);
    if(iter != this->userChats_.end()){
       //auto temp = dynamic_cast<PublicChat>(iter);
       shared_ptr<PublicChat> temp = dynamic_pointer_cast<PublicChat>((*iter));
       if(temp->getPublicChatOwner() == this->userID_){
            //Удалить из файла чатов пользователя
            string fileName{ "Chat_" + to_string(temp->getChatID()) + ".txt" };
            ifstream check(fileName);
            if (check.is_open()) {
                check.close();
                remove(fileName.c_str());
                this->userChats_.erase(iter);
                return true;
            }
            else{throw NoOpen(fileName);}

       }
    }
    return false;
}

bool User::removeNonOwnedPublicChat(const unsigned int chatID){
    auto iter = searchUserChat(chatID);
    if(iter != this->userChats_.end()){
        //Удалить из файла чатов пользователя
        this->userChats_.erase(iter);
        return true;
    }
    else{return false;}
}

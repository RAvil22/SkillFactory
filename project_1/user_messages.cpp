#include "user.h"

bool User::sendMessageToChat(shared_ptr<Message> message, unsigned int chatID){
    auto iter = searchUserChat(chatID);
    if(iter != this->userChats_.end()){
        unsigned int fileChatID;
        time_t lastUpdate{message->getMessageSendTime()};
        (* iter)->addMessage(std::move(message));
        //В файле user_chats_().txt найти ID чата в который отправляется сообщение и обновить дату последнего изменения чата на дату сообщения
        fstream userChatsFile("user_chats_" + to_string(this->userID_) + ".txt");
        while(userChatsFile.read((char*)&fileChatID, sizeof(fileChatID))){
            if(chatID != fileChatID){userChatsFile.seekg(sizeof(time_t),ios::cur);}
            else {userChatsFile.write((char*)&lastUpdate, sizeof(lastUpdate));break;}
        }
        userChatsFile.close();
        return true;
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

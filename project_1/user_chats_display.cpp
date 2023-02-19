#include "user.h"

void User::userSettings(unsigned int upload, string name, bool vis){ //?????????? ???????????? ?????????, ??? ????????????, ?????????
    this->showXUploadmessages = upload;
    this->userName_ = name;
    this->visability_ = vis;
}

bool User::showLastChatMessages(unsigned int chatID, const unsigned int showNum){
    auto iter = searchUserChat(chatID);
    if(iter != this->userChats_.end() && showNum < INT_MAX){
        if((*iter)->size() >= showNum){
            for(int i{static_cast<int> (showNum) - 1}; i >= 0; --i){
                cout << (*iter)->getMessageText(i) << endl;
            }
        }
        else{
            for(int i{static_cast<int>((*iter)->size())-1}; i >= 0; --i){
                cout << (*iter)->getMessageText(i) << endl;
            }
        }
        return true;
    }
    else return false;
}

bool User::uploadChatMessages(unsigned int chatID, list<shared_ptr<Message>>& chatMessages){
    //????? ?????? ???
    auto chat = searchUserChat(chatID);
    auto result = updateChat(chat);
    auto chatSize{(*chat)->size()};
    chatMessages = getAllChatMessages(chatID);
    return result;
}

bool User::updateChat(list<shared_ptr<Chat>>::iterator chat){
    if (*chat) {
        //???? ??? ??????????, ??????? ?? ?????????? ????????? ? ???? ???????????, ????? ? ?????.
        unsigned int userSender;
        time_t userTime;
        string userText;

        auto lastMes = (*chat)->getLastMessage();
        if(lastMes){
            userSender = lastMes->getMessageSender();
            userTime = lastMes->getMessageSendTime();
            userText = lastMes->getText();
        }
        else{
            userSender = 0;
            userTime = 0;
            userText = "";
        }

        //??????? ???? ????
        string chatFileName{"Chat_" + to_string((*chat)->getChatID()) + ".txt"};
        ifstream chatFile{chatFileName};

        if (chatFile.is_open()) {
            unsigned int chatType;
            chatFile.read((char*)&chatType,sizeof(chatType));
            switch (chatType) {
                case 1:
                    chatFile.seekg(144, ios::beg);
                    break;
                case 2:
                    chatFile.seekg(20, ios::beg);
                    break;
                default:
                    chatFile.close();
                    throw NoChatType(chatType);
                    break;
            }
            unsigned int currentSender;
            time_t currentTime;
            unsigned int size_;
            string currentText;
            char c;
            //????? ? ????? ??? ?????????
            while(chatFile.read((char*)&currentSender, sizeof(currentSender)) && chatFile.read((char*)&currentTime, sizeof(currentTime))
                   && chatFile.read((char*)&size_, sizeof(size_))) {
                currentText = "";
                for (unsigned int i{ 0 }; i < size_; ++i) {
                    chatFile.read((char*)&c, sizeof(c));
                    currentText += c;
                }
                //?? ?????????? ?? ????????? ????????? ? ?????, ??????? ?????? ????????? ? ???????? ? ???, ????????? ??????? ? ????? UnreadMessages ????
                if (currentTime > userTime){
                    shared_ptr<Message> temp = make_shared<Message>(currentText, currentSender, currentTime);
                    (*chat)->addMessage(temp); //?????? ?????, ????? ??????? ?? ????????-???????? ?????. ????????!
                    (*chat)->incUnreadMessages();
                }
            }
            chatFile.close();
            return true;
        }
        else {throw NoOpen(chatFileName);}
    }
    else return false;
}

bool User::updateChats(){
    auto chat = this->userChats_.begin();
    while(chat != userChats_.end())updateChat(chat);
    return true;
}

list<shared_ptr<Message>> User::getAllChatMessages(unsigned int chatID){
    auto chat = searchUserChat(chatID);
    return (*chat)->getAllMessages();
}

#include "user.h"

using namespace std;

User::User(unsigned int id, string password) : userID_{id}, password_{password}, userName_{""},showXUploadmessages{20}, visability_{true} {
    ifstream userFile("user_" + std::to_string(this->userID_) + ".txt");
    ifstream userChatsFile("user_chats_" + to_string(this->userID_) + ".txt");
    if(userFile.is_open() && userChatsFile.is_open()){
        userFile.close();
        userChatsFile.close();
        fillProfileFromFiles();
    }
    else{throw NoOpen("User " + std::to_string(this->userID_) + " files cannot be opened!");}
}

User::User(unsigned int id, string password, string login) : userID_{id}, password_{password}, userName_{login},showXUploadmessages{20}, visability_{true} {
    ifstream userFile("user_" + std::to_string(this->userID_) + ".txt");
    ifstream userChatsFile("user_chats_" + to_string(this->userID_) + ".txt");
    if(userFile.is_open() && userChatsFile.is_open()){throw WrongOpen("user_" + std::to_string(this->userID_) + ".txt");}
    else createProfileFiles();
}

void User::fillProfileFromFiles(){
    string userFileName{"user_" + std::to_string(this->userID_) + ".txt"};
    string userChatsFileName("user_chats_" + to_string(this->userID_) + ".txt");
    ifstream userFile(userFileName);
    ifstream userChatsFile(userChatsFileName);
    if(userFile.is_open() && userChatsFile.is_open()){
        userFile.close();
        userChatsFile.close();
        fillProfileSettingsFromFile();
        fillProfileChatsFromFile();
    }
    else{throw NoOpen(userFileName + " and/or " + userChatsFileName);}
}

void User::fillProfileSettingsFromFile(){
    string userFileName{"user_" + std::to_string(this->userID_) + ".txt"};
    ifstream userFile(userFileName);
    if(userFile.is_open()){
       //???????? ?? ??????? ?????? ? ?????
        unsigned int fileID;
        string filePassword;
        string fileUserName;
        unsigned int fileShowXUploadmessages;
        bool fileVisability;
        unsigned int blackID;
        unsigned int knownID;
        unsigned int size_;
        char c;

        //?????? ID
        userFile.read((char*)&fileID, sizeof(fileID));
        if(this->userID_ != fileID){}//??????? ???????????

        //?????? ??????
        userFile.read((char*)&size_, sizeof(size_));
        for (unsigned int i{ 0 }; i < size_; ++i) {
            userFile.read((char*)&c, sizeof(c));
            filePassword += c;
        }
        if(this->password_ != filePassword){}//??????? ???????????

        //?????? ???????????????? ????????(???, ?????? ?????????, ?????????)
        userFile.read((char*)&size_, sizeof(size_));
        for (unsigned int i{ 0 }; i < size_; ++i) {
            userFile.read((char*)&c, sizeof(c));
            fileUserName += c;
        }
        userFile.read((char*)&fileShowXUploadmessages, sizeof(fileShowXUploadmessages));
        userFile.read((char*)&fileVisability, sizeof(fileVisability));
        this->userName_ = fileUserName;
        this->showXUploadmessages = fileShowXUploadmessages;
        this->visability_ = fileVisability;

        //?????? ??????? ??????
        userFile.read((char*)&size_, sizeof(size_));
        for (unsigned int i{ 0 }; i < size_; ++i) {
            userFile.read((char*)&blackID, sizeof(blackID));
            this->blackList_.push_back(blackID);
        }

        //?????? ?????? ???????? ?????????????
        userFile.read((char*)&size_, sizeof(size_));
        for (unsigned int i{ 0 }; i < size_; ++i) {
            userFile.read((char*)&knownID, sizeof(knownID));
            this->knownUsers_.push_back(knownID);
        }

        userFile.close();
    }
    else{throw NoOpen(userFileName);}
}

void User::fillProfileChatsFromFile(){
    string userChatsFileName{"user_chats_" + to_string(this->userID_) + ".txt"};
    ifstream userChatsFile(userChatsFileName);
    if(userChatsFile.is_open()){
        unsigned int chatID;

        while(userChatsFile.read((char*)&chatID,sizeof(chatID))){
            //??????? ???? ???? ? ?????? ("Chat_" + to_string(chatID_) + ".txt")
            string fileName_ = "Chat_" + to_string(chatID) + ".txt";
            ifstream chatFile(fileName_);
            if(chatFile.is_open()){
                    unsigned int chatType{0};
                if(chatFile.is_open()){
                    chatFile.read((char*)&chatType, sizeof(chatType));
                    chatFile.close();
                }
                switch(chatType){
                case 0:
                    break;

                case 1://????? ???
                    {
                        //PublicChat(const unsigned int chatID, const unsigned int chatOwnerID)
                        chatFile.open(fileName_);
                        chatFile.seekg(sizeof(unsigned int), ios::beg);
                        unsigned int chatOwner;
                        chatFile.read((char*)&chatOwner, sizeof(chatOwner));
                        chatFile.close();
                        //?????? ???????? ?? ??????? ? ????? ????????????? ???? ???????? ????????????


                        shared_ptr<PublicChat> temp = make_shared<PublicChat>(chatID, chatOwner);
                        this->userChats_.push_back(std::move(temp));
                        break;
                    }

                case 2://?????? ???
                    {
                       //PrivateChat(unsigned int chatID, unsigned int firstUserID, unsigned int secondUserID)
                        chatFile.open(fileName_);
                        chatFile.seekg(sizeof(unsigned int), ios::beg);
                        unsigned int firstID;
                        unsigned int secondID;
                        chatFile.read((char*)&firstID, sizeof(firstID));
                        chatFile.read((char*)&secondID, sizeof(secondID));
                        chatFile.close();
                        if(firstID == this->userID_ || secondID == this->userID_){
                            shared_ptr<PrivateChat> temp = make_shared<PrivateChat>(chatID, firstID, secondID);
                            this->userChats_.push_back(std::move(temp));
                        }
                        break;
                    }

                default:

                    throw NoChatType(chatType);
                    break;

                }//switch(chatType)
                chatFile.close();
            }//if(chatFile.is_open())
            else{throw NoOpen(fileName_);}//??????? ??????????

        }//while(userChatsFile.read((char*)&chatID,sizeof(chatID)))
        userChatsFile.close();
    }//if(userChatsFile.is_open())
    else{throw NoOpen(userChatsFileName);}//??????? ??????????
}

void User::createProfileFiles(){

    ofstream userFile("user_" + std::to_string(this->userID_) + ".txt");
    //????????? ?????????? ??? ?????? ?????
    int size_;
    char c;
    /*?????? ID*/
        userFile.write((char*)&userID_, sizeof(userID_));

        /*?????? ??????*/
        size_ = this->password_.size();
        userFile.write((char*)&size_, sizeof(size_));
        for(int i{0}; i < size_; ++i){
            c = password_[i];
            userFile.write((char*)&c, sizeof(c));
        }

        //?????? ???????????????? ????????
        size_ = this->userName_.size();
        userFile.write((char*)&size_, sizeof(size_));
        for(int i{0}; i < size_; ++i){
            c = userName_[i];
            userFile.write((char*)&c, sizeof(c));
        }
        userFile.write((char*)&showXUploadmessages, sizeof(showXUploadmessages)); //?????????? ???????????? ?????????
        userFile.write((char*)&visability_, sizeof(visability_)); //????????? ????????????

        //?????? ??????? ?????? ?????????????
        size_ = this->blackList_.size();
        userFile.write((char*)&size_, sizeof(size_));
        auto blackListIter = blackList_.begin();
        while(blackListIter != blackList_.end()){
            userFile.write((char*)&((*blackListIter)), sizeof((*blackListIter)));
            ++blackListIter;
        }

        //?????? ?????? ???????? ?????????????
        size_ = this->knownUsers_.size();
        userFile.write((char*)&size_, sizeof(size_));
        auto knownUsersIter = knownUsers_.begin();
        while(knownUsersIter != knownUsers_.end()){
            auto temp = *knownUsersIter;
            userFile.write((char*)&(*knownUsersIter), sizeof(*knownUsersIter));
            ++knownUsersIter;
        }

        userFile.close();

        //???????? ????? ????? ????????????
        ofstream userChatsFile("user_chats_" + to_string(this->userID_) + ".txt", ios::out);
        auto chatsIter = this->userChats_.begin();
        while (chatsIter != this->userChats_.end()) {
            unsigned int chatID = (*chatsIter)->getChatID();
            userChatsFile.write((char*)&chatID, sizeof(chatID));
            ++chatsIter;
        }
        userChatsFile.close();
}

void User::setUserName(string name){

    ifstream userFile("user_" + std::to_string(this->userID_) + ".txt");
    if(userFile.is_open()){
        this->userName_ = name;
        unsigned int userID;
        userFile.read((char*)&userID, sizeof(userID));

        unsigned int size_;
        userFile.read((char*)&size_, sizeof(size_));

        string password{""};
        char c;
        for(unsigned int i{0}; i < size_; ++i){
            userFile.read((char*)&c, sizeof(c));
            password += c;
        }

        userFile.read((char*)&size_, sizeof(size_));

        string userName{""};
        for(unsigned int i{0}; i < size_; ++i){
            userFile.read((char*)&c, sizeof(c));
            userName += c;
        }
        userName = name;

        unsigned int showUpload;
        userFile.read((char*)&showUpload, sizeof(showUpload));

        bool vis;
        userFile.read((char*)&vis, sizeof(vis));

        userFile.read((char*)&size_, sizeof(size_));
        list<unsigned int>black;
        unsigned int bl;
        for(unsigned int i{0}; i < size_; ++i){
            userFile.read((char*)&bl, sizeof(bl));
            black.push_back(bl);
        }

        userFile.read((char*)&size_, sizeof(size_));
        list<unsigned int>known;
        unsigned int kn;
        for(unsigned int i{0}; i < size_; ++i){
            userFile.read((char*)&kn, sizeof(kn));
            known.push_back(kn);
        }

        userFile.close();

        ofstream userFile{"user_" + std::to_string(this->userID_) + ".txt",ios::out};
        userFile.write((char*)&userID, sizeof(userID));
        size_ = password.size();
        userFile.write((char*)&size_, sizeof(size_));
        for(unsigned int i{0}; i < size_; ++i){
           userFile.write((char*)&password[i], sizeof(password[i]));
        }
        size_ = userName.size();
        userFile.write((char*)&size_, sizeof(size_));
        for(unsigned int i{0}; i < size_; ++i){
           userFile.write((char*)&userName[i], sizeof(userName[i]));
        }
        userFile.write((char*)&showUpload, sizeof(showUpload));
        userFile.write((char*)&vis, sizeof(vis));
        size_= black.size();
        userFile.write((char*)&size_, sizeof(size_));
        /*for(unsigned int i{0}; i < size_; ++i){
           userFile.write((char*)&userName[i], sizeof(userName[i]));
        }*/
        userFile.write((char*)&size_, sizeof(size_));

    }
    else return;
}

void User::setPassword(string password){

    ifstream userFile("user_" + std::to_string(this->userID_) + ".txt");
    if(userFile.is_open()){
        this->password_ = password;
        unsigned int userID;
        userFile.read((char*)&userID, sizeof(userID));

        unsigned int size_;
        userFile.read((char*)&size_, sizeof(size_));

        string pass{""};
        char c;
        for(unsigned int i{0}; i < size_; ++i){
            userFile.read((char*)&c, sizeof(c));
            password += c;
        }
        pass = password;

        userFile.read((char*)&size_, sizeof(size_));

        string userName{""};
        for(unsigned int i{0}; i < size_; ++i){
            userFile.read((char*)&c, sizeof(c));
            userName += c;
        }

        unsigned int showUpload;
        userFile.read((char*)&showUpload, sizeof(showUpload));

        bool vis;
        userFile.read((char*)&vis, sizeof(vis));

        userFile.read((char*)&size_, sizeof(size_));
        list<unsigned int>black;
        unsigned int bl;
        for(unsigned int i{0}; i < size_; ++i){
            userFile.read((char*)&bl, sizeof(bl));
            black.push_back(bl);
        }

        userFile.read((char*)&size_, sizeof(size_));
        list<unsigned int>known;
        unsigned int kn;
        for(unsigned int i{0}; i < size_; ++i){
            userFile.read((char*)&kn, sizeof(kn));
            known.push_back(kn);
        }

        userFile.close();

        ofstream userFile{"user_" + std::to_string(this->userID_) + ".txt",ios::out};
        userFile.write((char*)&userID, sizeof(userID));
        size_ = password.size();
        userFile.write((char*)&size_, sizeof(size_));
        for(unsigned int i{0}; i < size_; ++i){
           userFile.write((char*)&password[i], sizeof(password[i]));
        }
        size_ = userName.size();
        userFile.write((char*)&size_, sizeof(size_));
        for(unsigned int i{0}; i < size_; ++i){
           userFile.write((char*)&userName[i], sizeof(userName[i]));
        }
        userFile.write((char*)&showUpload, sizeof(showUpload));
        userFile.write((char*)&vis, sizeof(vis));
        size_= black.size();
        userFile.write((char*)&size_, sizeof(size_));
        /*for(unsigned int i{0}; i < size_; ++i){
           userFile.write((char*)&userName[i], sizeof(userName[i]));
        }*/
        userFile.write((char*)&size_, sizeof(size_));

    }
    else return;
}

void User::showUserChatIDs(void) {
    for (auto const& i : this->userChats_) {
        cout << i->getChatID() << " ";
    }
    cout << endl;
}

int User::getChatID(const unsigned int num) {
    if (num < this->userChats_.size()) {
        auto iter = this->userChats_.begin();
        for (unsigned int i{ 0 }; i < num; ++i) ++iter;
        return (*iter)->getChatID();
    }
    else return -1;
}

unsigned int User::getChatType(const unsigned int num){
    if(num < this->userChats_.size()){
        auto iter = this->userChats_.begin();
        for (unsigned int i{ 0 }; i < num; ++i) ++iter;
        return (*iter)->getChatType();
    }
}

string User::getChatName(const unsigned int num){
    if(num < this->userChats_.size()){
        auto iter = this->userChats_.begin();
        for (unsigned int i{ 0 }; i < num; ++i) ++iter;
        return (*iter)->getChatName();
    }
}
/*????????/???????? ?????*/////////////////////////////////////////////////////////////

unsigned int User::getFreeChat(void) {
    fstream chatIDs;
    unsigned int result;
    chatIDs.open("chatIDs.txt", ios::in | ios::out);
    if (chatIDs.is_open()) {
        chatIDs.read((char*)&result, sizeof(result));
        chatIDs.seekp(0, ios::beg);
        ++result;
        chatIDs.write((char*)&result, sizeof(result));
        chatIDs.close();
        return result;
    }
    else {
        unsigned int one{ 1 };
        chatIDs.open("chatIDs.txt", ios::out);
        chatIDs.write((char*)&one, sizeof(one));
        chatIDs.close();
        return one;
    }
}

bool User::createPublicChat(void){
    //???????? ??????? ? ?????? ????
    unsigned int freeChatNum{ this->getFreeChat() };
    shared_ptr<PublicChat> temp = make_shared<PublicChat>(freeChatNum, this->getUserID());

    //?????????? ?????? ? ???? ????? ????????????
    ofstream userChats;
    string fileName{ "user_chats_" + std::to_string(this->userID_) + ".txt" };
    userChats.open(fileName, ios::app);
    userChats.write((char*)&freeChatNum, sizeof(freeChatNum));
    userChats.close();

    //?????????? ??????? ???? ? ??????
    this->userChats_.push_back(std::move(temp));
    return true;
}

void User::setChatName(unsigned int num, string name){
    auto iter = this->userChats_.begin();
    if(num >= this->userChats_.size())return;
    advance(iter, num);
    (*iter)->setChatName(name);
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
            string fileName{ "PubCh_" + to_string(temp->getChatID()) + ".txt" };
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
        this->userChats_.erase(iter);
        return true;
    }
    else{return false;}
}

bool User::createPrivateChat(unsigned int calledUserID){
    unsigned int freeChatNum{ this->getFreeChat() };
    string firstUserChatsFileName{"user_chats_" + to_string(this->userID_) + ".txt"};
    string secondUserChatsFileName{"user_chats_" + to_string(calledUserID) + ".txt"};

    ofstream firstUserChatsFile{firstUserChatsFileName, ios::app};
    firstUserChatsFile.write((char*)&freeChatNum, sizeof(freeChatNum));
    firstUserChatsFile.close();

    ofstream secondUserChatsFile{secondUserChatsFileName, ios::app};
    secondUserChatsFile.write((char*)&freeChatNum, sizeof(freeChatNum));
    secondUserChatsFile.close();

    shared_ptr<PrivateChat> temp = make_shared<PrivateChat>(freeChatNum, this->userID_, calledUserID);
    this->userChats_.push_back(std::move(temp));
    return true;
}

/*????? ????*/////////////////////////////////////////////////////////////
list<shared_ptr<Chat>>::iterator User::searchUserChat(const unsigned int chatID){
    auto iter = this->userChats_.begin();
    while(iter != this->userChats_.end()){
        if((*iter)->getChatID() == chatID) {
            return iter;
        }
        ++iter;
    }
    return iter;
}

unsigned int User::searchChatID(const unsigned int chatID){ //??????? ID ????
    auto iter{ searchUserChat(chatID) };
    if (iter != this->userChats_.end()) return  (*iter)->getChatID();
    else {
        string fileName{ "PubCh_" + to_string(chatID) + ".txt" };
        ifstream file(fileName);
        if (file.is_open()) { file.close(); return chatID; }
        else return 0;
    }
    return 0;
}

list<unsigned int> User::searchChatName(const string chatName){ //??????? ID ????? ?????????? ?????
    list<unsigned int> result;
    //????? ?????  ?????????? ????
    unsigned int lastChatID{ 1000 };
    char c;
    unsigned int size;
    auto cnSize{chatName.size()};
    string text;
    unsigned int id;
    for (unsigned int i{ 1 }; i < lastChatID; ++i) {
        string fileName{ "PubCh_" + to_string(i) + ".txt" };
        ifstream file(fileName);
        if (file.is_open()) {
            file.seekg(sizeof(unsigned int) + sizeof(time_t) + sizeof(unsigned int) + sizeof(time_t));
            file.read((char*)&size, sizeof(size));
            for (unsigned int j{ 0 }; j < size; ++j) {
                file.read((char*)&c, sizeof(char));
                text += c;
            }
            for (unsigned int i{ 0 }; i < cnSize; ++i) {
                if (text[i] != chatName[i])break;
                if (i == cnSize - 1) {
                    file.seekg(ios::beg);
                    file.read((char*)&id, sizeof(id));
                    result.push_back(id);
                }
            }
            file.close();
        }
        else{throw NoOpen(fileName);}
    }
    return result;
}

bool User::joinToChat(unsigned int chatID) {
    auto iter = this->userChats_.begin();
    auto end_ = this->userChats_.end();
    while (iter != end_) {
        if ((*iter)->getChatID() == chatID) {
            return true;
        }
    }

    //???????? ID ????????? ????
    string chatFileName{ "PubCh_" + to_string(chatID) + ".txt" };
    string chatUsersFileName{ "PubCh_" + to_string(chatID) + "_users.txt" };
    unsigned int chatOwner{0};
    ifstream chatFile(chatFileName);
    ofstream chatUsersFile(chatUsersFileName, ios::app);

    if (chatFile.is_open() && chatUsersFile.is_open()){
        chatFile.read((char*)&chatOwner, sizeof(chatOwner));
        chatFile.close();
        chatUsersFile.write((char*)&this->userID_, sizeof(this->userID_));
        chatUsersFile.close();
        shared_ptr<PublicChat> temp = make_unique<PublicChat>(chatID, chatOwner);
        this->userChats_.push_back(std::move(temp));
        iter = this->userChats_.end();
        --iter;
        shared_ptr<Message> last = temp->getLastMessage();
        temp->updateChatFromFiles(std::move(last));
        ofstream userChatsFile("user_chats_" + std::to_string(this->userID_) + ".txt", ios::app);
        userChatsFile.write((char*)&chatID, sizeof(chatID));
        userChatsFile.close();
        return true;
    }
    else return false;

}

bool User::leaveChat(unsigned int chatID) {
    auto iter = this->userChats_.begin();
    auto end_ = this->userChats_.end();
    while (iter != end_) {
        if ((*iter)->getChatID() == chatID) {
            shared_ptr<PublicChat> temp = dynamic_pointer_cast<PublicChat>((*iter));
            temp->removeUser(this->userID_);
            this->userChats_.erase(iter);
            return true;
        }
    }
    return false;
}

bool User::sendMessageToChat(shared_ptr<Message> message, unsigned int chatID){
    auto iter = searchUserChat(chatID);
    if(iter != this->userChats_.end()){
        return (* iter)->addMessage(std::move(message));
    }
    else return false;
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
                }
            }
            chatFile.close();
            return true;
        }
        else {throw NoOpen(chatFileName);}
    }
    else return false;
}

list<shared_ptr<Message>> User::getAllChatMessages(unsigned int chatID){
    auto chat = searchUserChat(chatID);
    return (*chat)->getAllMessages();
}

bool User::uploadChatMessages(unsigned int chatID, list<shared_ptr<Message>>& chatMessages){
    //????? ?????? ???
    auto chat = searchUserChat(chatID);
    auto result = updateChat(chat);
    auto chatSize{(*chat)->size()};
    chatMessages = getAllChatMessages(chatID);
    return result;
}

bool User::updateChats(){
    auto chat = this->userChats_.begin();
    while(chat != userChats_.end())updateChat(chat);
    return true;
}

void User::userSettings(unsigned int upload, string name, bool vis){ //?????????? ???????????? ?????????, ??? ????????????, ?????????
    this->showXUploadmessages = upload;
    this->userName_ = name;
    this->visability_ = vis;
}

bool User::removeMessageFromChat(unsigned int messageNum, unsigned int chatID){
    auto iter{ searchUserChat(chatID) };
    if(iter != this->userChats_.end()){
        (*iter)->removeMessage(messageNum, this->userID_);
        return true;
    }
    else return false;
}

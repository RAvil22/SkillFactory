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
            //userChatsFile.seekg(sizeof(time_t), ios::cur) //ѕропустить данные о последнем открытии чата
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



void User::setChatName(unsigned int num, string name){
    auto iter = this->userChats_.begin();
    if(num >= this->userChats_.size())return;
    advance(iter, num);
    (*iter)->setChatName(name);
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



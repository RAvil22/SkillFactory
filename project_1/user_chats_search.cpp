#include "user.h"

unsigned int User::getChatID(const unsigned int num) {
    if (num < this->userChats_.size()) {
        auto iter = this->userChats_.begin();
        for (unsigned int i{ 0 }; i < num; ++i) ++iter;
        return (*iter)->getChatID();
    }
    else return 0;
}

string User::getChatName(const unsigned int num){
    if(num < this->userChats_.size()){
        auto iter = this->userChats_.begin();
        for (unsigned int i{ 0 }; i < num; ++i) ++iter;
        return (*iter)->getChatName();
    }
}

unsigned int User::getChatType(const unsigned int num){
    if(num < this->userChats_.size()){
        auto iter = this->userChats_.begin();
        for (unsigned int i{ 0 }; i < num; ++i) ++iter;
        return (*iter)->getChatType();
    }
}

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
        string fileName{ "Chat_" + to_string(chatID) + ".txt" };
        ifstream file(fileName);
        if (file.is_open()) { file.close(); return chatID; }
        else return 0;
    }
    return 0;
}

list<unsigned int> User::searchChatName(const string chatName){ //??????? ID ????? ?????????? ?????
    list<unsigned int> result;
    //????? ?????  ?????????? ????
    unsigned int lastChatID{};//Взять из файла chatIDs
    ifstream chatIDs{"chatIDs.txt"};
    if(chatIDs.is_open()){chatIDs.read((char*)&lastChatID, sizeof(lastChatID));chatIDs.close();}
    else throw NoOpen("chatIDs.txt");
    char c;
    unsigned int size;
    auto cnSize{chatName.size()};
    string text;
    unsigned int id;
    for (unsigned int i{ 1 }; i < lastChatID; ++i) {
        string fileName{ "Chat_" + to_string(i) + ".txt" };
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

void User::showUserChatIDs(void) {
    for (auto const& i : this->userChats_) {
        cout << i->getChatID() << " ";
    }
    cout << endl;
}







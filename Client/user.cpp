#include "user.h"

using namespace std;

User::User(unsigned int id, string password) : userID_{id}, password_{password} {}


/*��������/�������� �����*/////////////////////////////////////////////////////////////
bool User::createPublicChat(void){
    //��������� � ������� �� ��������� ID ����
    //UserChat.userChatID_ = this->userID_ + size(userChats_);
    //UserChat temp(userChatID_ = this->userID_ + size(this->userChats_), userChat{this->userID_ + size(this->userChats_, this->userID_ );
    UserChat temp(this->getUserID(), getNumberOfChats());
    this->userChats_.push_back(temp);
    //�������� ���������� ������ �� ChatID
    return true;
}

bool User::removeOwnedChat(const unsigned int chatID){
    // ����� ��� � ������ ���������������� �����
    // ��������� ������������ �� �������� �����
    // ���� ������������ ������� �����, ������� ���
    auto iter = searchUserChat(chatID);
    if(iter != this->userChats_.end()){
       auto temp = *iter;
       if(temp.userChat.getPublicChatOwner() == this->userID_){
            //�������� ������� ������� �� �������� ���� �� ���� �����������
            this->userChats_.erase(iter);
            return true;
       }
    }
    return false;
}

bool User::removeNonOwnedChat(const unsigned int chatID){
    auto iter = searchUserChat(chatID);
    if(iter != this->userChats_.end()){
        this->userChats_.erase(iter);
        return true;
    }
    else{return false;}
}


/*����� ����*/////////////////////////////////////////////////////////////
list<UserChat>::iterator User::searchUserChat(const unsigned int chatID){
    auto iter = this->userChats_.begin();
    while(iter != this->userChats_.end()){
        auto temp = *iter;
        if(temp.chatID_ == chatID){
            return iter;
        }
        ++iter;
    }
    return iter;
}

unsigned int User::searchChatID(const unsigned int chatID){ //������� ID ����
    //��������� �� ������� ���� � ������� ������������ (searchUserChat)
    //��������� ������ �� ������
    //������� ����� �������
}

list<string> User::searchChatName(const string){ //������� ID ����� ���������� �����
    //��������� �� ������� ���� � ������� ������������ (searchUserChat)
    //��������� ������ �� ������
    //������� ����� �������
}

/*�����������/��������� �����*/////////////////////////////////////////////////////////////
bool User::joinToChat(unsigned int chatID){
    //����� ��� � ID chatID
    //������ ������ �� �������������
    //��� ������������� ������, ������� false
    //��� ������������� ������, �������� � ������ userChats ��������� userChat c ID ���� � ������ showXMessages ��������� ���������
    //������� true
}

bool User::leaveChat(const unsigned int chatID){
    //��������� �� ������� ���� � ������� ������������ (searchUserChat)
    //���� ��� ���, ������� false
    //���� ����, � ������������ �������� ����, ������� removeOwnedChat, ������� true
    //���� ����, � ������������ �� �������� ����, ��������� ������� ������ �� ��������
    //���� ������ �� ���� �����, ������� false
    //���� ������ ���� �����, ������� removeNonOwnedChat, ������� true
}

bool User::inviteToChat(const unsigned int chatID, const unsigned int userID){
    //��������� �� ������� ������������ � ��������� ID(��������� ������ �� ������)
    //���� ������ ���, ��� �� ��������� ����������� ������� false
    //���� ����� ����, ��������� ������-����������� �� ������
}

bool User::receiveToChat(const unsigned int chatID, const unsigned int userID){
    //��������� �� ������� ������������ � ��������� ID(��������� ������ �� ������)
    //���� ������ ���, ������� false
    //���� ����� ����, ��������� ������� ������-����� � ��� (������ ������ �������� ID ������������� ������������ � ���������� userIDs_)
    //return true
}

bool User::sendMessageToChat(Message message, unsigned int chatID){
    ///����� ������ ���������������� ���
    auto iter = searchUserChat(chatID);

    if(iter != this->userChats_.end()){
        ///���� ��� ����������, �������� ��������� � ������
        iter->userChat.addMessage(message);
        ///������������ ��� ����� ����(����� � ������� ���� ������� ��� �������������)
        string fileaddr;
        time_t timepoint = time(nullptr);
        auto time = ctime(&timepoint);
        string date;
        for(int i{0}; i < 24; ++i){
            if((i >= 4 && i <= 6) || (i >= 8 && i <= 9) || (i >= 20 && i <= 23))date += time[i];
        }
        fileaddr = to_string(this->getUserID()) + "_" + to_string(iter->userChat.getChatID()) + "_" + date + ".txt";
        //cout << fileaddr << endl;
        ifstream check(fileaddr);
        if(!check.is_open()){
            ofstream file(fileaddr, ios::out);
            file << "Time\t";
            file << time;
            file << "UserID\t";
            file << getUserID() << endl;
            file << "Message text\t";
            file << message.getText() << endl << endl;
            file.close();
        }
        else{
            check.close();
            ofstream file(fileaddr, ios::app);
            file << "Time\t";
            file << time;
            file << "UserID\t";
            file << getUserID() << endl;
            file << "Message text\t";
            file << message.getText() << endl << endl;
            file.close();
        }
        return true;
    }

    else{
        //cout << "False" << endl;
        return false;
    }
}

bool User::showLastChatMessages(unsigned int chatID, const unsigned int showNum){
    auto iter = searchUserChat(chatID);
    if(iter != this->userChats_.end() && showNum < INT_MAX){
        if(iter->userChat.size() >= showNum){
            for(int i{showNum-1}; i >= 0; --i){
                cout << iter->userChat.getMessageText(i) << endl;
            }
        }
        else{
            for(int i{iter->userChat.size()-1}; i >= 0; --i){
                cout << iter->userChat.getMessageText(i) << endl;
            }
        }
        return true;
    }
    else return false;
}


























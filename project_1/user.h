#pragma once
#include "chat.h"
#include <fstream>
#include <ctime>
#include <cstdio>
#include <string>
#include <cstring>

using namespace std;


class User{
public:
    User(unsigned int userID, string password);
    User(unsigned int userID, string password, string login); // ID, password, login  //ok

    /*�������*/
    void setUserName(string userName);//ok
    void setChatName(unsigned int num, string name);
    void setPassword(string password);

    /*�������*/
    const string getUserName(void){return this->userName_;} //ok
    const string getUserPassword(void){return this->password_;}
    const unsigned int getUserID(void){return this->userID_;} //ok
    unsigned int getNumberOfChats(void){return userChats_.size();} //ok

    /*��������/�������� �����*/
    bool createPublicChat(void); //ok
    bool createPrivateChat(unsigned int calledUserID);
    bool removeOwnedPublicChat(const unsigned int); //ok
    bool removeNonOwnedPublicChat(const unsigned int); //ok


    /*����� ����*/
    unsigned int getChatID(const unsigned int);
    string getChatName(const unsigned int);
    unsigned int getChatType(const unsigned int);
    list<shared_ptr<Chat>>::iterator searchUserChat(const unsigned int); //ok
    unsigned int searchChatID(const unsigned int); //������� ID ����
    list<unsigned int> searchChatName(const string); //������� ID ���������� �����
    void showUserChatIDs(void);

    /*�����������/��������� �����*/
    bool joinToChat(const unsigned int chatID);
    bool leaveChat(const unsigned int chatID);

    /*��������/�������� ���������*/
    bool sendMessageToChat(shared_ptr<Message> message, unsigned int chatID);
    bool removeMessageFromChat(unsigned int messageNum, unsigned int chatID); //������ �������� �� �������� �����

    /*����������� ����������� �����*/
    void userSettings(unsigned int, string, bool); //���������� ������������ ���������, ��� ������������, ���������
    bool showLastChatMessages(unsigned int chatID, unsigned int showNum);
    bool uploadChatMessages(unsigned int chatID, list<shared_ptr<Message>>& chatMessages);
    bool updateChat(list<shared_ptr<Chat>>::iterator);
    bool updateChats(); //������ � ����������� ������� ������������ �� ������� (���� ��� � �������, ���� �� �������������� ���� �����.)
    list<shared_ptr<Message>> getAllChatMessages(unsigned int chatID);

private:
    unsigned int userID_;
    string password_;
    string userName_;
    unsigned int showXUploadmessages;
    bool visability_;//����� �� ����� ������������ ����� �����
    list<unsigned int> blackList_;
    list<unsigned int> knownUsers_;
    list<shared_ptr<Chat>> userChats_;
    void fillProfileFromFiles();
    void fillProfileSettingsFromFile();
    void fillProfileChatsFromFile();
    void createProfileFiles();
    /*��������*/
    unsigned int getFreeChat(void);
};

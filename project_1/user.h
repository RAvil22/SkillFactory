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

    /*Сеттеры*/
    void setUserName(string userName);//ok
    void setChatName(unsigned int num, string name);
    void setPassword(string password);

    /*Геттеры*/
    const string getUserName(void){return this->userName_;} //ok
    const string getUserPassword(void){return this->password_;}
    const unsigned int getUserID(void){return this->userID_;} //ok
    unsigned int getNumberOfChats(void){return userChats_.size();} //ok

    /*Создание/удаление чатов*/
    bool createPublicChat(void); //ok
    bool createPrivateChat(unsigned int calledUserID);
    bool removeOwnedPublicChat(const unsigned int); //ok
    bool removeNonOwnedPublicChat(const unsigned int); //ok


    /*Поиск чата*/
    unsigned int getChatID(const unsigned int);
    string getChatName(const unsigned int);
    unsigned int getChatType(const unsigned int);
    list<shared_ptr<Chat>>::iterator searchUserChat(const unsigned int); //ok
    unsigned int searchChatID(const unsigned int); //Возврат ID чата
    list<unsigned int> searchChatName(const string); //Возврат ID подходящих чатов
    void showUserChatIDs(void);

    /*Подключение/покидание чатов*/
    bool joinToChat(const unsigned int chatID);
    bool leaveChat(const unsigned int chatID);

    /*Отправка/удаление сообщений*/
    bool sendMessageToChat(shared_ptr<Message> message, unsigned int chatID);
    bool removeMessageFromChat(unsigned int messageNum, unsigned int chatID); //ввести проверку на владение чатом

    /*Отображение содержимого чатов*/
    void userSettings(unsigned int, string, bool); //Количество подгружаемых сообщений, имя пользователя, видимость
    bool showLastChatMessages(unsigned int chatID, unsigned int showNum);
    bool uploadChatMessages(unsigned int chatID, list<shared_ptr<Message>>& chatMessages);
    bool updateChat(list<shared_ptr<Chat>>::iterator);
    bool updateChats(); //Сверка с экземпляром объекта пользователя на сервере (один раз в секунду, если не обрабатывается иной вызов.)
    list<shared_ptr<Message>> getAllChatMessages(unsigned int chatID);

private:
    unsigned int userID_;
    string password_;
    string userName_;
    unsigned int showXUploadmessages;
    bool visability_;//Можно ли найти пользователя через поиск
    list<unsigned int> blackList_;
    list<unsigned int> knownUsers_;
    list<shared_ptr<Chat>> userChats_;
    void fillProfileFromFiles();
    void fillProfileSettingsFromFile();
    void fillProfileChatsFromFile();
    void createProfileFiles();
    /*Временно*/
    unsigned int getFreeChat(void);
};

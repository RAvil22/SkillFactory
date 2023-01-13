#pragma once
#include "chat.h"
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>

using namespace std;

struct UserIDs{
    const unsigned int userID_;
    string userName_;
};

struct UserSettings{
    unsigned int showXUploadmessages;
    string userName_;
    bool visability_; //Можно ли найти пользователя через поиск
    list <unsigned int> joiningRequests_; //Список чатов на присоединение к которым подан запрос, но еще не получен ответ
    list<UserIDs> blackList;
};

struct UserChat{
    UserChat(unsigned int userID, const unsigned int chatID) : chatID_{chatID}, userChat(chatID, userID) {}
    const unsigned int chatID_;
    PublicChat userChat;
};

enum USER_REQUESTS
{
    joinToChat = 1,
    leaveChat = 2,
    searchChat = 3
};

class User{
public:
    User(unsigned int, string); // ID, password  //ok

    /*Сеттеры*/
    void setUserName(string userName){this->userSets_.userName_ = userName;} //ok

    /*Геттеры*/
    const string getUserName(void){return this->userSets_.userName_;} //ok
    const unsigned int getUserID(void){return this->userID_;} //ok
    auto getNumberOfChats(void){return userChats_.size();} //ok

    /*Создание/удаление чатов*/
    bool createPublicChat(void); //ok
    //bool createPrivateChat();
    bool removeOwnedChat(const unsigned int); //ok
    bool removeNonOwnedChat(const unsigned int); //ok

    /*Поиск чата*/
    list<UserChat>::iterator searchUserChat(const unsigned int); //ok
    unsigned int searchChatID(const unsigned int); //Возврат ID чата
    list<string> searchChatName(const string); //Возврат ID подходящих чатов

    ///
    void showUserChatIDs(void){
        for(auto const& i : this->userChats_){
            cout << i.userChat.getChatID() << " ";
        }
        cout << endl;
    }
    ///

    /*Подключение/покидание чатов*/
    bool joinToChat(const unsigned int chatID);
    bool leaveChat(const unsigned int chatID);
    bool inviteToChat(const unsigned int chatID, const unsigned int userID);
    bool receiveToChat(const unsigned int chatID, const unsigned int userID);

    /*Отправка/удаление сообщений*/
    bool sendMessageToChat(Message message, unsigned int chatID);
    //bool removeMessageFromChat(unsigned int messageNum, unsigned int chatID); //ввести проверку на владение чатом

    /*Отображение содержимого чатов*/
    void userSettings(char, char, string); //Количество отображаемых сообщений в чате, количество подгружаемых сообщений, имя пользователя
    bool showLastChatMessages(unsigned int chatID, unsigned int showNum);
    //bool uploadChatMessages(unsigned int chatID);
    //bool updateChats(); //Сверка с экземпляром объекта пользователя на сервере (один раз в секунду, если не обрабатывается иной вызов.)

private:
    unsigned int userID_;
    string password_; //Должен храниться на сервере?
    UserSettings userSets_;
    list<UserChat> userChats_;
    //PublicChat tempChat; //?
    list<UserIDs> knownUsers_;
};

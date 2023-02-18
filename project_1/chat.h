#pragma once
#include <list>
#include "message.h"
#include "chatExcept.h"
#include <fstream>
#include <ctime>

class Chat{
public:
    Chat(void) = delete;
    Chat(const unsigned int chatID, const unsigned int chatType); // ID чата
    const unsigned int getChatID(void) const;
    void setChatName(string chatName);
    const string getChatName(void);
    time_t getChatLastUpdate(void){return this->lastUpdate_;}
    virtual bool addMessage(shared_ptr<Message>) = 0;
    string getMessageText(unsigned int);
    unsigned int getMessageSender(unsigned int);
    time_t getMessageSendTime(unsigned int);
    unsigned int getChatType(){return chatType_;}
    virtual bool removeMessage(unsigned int num, unsigned int userID) = 0;
    unsigned int size(void);
    shared_ptr<Message> getLastMessage(void);
    list<shared_ptr<Message>> getAllMessages(void);
    virtual ~Chat() = default;
protected:
    const unsigned int chatID_;
    string chatName_;
    unsigned int unreadMessages_;
    string fileName_;
    list<shared_ptr<Message>> messages_;
    time_t lastUpdate_;
    unsigned int chatType_;
};

class PublicChat : public Chat{
public:
    PublicChat(const unsigned int chatID, const unsigned int chatOwnerID); // ID чата, ID владельца чата
    const unsigned int getPublicChatOwner(void){return this->chatOwnerID_;}
    virtual bool addMessage(shared_ptr<Message> mess) override;
    virtual bool removeMessage(unsigned int num, unsigned int userID) override;
    virtual void updateChatFromFiles(shared_ptr<Message>);
    void addUser(unsigned int userID);
    void removeUser(unsigned int UserID);
    virtual ~PublicChat() = default;
    //Добавить оператор копирования
protected:
    list<unsigned int> userIDs_;
    unsigned int chatOwnerID_;
    void createChatFiles(void);
    void fillChatFromFiles(void);
    string fileUsersName_;
};

class PrivateChat : public Chat{
public:
    PrivateChat(unsigned int ChatID, unsigned int firstUserID, unsigned int secondUserID);
    virtual bool addMessage(shared_ptr<Message>) override;
    virtual bool removeMessage(unsigned int num, unsigned int userID) override;
    void updateChatFromFile(shared_ptr<Message>);
    virtual ~PrivateChat() = default;
    unsigned int getFirstUserID(){return this->firstUserID_;}
    unsigned int getSecondUserID(){return this->secondUserID_;}
protected:
    const unsigned int firstUserID_;
    const unsigned int secondUserID_;
};

/*
class OpenPublicChat : public PublicChat{};

class ClosedPublicChat : public PublicChat{};

class EncryptedPrivateChat : public PrivateChat{};
*/

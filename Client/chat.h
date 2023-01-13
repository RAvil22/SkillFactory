#pragma once
#include <list>
#include "message.h"
#include "chatExcept.h"
#include <ctime>

class Chat{
public:
    Chat(void) = delete;
    Chat(const unsigned int); // ID чата
    const unsigned int getChatID(void) const;
    void setChatName(const string);
    const string getChatName(void);
    virtual void addMessage(Message) = 0;
    string getMessageText(unsigned int);
    bool removeMessage(unsigned int);
    unsigned int size(void);
    virtual ~Chat() = default;
protected:
    const unsigned int chatID_;
    string chatName_;
    unsigned int unreadMessages_;
    list<Message> messages_;
};

class PublicChat : public Chat{
public:
    PublicChat(const unsigned int, unsigned int); // ID чата, ID владельца чата
    const unsigned int getPublicChatOwner(void);
    virtual void addMessage(Message) override;
    virtual ~PublicChat() = default;
protected:
    time_t lastUpdate_;
    list<unsigned int> userIDs_;
    unsigned int chatOwnerID_;
};


//class OpenPublicChat : public PublicChat{};

//class ClosedPublicChat : public PublicChat{};

/*class PrivateChat : public Chat{
public:
    virtual bool sendMessage(Message) override;
    virtual ~PrivateChat() = default;
protected:
    unsigned int firstUserID_;
    unsigned int secondUserID_;
};*/

//class EncryptedPrivateChat : public PrivateChat{};

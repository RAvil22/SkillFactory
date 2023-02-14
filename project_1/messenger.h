#pragma once

#include <QMainWindow>
#include "qmessagewidget.h"
#include "singledialog.h"
#include "newpassword.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Messenger; }
class QAction;
QT_END_NAMESPACE

class Messenger : public QMainWindow
{
    Q_OBJECT

public:
    Messenger(unique_ptr<User>, QWidget *parent = nullptr);
    ~Messenger();

private slots:
    void sendMessage(void);

    void getChat(void);

    void createPublicChat(void);
    void createPrivateChat(void);
    unsigned int searchUser(void);
    unsigned int searchChat(void);
    void leaveChat(void);
    void joinChat(void);
    void quitFromMessenger(void);
    void changeUserSets(void);
    void refreshPassword(void);

private:
    Ui::Messenger *ui;
    unique_ptr<User> current;
    void createMainActions(void);
    void createSettingsActions(void);
    void createMenus(void);
    bool loadUserChat(unsigned int chatID);
    bool updateUserChatsStatus(void);
    bool clearMessagesWindow(void);
    bool checkForAllDigits(QString& fromDialog);


    QMenu *mainMenu;
    QMenu *setsMenu;

    QAction *createPublicChatAct;
    QAction *createPrivateChatAct;
    QAction *searchUserAct;
    QAction *searchChatAct;
    QAction *leaveChatAct;
    QAction *joinChatAct;
    QAction *quitFromMessengerAct;
    QAction *changeUserSetsAct;
    QAction *refreshPasswordAct;
};


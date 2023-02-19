#include "messenger.h"
#include "ui_messenger.h"
#include <iostream>
#include "user.h"

#include <typeinfo>

Messenger::Messenger(unique_ptr<User> curr, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Messenger)
{
    ui->setupUi(this);

    ui->pushButton_SendMes->setDisabled(true);

    /*Create actions*/
    createMainActions();
    createSettingsActions();
    /*Create menu's*/
    createMenus();

    /*Signals*/
    connect(ui->pushButton_SendMes, &QPushButton::released, this, &Messenger::sendMessage);

    /*Создать объект класса user с id*/
    this->current = std::move(curr);

    /*Создать кнопки выбора чата*/
    auto numChats{current->getNumberOfChats()};
    for(unsigned int i{0}; i < numChats; ++i){
        auto chat = (*current->searchUserChat(current->getChatID(i)));
        switch(current->getChatType(i)){
            case 1:{
                QContactWidget *contact = new QContactWidget(current->getChatID(i), current->getChatType(i),
                                                            QString::fromStdString(current->getChatName(i)));
                QObject::connect(contact, SIGNAL(chatCalled()), this, SLOT(getChat()));
                ui->scrollArea_Contacts->widget()->layout()->addWidget(contact);
                break;
            }
            case 2:{
                auto temp = dynamic_pointer_cast<PrivateChat>(chat);
                unsigned int calledID;
                if(temp->getFirstUserID() == current->getUserID()){calledID = temp->getSecondUserID();}
                else {calledID = temp->getFirstUserID();}
                QContactWidget *contact = new QContactWidget(current->getChatID(i), current->getChatType(i),
                                                            QString::fromStdString(to_string(calledID)));
                QObject::connect(contact, SIGNAL(chatCalled()), this, SLOT(getChat()));
                ui->scrollArea_Contacts->widget()->layout()->addWidget(contact);
                break;
            }
            default:{
                throw NoChatType(current->getChatType(i));
                break;
            }
        }

    }

    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(on_timeout()));
    timer_->start(1000);
}

bool Messenger::checkForAllDigits(QString& fromDialog){
    auto strSize{fromDialog.size()};
    for(unsigned int i{0}; i < strSize; ++i){
        if(fromDialog[i] < '0' || fromDialog[i] > '9')return false;
    }
    return true;
}

void Messenger::getChat(){
    timer_->stop();
    QContactWidget *contact = (QContactWidget*)sender();
    QString chatID = QString::fromStdString(to_string(contact->getChatID()));
    ui->Label_ActiveChatID->setText(chatID);//в надпись должен идти номер чата
    ui->pushButton_SendMes->setEnabled(true);
    loadUserChat(ui->Label_ActiveChatID->text().toUInt());
    fstream userChatsFile{"user_chats_" + to_string(current->getUserID()) + ".txt"};
    if(userChatsFile.is_open()){
        unsigned int currChatID;
        while(userChatsFile.read((char*)&currChatID,sizeof(currChatID))){
            if(currChatID != contact->getChatID()){userChatsFile.seekg(sizeof(time_t), ios::cur);}
            else{
                auto currChat = current->searchUserChat(contact->getChatID());
                time_t lastUp = (*currChat)->getChatLastUpdate();
                userChatsFile.write((char*)&lastUp, sizeof(lastUp));
                (*currChat)->zeroUnreadMessages();
                break;
            }
        }
        userChatsFile.close();
    }
    else{
        QMessageBox::warning(this, "Внимание!", "Отсутствует файл чатов пользователя!");
        close();
    }
    //contact->zeroUnread();
    timer_->start(1000);
}

Messenger::~Messenger()
{
    delete ui;
}

void Messenger::sendMessage(){
    /*Создать shared_ptr<Message>, добавить в активный чат, из файла активного чата взять данные и передать в конструктор QMessageWidget*/
    shared_ptr<Message> mess = make_unique<Message>(ui->textEdit->toPlainText().toStdString(), current->getUserID());
    current->sendMessageToChat(std::move(mess), ui->Label_ActiveChatID->text().toUInt());
    QMessageWidget *temp = new QMessageWidget(ui->scrollArea_Chat->widget(), this->current->getUserID(),
                                              QString::fromStdString(current->getUserName()), std::time(nullptr), ui->textEdit->toPlainText());
    ui->scrollArea_Chat->widget()->layout()->addWidget(temp);
    ui->textEdit->clear();
}

void Messenger::createMainActions(void){
    createPublicChatAct = new QAction(tr("&Create public chat"), this);
    connect(createPublicChatAct, &QAction::triggered, this, &Messenger::createPublicChat);

    createPrivateChatAct = new QAction(tr("&Create private chat"), this);
    connect(createPrivateChatAct, &QAction::triggered, this, &Messenger::createPrivateChat);

    searchUserAct = new QAction(tr("&Search user"), this);
    //searchUserAct->setShortcuts(QKeySequence::New);
    //searchUserAct->setStatusTip(tr("Create a new file"));
    connect(searchUserAct, &QAction::triggered, this, &Messenger::searchUser);

    searchChatAct = new QAction(tr("&Search chat"), this);
    connect(searchChatAct, &QAction::triggered, this, &Messenger::searchChat);

    leaveChatAct = new QAction(tr("&Leave chat"), this);
    connect(leaveChatAct, &QAction::triggered, this, &Messenger::leaveChat);

    joinChatAct = new QAction(tr("&Join chat"), this);
    connect(joinChatAct, &QAction::triggered, this, &Messenger::joinChat);

    quitFromMessengerAct = new QAction(tr("&Quit"), this);
    connect(quitFromMessengerAct, &QAction::triggered, this, &Messenger::quitFromMessenger);
}

void Messenger::createSettingsActions(void){
    changeUserSetsAct = new QAction(tr("&Change settings"), this);
    connect(changeUserSetsAct, &QAction::triggered, this, &Messenger::changeUserSets);

    refreshPasswordAct = new QAction(tr("&Refresh password"), this);
    connect(refreshPasswordAct, &QAction::triggered, this, &Messenger::refreshPassword);
}

void Messenger::createMenus(void){
    mainMenu = menuBar()->addMenu(tr("&Main"));
    mainMenu->addAction(createPublicChatAct);
    mainMenu->addAction(createPrivateChatAct);
    mainMenu->addAction(searchUserAct);
    mainMenu->addAction(searchChatAct);
    mainMenu->addAction(leaveChatAct);
    mainMenu->addAction(joinChatAct);
    mainMenu->addAction(quitFromMessengerAct);

    setsMenu = menuBar()->addMenu(tr("&Settings"));
    setsMenu->addAction(changeUserSetsAct);
    setsMenu->addAction(refreshPasswordAct);
}

void Messenger::createPublicChat(void){
    //Создание диалогового окна
    SingleDialog sCh("Public chat name", this);
    QString result;
    sCh.setModal(true);
    //Создание обработчика сигнала диалогового окна
    connect(&sCh, &SingleDialog::lineText, [&](QString text){result = text;});
    //Запуск диалогового окна
    sCh.exec();
    //Создание нового публичного чата
    current->createPublicChat();
    //Получение позиции нового чата в списке чатов
    auto numChats{current->getNumberOfChats()};
    auto lastChatNum = numChats-1;
    //Установка имени чата полученного из диалогового окна
    current->setChatName(lastChatNum, result.toStdString());
    //Создание и размещение в окне кнопки вызова чата
    QPushButton *newContact = new QPushButton();
    newContact->setText("Chat " + QString::fromStdString(std::to_string(current->getChatID(lastChatNum))) + " " + result);
    QObject::connect(newContact, &QPushButton::clicked, this, &Messenger::getChat);
    ui->scrollArea_Contacts->widget()->layout()->addWidget(newContact);
}

void Messenger::createPrivateChat(void){
    //Создание диалогового окна
    SingleDialog sCh("Chat with who?", this);
    QString result;
    sCh.setModal(true);
    //Создание обработчика сигнала диалогового окна
    connect(&sCh, &SingleDialog::lineText, [&](QString text){result = text;});
    //Запуск диалогового окна
    sCh.exec();
    //Проверка на строки на корректность
    for(int i{0}; i < result.size(); ++i){
        if(result[i] > '9' || result[i] < '0'){
            QMessageBox::warning(this, "Внимание!", "Персональный номер состоит из чисел!");
            return;
        }
    }
    //Проверка вызываемого пользователя на существование
    unsigned int calledUserID{result.toUInt()};
    unsigned int fileLastID{0};
    ifstream userIDsFile{"userIDs.txt"};
    if(userIDsFile.is_open()){
        userIDsFile.read((char*)&fileLastID, sizeof(fileLastID));
        userIDsFile.close();
    }
    else{
        QMessageBox::warning(this, "Внимание!", "Отсуствует файл номеров пользователей!");
        close();
    }

    //Создание нового приватного чата
    if(calledUserID <= fileLastID)current->createPrivateChat(calledUserID);
    else{QMessageBox::warning(this, "Внимание!", "Приватный чат не создан!");return;}
    //Получение позиции нового чата в списке чатов
    auto numChats{current->getNumberOfChats()};
    auto lastChatNum = numChats-1;
    current->getChatID(lastChatNum);
    //Создание и размещение в окне кнопки вызова чата
    QPushButton *newContact = new QPushButton();
    newContact->setText("Contact " + QString::fromStdString(std::to_string(current->getChatID(lastChatNum))) + " " + result);
    QObject::connect(newContact, &QPushButton::clicked, this, &Messenger::getChat);
    ui->scrollArea_Contacts->widget()->layout()->addWidget(newContact);
}

unsigned int Messenger::searchUser(void){
    SingleDialog sCh("Search user", this);
    QString userID;
    sCh.setModal(true);
    connect(&sCh, &SingleDialog::lineText, [&](QString text)
    {userID = text;});
    sCh.exec();
    if(!checkForAllDigits(userID)){
        QMessageBox::warning(this, "Внимание!", "Персональный номер состоит из чисел!");
        return 0;
    }
    string calledUserFileName{"user_" + userID.toStdString() + ".txt"};
    ifstream calledUserFile{calledUserFileName};
    if(calledUserFile.is_open()){
        calledUserFile.close();
        return userID.toUInt();
    }
    else{
        QMessageBox::warning(this, "Внимание!", "Пользователь не найден!");
        return 0;
    }
}

unsigned int Messenger::searchChat(void){ //Задействовать класс User
    SingleDialog sCh("Search chat", this);
    QString chatID;
    sCh.setModal(true);
    connect(&sCh, &SingleDialog::lineText, [&](QString text)
    {chatID = text;});
    sCh.exec();
    if(!checkForAllDigits(chatID)){
        QMessageBox::warning(this, "Внимание!", "Номер чата состоит из чисел!");
        return 0;
    }
    string chatFileName{"chat_" + chatID.toStdString() + ".txt"};
    ifstream chatFile{chatFileName};
    if(chatFile.is_open()){chatFile.close(); return chatID.toUInt();}
    else return 0;
}

void Messenger::leaveChat(void){ //Доделать
    SingleDialog sCh("Leave chat", this);
    QString chatID;
    sCh.setModal(true);
    connect(&sCh, &SingleDialog::lineText, [&](QString text)
    {chatID = text;});
    sCh.exec();
    if(!checkForAllDigits(chatID)){
        QMessageBox::warning(this, "Внимание!", "Номер чата состоит из чисел!");
        return;
    }
    current->leaveChat(chatID.toUInt());
    //Удалить кнопку

}

void Messenger::joinChat(void){
    try {
        SingleDialog sCh("Join to chat", this);
        QString chatID;
        sCh.setModal(true);
        connect(&sCh, &SingleDialog::lineText, [&](QString text)
        {chatID = text;});
        sCh.exec();
        if(!checkForAllDigits(chatID)){
            QMessageBox::warning(this, "Внимание!", "Номер чата состоит из чисел!");
            return;
        }
        if(current->joinToChat(chatID.toUInt())){
            //Получение позиции нового чата в списке чатов
            auto numChats{current->getNumberOfChats()};
            auto lastChatNum = numChats-1;
            //Создание и размещение в окне кнопки вызова чата
            QPushButton *newContact = new QPushButton();
            newContact->setText("Chat " + QString::fromStdString(std::to_string(current->getChatID(lastChatNum))) + " " +
                                QString::fromStdString(current->getChatName(lastChatNum)));
            QObject::connect(newContact, &QPushButton::clicked, this, &Messenger::getChat);
            ui->scrollArea_Contacts->widget()->layout()->addWidget(newContact);
        }
    }
    catch (exception &ex) {
    QMessageBox::warning(this, "Внимание!", ex.what());
    }

}

void Messenger::quitFromMessenger(void){
    std::cout << "quit" << std::endl;
}

void Messenger::changeUserSets(void){
    std::cout << "change sets" << std::endl;
}

void Messenger::refreshPassword(void){
    NewPassword nP(current->getUserPassword());
    QString result;
    nP.setModal(true);
    connect(&nP, &NewPassword::lineText, [&](QString text)
    {result = text;});
    nP.exec();
    current->setPassword(result.toStdString());
}

bool Messenger::loadUserChat(unsigned int chatID){
    //Очистить окно чата
    while(!ui->scrollArea_Chat->widget()->layout()->isEmpty()){
        QLayoutItem* item = ui->scrollArea_Chat->widget()->layout()->itemAt(0);
        ui->scrollArea_Chat->widget()->layout()->removeItem(item);
        QWidget* widget = item->widget();
        if(widget) delete widget;
    }

    list<shared_ptr<Message>> chatMessages;
    try {
        if(current->uploadChatMessages(chatID, chatMessages)){
            auto iter{chatMessages.begin()};
            auto endChat{chatMessages.end()};
            while(iter != endChat){
                auto curID{(*iter)->getMessageSender()};
                /**/
                QString curName{""};
                ifstream userName{"user_" + std::to_string(curID) + ".txt"};
                if(userName.is_open()){
                    unsigned int id{0};
                    unsigned int passSize{0};
                    unsigned int nameSize{0};
                    string name{""};
                    char c;
                    userName.read((char*)&id, sizeof(id));
                    userName.read((char*)&passSize, sizeof(passSize));
                    userName.seekg(passSize,ios::cur);
                    userName.read((char*)&nameSize, sizeof(nameSize));
                    for(unsigned int i{0}; i < nameSize; ++i){
                        userName.read((char*)&c, sizeof(c));
                        curName += c;
                    }
                    userName.close();
                }
                /**/
                auto curTime{(*iter)->getMessageSendTime()};
                QString curText{(*iter)->getText().c_str()};
                QMessageWidget *temp = new QMessageWidget(ui->scrollArea_Chat->widget(), curID, curName, curTime, curText);
                ui->scrollArea_Chat->widget()->layout()->addWidget(temp);
                ++iter;
            }
        }
    }
    catch (exception &ex) {
        QMessageBox::warning(this, "Внимание!", ex.what());
    }

    return true;
}

void Messenger::on_timeout(void){
    if(updateUserChatsStatus());
    else{
        QMessageBox::warning(this, "Внимание!", "Невозможно обновить статус чатов!");
        timer_->stop();
    }

}

bool Messenger::updateUserChatsStatus(void){
    auto numOfWids{ui->scrollArea_Contacts->widget()->layout()->count()};
    for(int i{0}; i < numOfWids; ++i){
        QContactWidget *currWidget = qobject_cast<QContactWidget*>(ui->verticalLayout->itemAt(i)->widget());
        if(currWidget){
            unsigned int currChatID{currWidget->getChatID()};
            auto currChat{current->searchUserChat(currChatID)};
            try {
                if(!current->updateChat(currChat))return false;
            } catch (exception &ex) {
                QMessageBox::warning(this, "Внимание!", ex.what());
            }
            currWidget->updateUnreadMessages(current->getUnreadMessages(currChatID));
        }
    }
    return true;
}



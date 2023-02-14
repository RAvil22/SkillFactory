#include "messenger.h"
#include "ui_messenger.h"
#include <iostream>
#include "user.h"

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
        QPushButton *contact = new QPushButton();
        switch(current->getChatType(i)){
            case 1:{
                QString temp{"Chat " + QString::number(current->getChatID(i))};
                auto name = current->getChatName(i);
                if(current->getChatName(i).size()){
                    temp += " ";
                    temp += QString::fromStdString(current->getChatName(i));
                }
                contact->setText(temp);
                break;
            }
            case 2:{
                contact->setText("Contact " + QString::number(current->getChatID(i)));
                break;
            }
            default:{
                throw NoChatType(current->getChatType(i));
                break;
            }
        }
        QObject::connect(contact, &QPushButton::clicked, this, &Messenger::getChat);
        ui->contactsLayout->addWidget(contact);
    }
}

bool Messenger::checkForAllDigits(QString& fromDialog){
    auto strSize{fromDialog.size()};
    for(unsigned int i{0}; i < strSize; ++i){
        if(fromDialog[i] < '0' || fromDialog[i] > '9')return false;
    }
    return true;
}

void Messenger::getChat(){
    QPushButton *button = (QPushButton*)sender();
    QString btnStr{button->text()};
    //Извлечение из строки номера чата
    auto start{btnStr.indexOf(L' ')};
    auto finish{btnStr.indexOf(L' ',start+1)};
    QString chatID;
    if(finish < 0){
        chatID = btnStr.sliced(start+1);
    }
    else{
        for(auto i{start+1}; i < finish; ++i){
            chatID += btnStr[i];
        }
    }
    ui->Label_ActiveChatID->setText((chatID));//в надпись должен идти немер чата
    ui->pushButton_SendMes->setEnabled(true);
    loadUserChat(ui->Label_ActiveChatID->text().toUInt());
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
    ui->chatLayout->addWidget(temp);
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
    ui->contactsLayout->addWidget(newContact);
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
    ui->contactsLayout->addWidget(newContact);
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

void Messenger::leaveChat(void){
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
        ui->contactsLayout->addWidget(newContact);
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
    while(!ui->chatLayout->isEmpty()){
        QLayoutItem* item = ui->chatLayout->itemAt(0);
        ui->chatLayout->removeItem(item);
        QWidget* widget = item->widget();
        if(widget) delete widget;
    }
    //Загрузить из файлов сообщения чата(делать через класс User)
    //Обновить чат в объекте пользователя из файла
    //Выгрузить из чата объекта пользователя все сообщения
    list<shared_ptr<Message>> chatMessages;
    /*Проблема в методе User::uploadChatMessages, после передачи владения unique_ptr в список, не удается передать владение новым элементом unique_ptr*/
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
            ui->chatLayout->addWidget(temp);
            ++iter;
        }
    }
}

bool Messenger::updateUserChatsStatus(void){
    std::cout << "load user chats" << std::endl;
}



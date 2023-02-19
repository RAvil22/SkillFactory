#include "autorization.h"
#include "ui_autorization.h"

Autorization::Autorization(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Autorization), chatter{nullptr}
{
    ui->setupUi(this);
    connect(ui->pushButton_signIn, &QPushButton::released, this, &Autorization::btnSignInClicked);
    connect(ui->pushButton_signUp, &QPushButton::released, this, &Autorization::btnSignUpClicked);
}

Autorization::~Autorization()
{
    delete ui;
}

void Autorization::btnSignInClicked(void){

    //Создать объект пользователя
    std::string userIDstr = ui->lineEdit_ID->text().toStdString();
    for(auto i:userIDstr){
        if(i > 57 || i < 48){
            QMessageBox::warning(this, "Внимание!", "Персональный номер состоит из чисел!");
            return;
        }
    }
    unsigned int userID{ui->lineEdit_ID->text().toUInt()} ;
    string userPassword{ui->lineEdit_password->text().toStdString()};
    std::string userFileName{"user_"+userIDstr+".txt"};
    ifstream userFile{userFileName};
    if(userFile.is_open()){
        unsigned int fileID;
        string filePassword;
        unsigned int s;
        char c;
        userFile.read((char*)&fileID, sizeof(fileID));
        userFile.read((char*)&s, sizeof(s));
        for(unsigned int i{0}; i < s; ++i){
            userFile.read((char*)&c, sizeof(c));
            filePassword += c;
        }
        userFile.close();
        if(fileID != userID || filePassword != userPassword){
            QMessageBox::warning(this, "Внимание!", "Такого сочетания нет!");
            return;
        }
        try{
            unique_ptr<User> currentUser = make_unique<User>(userID, userPassword);
            this->chatter = make_unique<Messenger>(std::move(currentUser));
            this->chatter->show();
            this->hide();
        }
        catch(exception &ex){
            QMessageBox::warning(this, "Внимание!", ex.what());
            this->close();
        }


    }
    else {
        QMessageBox::warning(this, "Внимание!", "Файл пользователя отсуствует!");
        return;
    }
}

void Autorization::btnSignUpClicked(){
    aNewOne = make_unique<Registration>(this);
    aNewOne->setModal(true);
    aNewOne->exec();
}

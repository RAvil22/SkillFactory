#include "registration.h"
#include "ui_Registration.h"

Registration::Registration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &Registration::novice);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::novice(void){
    /*Проверка на корректность введения пароля*/
    if(ui->lineEdit_Password1->text() != ui->lineEdit_Password2->text()){
        QMessageBox::warning(this, "Внимание","Пароль не подтвержден!");
        return;
    }

    /*Получение ID*/
    unsigned int id{this->getNewUserID()};
    /*Запись логина и пароля*/
    string login{ui->lineEdit_Login->text().toStdString()};
    string password{ui->lineEdit_Password1->text().toStdString()};

    ui->pushButton->setEnabled(false);
    ui->pushButton->setText(QString::number(id));

    /*Создание файла user с копией объекта пользователя*/
    unique_ptr<User> newOne = make_unique<User>(id, password, login);

    /*Выход из окна регистрации*/
    QMessageBox::warning(this, "Ваш ID", QString::number(id));
    close();

}

unsigned int Registration::getNewUserID(void){
    fstream userIDs;
    unsigned int result;
    userIDs.open("userIDs.txt", ios::in | ios::out);
    if (userIDs.is_open()) {
        userIDs.read((char*)&result, sizeof(result));
        userIDs.seekp(0, ios::beg);
        ++result;
        userIDs.write((char*)&result, sizeof(result));
        userIDs.close();
        return result;
    }
    else {
        unsigned int one{ 1 };
        //ofstream new
        userIDs.open("userIDs.txt", ios::out);
        userIDs.write((char*)&one, sizeof(one));
        userIDs.close();
        return one;
    }
}

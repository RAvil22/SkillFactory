#include "newpassword.h"
#include "ui_newpassword.h"

NewPassword::NewPassword(std::string cP, QWidget *parent) :
    QDialog(parent), curPass{cP.c_str()},
    ui(new Ui::NewPassword)
{
    ui->setupUi(this);
}

NewPassword::~NewPassword()
{
    delete ui;
}

void NewPassword::accept(void){
    if(ui->lineEdit_CP->text() != this->curPass){
        QMessageBox::warning(this, "Внимание","Текущий пароль введен неверно!");
        return;
    }
    if(ui->lineEdit_NP1->text() != ui->lineEdit_NP2->text()){
        QMessageBox::warning(this, "Внимание","Новый пароль не подтвержден!");
        return;
    }
    else{
        emit lineText(ui->lineEdit_NP1->text());
        done(0);
    }
}

void NewPassword::reject(void){
    this->close();
    done(0);
}

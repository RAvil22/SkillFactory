#pragma once

#include <QDialog>
#include <QMessageBox>
#include <fstream>
#include "registration.h"
#include "messenger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Autorization; }
QT_END_NAMESPACE

class Autorization : public QDialog
{
    Q_OBJECT

public:
    Autorization(QWidget *parent = nullptr);
    ~Autorization();

private slots:
    void btnSignInClicked(void);
    void btnSignUpClicked(void);

private:
    Ui::Autorization *ui;
    unique_ptr<Registration> aNewOne;
    unique_ptr<Messenger> chatter;
};

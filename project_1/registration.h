#pragma once

#include <fstream>
#include <QDialog>
#include <QMessageBox>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Registration; }
QT_END_NAMESPACE

class Registration : public QDialog
{
    Q_OBJECT

public:
    Registration(QWidget *parent = nullptr);
    ~Registration();

private slots:
    void novice(void);

private:
    unsigned int getNewUserID(void);
    Ui::Registration *ui;
};

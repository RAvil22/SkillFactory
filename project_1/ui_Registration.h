/********************************************************************************
** Form generated from reading UI file 'Registration.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_Login;
    QLineEdit *lineEdit_Login;
    QLabel *label_Password1;
    QLineEdit *lineEdit_Password1;
    QLabel *label_Password2;
    QLineEdit *lineEdit_Password2;
    QPushButton *pushButton;

    void setupUi(QDialog *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName("Registration");
        Registration->resize(446, 640);
        verticalLayout = new QVBoxLayout(Registration);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(Registration);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 75));
        QFont font;
        font.setFamilies({QString::fromUtf8("Chiller")});
        font.setPointSize(24);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_Login = new QLabel(Registration);
        label_Login->setObjectName("label_Login");
        label_Login->setMaximumSize(QSize(16777215, 50));
        label_Login->setFont(font);

        verticalLayout->addWidget(label_Login);

        lineEdit_Login = new QLineEdit(Registration);
        lineEdit_Login->setObjectName("lineEdit_Login");
        lineEdit_Login->setMaximumSize(QSize(16777215, 50));
        QFont font1;
        font1.setPointSize(24);
        lineEdit_Login->setFont(font1);
        lineEdit_Login->setEchoMode(QLineEdit::Normal);

        verticalLayout->addWidget(lineEdit_Login);

        label_Password1 = new QLabel(Registration);
        label_Password1->setObjectName("label_Password1");
        label_Password1->setMaximumSize(QSize(16777215, 50));
        label_Password1->setFont(font);

        verticalLayout->addWidget(label_Password1);

        lineEdit_Password1 = new QLineEdit(Registration);
        lineEdit_Password1->setObjectName("lineEdit_Password1");
        lineEdit_Password1->setMaximumSize(QSize(16777215, 50));
        lineEdit_Password1->setFont(font1);
        lineEdit_Password1->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEdit_Password1);

        label_Password2 = new QLabel(Registration);
        label_Password2->setObjectName("label_Password2");
        label_Password2->setMaximumSize(QSize(16777215, 50));
        label_Password2->setFont(font);

        verticalLayout->addWidget(label_Password2);

        lineEdit_Password2 = new QLineEdit(Registration);
        lineEdit_Password2->setObjectName("lineEdit_Password2");
        lineEdit_Password2->setMaximumSize(QSize(16777215, 50));
        lineEdit_Password2->setFont(font1);
        lineEdit_Password2->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEdit_Password2);

        pushButton = new QPushButton(Registration);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(200, 50));
        pushButton->setMaximumSize(QSize(250, 50));
        pushButton->setFont(font);

        verticalLayout->addWidget(pushButton, 0, Qt::AlignHCenter);


        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QDialog *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Registration", "Who are you? What is your secret?", nullptr));
        label_Login->setText(QCoreApplication::translate("Registration", "Login", nullptr));
        label_Password1->setText(QCoreApplication::translate("Registration", "Password", nullptr));
        label_Password2->setText(QCoreApplication::translate("Registration", "Password", nullptr));
        pushButton->setText(QCoreApplication::translate("Registration", "Join", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H

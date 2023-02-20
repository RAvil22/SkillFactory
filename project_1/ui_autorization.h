/********************************************************************************
** Form generated from reading UI file 'autorization.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTORIZATION_H
#define UI_AUTORIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Autorization
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_exe_name;
    QLabel *label_ID;
    QLineEdit *lineEdit_ID;
    QLabel *label_password;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_signIn;
    QPushButton *pushButton_signUp;

    void setupUi(QDialog *Autorization)
    {
        if (Autorization->objectName().isEmpty())
            Autorization->setObjectName("Autorization");
        Autorization->resize(400, 584);
        Autorization->setMaximumSize(QSize(800, 800));
        verticalLayout = new QVBoxLayout(Autorization);
        verticalLayout->setObjectName("verticalLayout");
        label_exe_name = new QLabel(Autorization);
        label_exe_name->setObjectName("label_exe_name");
        label_exe_name->setMaximumSize(QSize(16777215, 100));
        QFont font;
        font.setFamilies({QString::fromUtf8("Chiller")});
        font.setPointSize(36);
        font.setBold(false);
        font.setItalic(false);
        label_exe_name->setFont(font);
        label_exe_name->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_exe_name);

        label_ID = new QLabel(Autorization);
        label_ID->setObjectName("label_ID");
        label_ID->setMaximumSize(QSize(16777215, 50));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Chiller")});
        font1.setPointSize(24);
        label_ID->setFont(font1);

        verticalLayout->addWidget(label_ID);

        lineEdit_ID = new QLineEdit(Autorization);
        lineEdit_ID->setObjectName("lineEdit_ID");
        lineEdit_ID->setFont(font1);

        verticalLayout->addWidget(lineEdit_ID);

        label_password = new QLabel(Autorization);
        label_password->setObjectName("label_password");
        label_password->setMaximumSize(QSize(16777215, 50));
        label_password->setFont(font1);

        verticalLayout->addWidget(label_password);

        lineEdit_password = new QLineEdit(Autorization);
        lineEdit_password->setObjectName("lineEdit_password");
        QFont font2;
        font2.setPointSize(24);
        lineEdit_password->setFont(font2);
        lineEdit_password->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEdit_password);

        pushButton_signIn = new QPushButton(Autorization);
        pushButton_signIn->setObjectName("pushButton_signIn");
        pushButton_signIn->setMinimumSize(QSize(200, 50));
        pushButton_signIn->setMaximumSize(QSize(250, 75));
        pushButton_signIn->setFont(font1);
        pushButton_signIn->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(pushButton_signIn, 0, Qt::AlignHCenter);

        pushButton_signUp = new QPushButton(Autorization);
        pushButton_signUp->setObjectName("pushButton_signUp");
        pushButton_signUp->setMinimumSize(QSize(200, 50));
        pushButton_signUp->setMaximumSize(QSize(250, 75));
        pushButton_signUp->setFont(font1);

        verticalLayout->addWidget(pushButton_signUp, 0, Qt::AlignHCenter);


        retranslateUi(Autorization);

        QMetaObject::connectSlotsByName(Autorization);
    } // setupUi

    void retranslateUi(QDialog *Autorization)
    {
        Autorization->setWindowTitle(QCoreApplication::translate("Autorization", "Dialog", nullptr));
        label_exe_name->setText(QCoreApplication::translate("Autorization", "Chatter", nullptr));
        label_ID->setText(QCoreApplication::translate("Autorization", "Personal number", nullptr));
        label_password->setText(QCoreApplication::translate("Autorization", "Password", nullptr));
        pushButton_signIn->setText(QCoreApplication::translate("Autorization", "Sign in", nullptr));
        pushButton_signUp->setText(QCoreApplication::translate("Autorization", "Sign up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Autorization: public Ui_Autorization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTORIZATION_H

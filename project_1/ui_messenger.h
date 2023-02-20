/********************************************************************************
** Form generated from reading UI file 'messenger.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSENGER_H
#define UI_MESSENGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Messenger
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea_Chat;
    QWidget *scrollAreaChatWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QWidget *chatContainer;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *chatLayout;
    QTextEdit *textEdit;
    QLabel *label_Search;
    QLineEdit *lineEdit_Search;
    QPushButton *pushButton_SendMes;
    QScrollArea *scrollArea_Contacts;
    QWidget *scrollAreaContactsWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *contactsContainer;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *contactsLayout;
    QLabel *label_ActiveChat;
    QLabel *Label_ActiveChatID;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Messenger)
    {
        if (Messenger->objectName().isEmpty())
            Messenger->setObjectName("Messenger");
        Messenger->resize(1146, 769);
        centralwidget = new QWidget(Messenger);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        scrollArea_Chat = new QScrollArea(centralwidget);
        scrollArea_Chat->setObjectName("scrollArea_Chat");
        scrollArea_Chat->setWidgetResizable(true);
        scrollAreaChatWidgetContents = new QWidget();
        scrollAreaChatWidgetContents->setObjectName("scrollAreaChatWidgetContents");
        scrollAreaChatWidgetContents->setGeometry(QRect(0, 0, 815, 442));
        verticalLayout_4 = new QVBoxLayout(scrollAreaChatWidgetContents);
        verticalLayout_4->setObjectName("verticalLayout_4");
        chatContainer = new QWidget(scrollAreaChatWidgetContents);
        chatContainer->setObjectName("chatContainer");
        verticalLayoutWidget_2 = new QWidget(chatContainer);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(9, 9, 771, 401));
        chatLayout = new QVBoxLayout(verticalLayoutWidget_2);
        chatLayout->setObjectName("chatLayout");
        chatLayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout_4->addWidget(chatContainer);

        scrollArea_Chat->setWidget(scrollAreaChatWidgetContents);

        gridLayout->addWidget(scrollArea_Chat, 2, 1, 1, 1);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setMaximumSize(QSize(16777215, 150));

        gridLayout->addWidget(textEdit, 3, 1, 1, 1);

        label_Search = new QLabel(centralwidget);
        label_Search->setObjectName("label_Search");

        gridLayout->addWidget(label_Search, 0, 0, 1, 1);

        lineEdit_Search = new QLineEdit(centralwidget);
        lineEdit_Search->setObjectName("lineEdit_Search");
        lineEdit_Search->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(lineEdit_Search, 1, 0, 1, 1);

        pushButton_SendMes = new QPushButton(centralwidget);
        pushButton_SendMes->setObjectName("pushButton_SendMes");

        gridLayout->addWidget(pushButton_SendMes, 4, 1, 1, 1);

        scrollArea_Contacts = new QScrollArea(centralwidget);
        scrollArea_Contacts->setObjectName("scrollArea_Contacts");
        scrollArea_Contacts->setMaximumSize(QSize(300, 16777215));
        scrollArea_Contacts->setWidgetResizable(true);
        scrollAreaContactsWidgetContents = new QWidget();
        scrollAreaContactsWidgetContents->setObjectName("scrollAreaContactsWidgetContents");
        scrollAreaContactsWidgetContents->setGeometry(QRect(0, 0, 298, 635));
        verticalLayout = new QVBoxLayout(scrollAreaContactsWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        contactsContainer = new QWidget(scrollAreaContactsWidgetContents);
        contactsContainer->setObjectName("contactsContainer");
        verticalLayoutWidget = new QWidget(contactsContainer);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(9, 9, 261, 591));
        contactsLayout = new QVBoxLayout(verticalLayoutWidget);
        contactsLayout->setObjectName("contactsLayout");
        contactsLayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout->addWidget(contactsContainer);

        scrollArea_Contacts->setWidget(scrollAreaContactsWidgetContents);

        gridLayout->addWidget(scrollArea_Contacts, 2, 0, 3, 1);

        label_ActiveChat = new QLabel(centralwidget);
        label_ActiveChat->setObjectName("label_ActiveChat");

        gridLayout->addWidget(label_ActiveChat, 0, 1, 1, 1);

        Label_ActiveChatID = new QLabel(centralwidget);
        Label_ActiveChatID->setObjectName("Label_ActiveChatID");

        gridLayout->addWidget(Label_ActiveChatID, 1, 1, 1, 1);

        Messenger->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Messenger);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1146, 26));
        Messenger->setMenuBar(menubar);
        statusbar = new QStatusBar(Messenger);
        statusbar->setObjectName("statusbar");
        Messenger->setStatusBar(statusbar);

        retranslateUi(Messenger);

        QMetaObject::connectSlotsByName(Messenger);
    } // setupUi

    void retranslateUi(QMainWindow *Messenger)
    {
        Messenger->setWindowTitle(QCoreApplication::translate("Messenger", "MainWindow", nullptr));
        label_Search->setText(QCoreApplication::translate("Messenger", "\320\235\320\260\320\271\321\202\320\270 \321\207\320\260\321\202/\320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        pushButton_SendMes->setText(QCoreApplication::translate("Messenger", "Send Message", nullptr));
        label_ActiveChat->setText(QCoreApplication::translate("Messenger", "\320\220\320\272\321\202\320\270\320\262\320\275\321\213\320\271 \321\207\320\260\321\202", nullptr));
        Label_ActiveChatID->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Messenger: public Ui_Messenger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSENGER_H

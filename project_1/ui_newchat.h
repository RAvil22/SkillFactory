/********************************************************************************
** Form generated from reading UI file 'newchat.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCHAT_H
#define UI_NEWCHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewChat
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_Type;
    QRadioButton *radioButton_Pub;
    QRadioButton *radioButton_Pr;

    void setupUi(QDialog *NewChat)
    {
        if (NewChat->objectName().isEmpty())
            NewChat->setObjectName("NewChat");
        NewChat->resize(240, 320);
        buttonBox = new QDialogButtonBox(NewChat);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(10, 270, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(NewChat);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(9, 9, 221, 251));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_Type = new QLabel(verticalLayoutWidget);
        label_Type->setObjectName("label_Type");
        label_Type->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setFamilies({QString::fromUtf8("Chiller")});
        font.setPointSize(24);
        label_Type->setFont(font);

        verticalLayout->addWidget(label_Type, 0, Qt::AlignHCenter);

        radioButton_Pub = new QRadioButton(verticalLayoutWidget);
        radioButton_Pub->setObjectName("radioButton_Pub");
        radioButton_Pub->setFont(font);
        radioButton_Pub->setIconSize(QSize(20, 20));

        verticalLayout->addWidget(radioButton_Pub);

        radioButton_Pr = new QRadioButton(verticalLayoutWidget);
        radioButton_Pr->setObjectName("radioButton_Pr");
        radioButton_Pr->setFont(font);

        verticalLayout->addWidget(radioButton_Pr);


        retranslateUi(NewChat);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, NewChat, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, NewChat, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(NewChat);
    } // setupUi

    void retranslateUi(QDialog *NewChat)
    {
        NewChat->setWindowTitle(QCoreApplication::translate("NewChat", "Dialog", nullptr));
        label_Type->setText(QCoreApplication::translate("NewChat", "Select chat type", nullptr));
        radioButton_Pub->setText(QCoreApplication::translate("NewChat", "Public chat", nullptr));
        radioButton_Pr->setText(QCoreApplication::translate("NewChat", "Private chat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewChat: public Ui_NewChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCHAT_H

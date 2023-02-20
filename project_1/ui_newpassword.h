/********************************************************************************
** Form generated from reading UI file 'newpassword.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPASSWORD_H
#define UI_NEWPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewPassword
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_CP;
    QLineEdit *lineEdit_CP;
    QLabel *label_NP1;
    QLineEdit *lineEdit_NP1;
    QLabel *label_NP2;
    QLineEdit *lineEdit_NP2;

    void setupUi(QDialog *NewPassword)
    {
        if (NewPassword->objectName().isEmpty())
            NewPassword->setObjectName("NewPassword");
        NewPassword->resize(300, 360);
        buttonBox = new QDialogButtonBox(NewPassword);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(70, 310, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(NewPassword);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(9, 9, 281, 291));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_CP = new QLabel(verticalLayoutWidget);
        label_CP->setObjectName("label_CP");
        QFont font;
        font.setFamilies({QString::fromUtf8("Chiller")});
        font.setPointSize(20);
        label_CP->setFont(font);

        verticalLayout_2->addWidget(label_CP);

        lineEdit_CP = new QLineEdit(verticalLayoutWidget);
        lineEdit_CP->setObjectName("lineEdit_CP");
        lineEdit_CP->setMinimumSize(QSize(0, 40));
        lineEdit_CP->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(lineEdit_CP);

        label_NP1 = new QLabel(verticalLayoutWidget);
        label_NP1->setObjectName("label_NP1");
        label_NP1->setFont(font);

        verticalLayout_2->addWidget(label_NP1);

        lineEdit_NP1 = new QLineEdit(verticalLayoutWidget);
        lineEdit_NP1->setObjectName("lineEdit_NP1");
        lineEdit_NP1->setMinimumSize(QSize(0, 40));
        lineEdit_NP1->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(lineEdit_NP1);

        label_NP2 = new QLabel(verticalLayoutWidget);
        label_NP2->setObjectName("label_NP2");
        label_NP2->setFont(font);

        verticalLayout_2->addWidget(label_NP2);

        lineEdit_NP2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_NP2->setObjectName("lineEdit_NP2");
        lineEdit_NP2->setMinimumSize(QSize(0, 40));
        lineEdit_NP2->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(lineEdit_NP2);


        retranslateUi(NewPassword);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, NewPassword, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, NewPassword, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(NewPassword);
    } // setupUi

    void retranslateUi(QDialog *NewPassword)
    {
        NewPassword->setWindowTitle(QCoreApplication::translate("NewPassword", "Dialog", nullptr));
        label_CP->setText(QCoreApplication::translate("NewPassword", "Current password", nullptr));
        label_NP1->setText(QCoreApplication::translate("NewPassword", "New password", nullptr));
        label_NP2->setText(QCoreApplication::translate("NewPassword", "New password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewPassword: public Ui_NewPassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPASSWORD_H

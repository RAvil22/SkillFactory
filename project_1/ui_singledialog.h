/********************************************************************************
** Form generated from reading UI file 'singledialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEDIALOG_H
#define UI_SINGLEDIALOG_H

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

class Ui_SingleDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QDialog *SingleDialog)
    {
        if (SingleDialog->objectName().isEmpty())
            SingleDialog->setObjectName("SingleDialog");
        SingleDialog->resize(240, 200);
        buttonBox = new QDialogButtonBox(SingleDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(10, 150, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(SingleDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(9, 9, 222, 131));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setFamilies({QString::fromUtf8("Chiller")});
        font.setPointSize(16);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(200, 40));
        lineEdit->setMaximumSize(QSize(220, 16777215));

        verticalLayout->addWidget(lineEdit, 0, Qt::AlignHCenter);


        retranslateUi(SingleDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, SingleDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, SingleDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(SingleDialog);
    } // setupUi

    void retranslateUi(QDialog *SingleDialog)
    {
        SingleDialog->setWindowTitle(QCoreApplication::translate("SingleDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SingleDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SingleDialog: public Ui_SingleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEDIALOG_H

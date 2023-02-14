#include "qmessagewidget.h"

QMessageWidget::QMessageWidget(QWidget *parent, unsigned int senderID, QString senderName, time_t time, QString text)
    : QWidget{parent}
{
    senderID_ = new QLabel;
    senderID_->setText(QString::fromUtf8(std::to_string(senderID)));
    senderName_ = new QLabel();
    senderName_->setText(senderName);
    time_ = new QLabel;
    time_->setText(QString::fromUtf8(ctime(&time)));
    text_ = new QLabel;
    text_->setText(text);
    text_->setWordWrap(true);

    layout = new QVBoxLayout(this);
    layout->addWidget(senderName_);
    layout->addWidget(senderID_);
    layout->addWidget(time_);
    layout->addWidget(text_);

    //this->setStyleSheet("background-color:red"); //Меняет все
}

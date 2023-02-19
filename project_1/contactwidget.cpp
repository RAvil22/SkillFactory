#include "contactwidget.h"

QContactWidget::QContactWidget(unsigned int chatID, unsigned int chatType, QString chatName, QWidget *parent) : QWidget{parent}
{
    chatID_ = chatID;

    this->unreadMessages_ = new QLabel;
    this->unreadMessages_->setText("Unread messages ");

    this->chatCall_ = new QPushButton;
    if(chatType == 1){this->chatCall_->setText("Chat " + QString::fromUtf8(std::to_string(chatID)) + " " + chatName);}
    if(chatType == 2){this->chatCall_->setText("Contact " + QString::fromUtf8(std::to_string(chatID)) + " " + chatName);}

    this->layout_ = new QVBoxLayout(this);
    this->layout_->addWidget(this->chatCall_);
    this->layout_->addWidget(this->unreadMessages_);
    this->setLayout(layout_);

    connect(chatCall_, SIGNAL(clicked()), this, SLOT(chatCall()));

}

void QContactWidget::updateUnreadMessages(unsigned int unreadMessages){
    this->unreadMessages_->setText("Unread messages " + QString::fromUtf8(std::to_string(unreadMessages)));
}

const unsigned int QContactWidget::getChatID(void) const{
    return this->chatID_;
}

void QContactWidget::zeroUnread(void){
    this->unreadMessages_->setText("Unread messages 0");
}


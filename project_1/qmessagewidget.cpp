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

    layout_ = new QVBoxLayout(this);
    layout_->addWidget(senderName_);
    layout_->addWidget(senderID_);
    layout_->addWidget(time_);
    layout_->addWidget(text_);
    this->setLayout(layout_);
}

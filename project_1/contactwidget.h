#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class QContactWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QContactWidget(unsigned int chatID, unsigned int chatType, QString chatName, QWidget *parent = nullptr);
    void updateUnreadMessages(unsigned int unreadMessages);
    void setButtonText(QString text);
    const unsigned int getChatID(void) const;
    void zeroUnread(void);
private slots:
    void chatCall(void){
        emit chatCalled();
    }


signals:
    void chatCalled();

private:
    unsigned int chatID_;
    QPushButton *chatCall_;
    QLabel *unreadMessages_;
    QVBoxLayout *layout_;
};



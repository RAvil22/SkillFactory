#ifndef QMESSAGEWIDGET_H
#define QMESSAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <ctime>

class QMessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QMessageWidget(QWidget *parent = nullptr, unsigned int senderID = 0, QString senderName = "", time_t time = 0, QString text = "");

signals:

private:
    QLabel *senderID_;
    QLabel *senderName_;
    QLabel *time_;
    QLabel *text_;
    QVBoxLayout *layout;
};

#endif // QMESSAGEWIDGET_H

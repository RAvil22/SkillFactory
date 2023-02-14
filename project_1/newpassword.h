#pragma once

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class NewPassword;
}

class NewPassword : public QDialog
{
    Q_OBJECT

public:
    explicit NewPassword(std::string cP, QWidget *parent = nullptr);
    ~NewPassword();

private slots:
    void accept(void) override;
    void reject(void) override;
signals:
    void lineText(QString text);

private:
    Ui::NewPassword *ui;
    QString curPass;
};


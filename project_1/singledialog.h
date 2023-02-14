#ifndef SINGLEDIALOG_H
#define SINGLEDIALOG_H

#include <QDialog>

namespace Ui {
class SingleDialog;
}

class SingleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SingleDialog(QString lab, QWidget *parent = nullptr);
    ~SingleDialog();

private slots:
    void accept(void) override;
    void reject(void) override;
signals:
    void lineText(QString text);

private:
    Ui::SingleDialog *ui;
};

#endif // SINGLEDIALOG_H

#include "singledialog.h"
#include "ui_singledialog.h"

SingleDialog::SingleDialog(QString lab, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingleDialog)
{
    ui->setupUi(this);
    ui->label->setText(lab);
}

SingleDialog::~SingleDialog()
{
    delete ui;
}

void SingleDialog::accept(void){
    emit lineText(ui->lineEdit->text());
    done(0);
}

void SingleDialog::reject(void){
    done(0);
}

#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_find,SIGNAL(clicked()),this,SIGNAL(sendFindData()));

}

FindDialog::~FindDialog()
{
    delete ui;
    //test
}

QString FindDialog::getRequest()
{
    return ui->lineEdit->text();
}

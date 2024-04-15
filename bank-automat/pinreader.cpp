#include "pinreader.h"
#include "ui_pinreader.h"

pinReader::pinReader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pinReader)
{
    ui->setupUi(this);
    connect(ui->PIN_BT,SIGNAL(clicked(bool)),
            this,SLOT(handleClick()));
}

pinReader::~pinReader()
{
    qDebug()<<"pin tuhoutui";
    delete ui;
}

void pinReader::handleClick()
{
    qDebug()<<"PIN read sim hancleClick()";
    QString number = ui->PIN_LE->text();
    short num = number.toShort();
    emit sendPinNumToMain(num);
}

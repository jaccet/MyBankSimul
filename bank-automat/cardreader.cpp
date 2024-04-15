#include "cardreader.h"
#include "ui_cardreader.h"
#include <QDebug>
#include "pinui.h"

cardReader::cardReader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cardReader)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),
            this,SLOT(handleClick()));
    this->setStyleSheet("background-color: lightblue;");
}

cardReader::~cardReader()
{
    qDebug()<<"card tuhoutui";
    delete ui;
}

void cardReader::handleClick()
{
    qDebug()<<"RFID card reade sim handleClick()";
    QString number = ui->lineEdit->text();
    short num = number.toShort();
    emit sendCardNumToMain(num);

}

void cardReader::on_pushButton_clicked()
{
    pinUI *pinUIObject = new pinUI(this);
    connect(pinUIObject,SIGNAL(sendPinNumToMain(QString)),
            this,SLOT(handlePinNumberRead(QString)));
    pinUIObject->show();
    this->close();
}


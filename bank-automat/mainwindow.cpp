#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "pinui.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    serialPort = new QSerialPort(this);
    serialPort->setPortName("COM3");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    ui->setupUi(this);
    connect(ui->INSERT_CARD_BT,SIGNAL(clicked(bool)),
            this,SLOT(handleInserCardClick()));
    this->setStyleSheet("background-color: lightblue;");
}

MainWindow::~MainWindow()
{
    delete ui;
    serialPort->close();
    ui=nullptr;
}
//RFID
void MainWindow::dataHandler(){

    QByteArray rD = serialPort->readAll();
    qDebug() << rD;
    userid=rD;
    // ui->tekstiboksi->setText(rD);
    userid.remove(0,7);
    userid.chop(3);
    qDebug() << userid;

    if (userid.startsWith("CB1")){
        ui->INSERT_CARD_BT->animateClick();
        QString name="Mikki Hiiri";
        qDebug() << "mikki hiiri";
        serialPort->close();
    }
    if (userid.startsWith("CAA")){
        ui->INSERT_CARD_BT->animateClick();
        QString name="Aku Ankka";
        qDebug() << "Aku Ankka";
        serialPort->close();
    }
}

void MainWindow::on_INSERT_CARD_BT_clicked()
{
    ui->setupUi(this);
    pinpointer = new Pinuitest(this);
    ui->INSERT_CARD_BT->deleteLater();
    pinpointer->show();

}

void MainWindow::handleInserCardClick()
{
    //RFID
    qDebug()<<"handleInsertCardClick funktiossa";
    readerPtr = new cardReader(this);
    connect(readerPtr,SIGNAL(sendCardNumToMain(short)),
            this,SLOT(handleCardNumberRead(short)));
    readerPtr->show();
}
    //PIN
void MainWindow::handlePinNumberRead(QString numero)
{
    qDebug()<<"numero on : " << numero;
    ui->Current_PIN_NumberLE->setText(numero);
}
    //RFID
void MainWindow::handleCardNumberRead(short n)
{
    qDebug()<<"MainWindow handleCardNumberRead funktiossa";
    qDebug()<<"numero on = "<<n;
    cardNumber = n;
    ui->Current_CARD_NumberLE->setText(QString::number(n));
}

void MainWindow::on_LoginBT_clicked()
{
    qDebug()<<"login funktiossa";
    pankkiPtr = new pankkiSivu();
    pankkiPtr->show();
    close();
}



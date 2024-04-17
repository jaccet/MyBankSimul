#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "pinui.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rfidPtr = new rfid(this);
    rfidPtr->openPort();
    connect(ui->INSERT_CARD_BT,SIGNAL(clicked(bool)),
            this,SLOT(handleInserCardClick()));
    this->setStyleSheet("background-color: lightblue;");
    connect(rfidPtr->serialPort, SIGNAL(readyRead()), this,SLOT(handleInserCardClick()));
}
MainWindow::~MainWindow()
{
    delete ui;
    rfidPtr->closePort();
    ui=nullptr;
}

void MainWindow::handleInserCardClick()
{
    //RFID
    QByteArray rD = rfidPtr->readPort();
    qDebug() << rD;
    userid=rD;              // userID korvataan käyttäjällä, muutetaan tätä True/false metodiin että katsotaan onko käyttäjää olemassa.
    userid.remove(0,7);     // Rivit 47 - 48 leikkaa turhaa infoa kortista helpompaa lukua varten.
    userid.chop(3);
    qDebug() << userid;

    if (userid.startsWith("CB1")){
        ui->INSERT_CARD_BT->animateClick();
        QString name="Mikki Hiiri";
        qDebug() << "mikki hiiri";
        rfidPtr->closePort();
    }
    if (userid.startsWith("CAA")){
        ui->INSERT_CARD_BT->animateClick();
        QString name="Aku Ankka";
        qDebug() << "Aku Ankka";
        rfidPtr->closePort();
    }

}

//PIN

void MainWindow::handlePinNumberRead(QString numero)
{
    qDebug()<<"numero on : " << numero;
    ui->Current_PIN_NumberLE->setText(numero);
}

void MainWindow::on_LoginBT_clicked()
{
    qDebug()<<"login funktiossa";
    pankkiPtr = new pankkiSivu();
    pankkiPtr->show();
    close();
}



void MainWindow::on_INSERT_CARD_BT_clicked()
{
    pinpointer = new pinUI();
    pinpointer->show();
}


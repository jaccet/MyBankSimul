#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "pinui.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "menee tänne";
    rfidPtr = new rfid(this);
    rfidPtr->openPort();
    connect(ui->INSERT_CARD_BT,SIGNAL(clicked(bool)), this,SLOT(handleInserCardClick()));
    connect(rfidPtr->serialPort, SIGNAL(readyRead()), this,SLOT(handleInserCardClick()));
    restPtr = new REST_API;
    connect(restPtr, SIGNAL(cardChecked(bool)), this, SLOT(receiveCardCheck(bool)));

}


MainWindow::~MainWindow()
{
    delete ui;
    rfidPtr->closePort();
    delete restPtr;
    restPtr=nullptr;
    ui=nullptr;
}

void MainWindow::handleInserCardClick()
{
    //RFID

    QByteArray rD = rfidPtr->readPort();
    rfidPtr->closePort();
    qDebug() << rD;
    userid=rD;              // userID korvataan käyttäjällä, muutetaan tätä True/false metodiin että katsotaan onko käyttäjää olemassa.
    userid.remove(0,7);     // Rivit 47 - 48 leikkaa turhaa infoa kortista helpompaa lukua varten.
    userid.chop(3);
    qDebug() << userid;

    restPtr->checkCard(userid);
}

//PIN

void MainWindow::handlePinNumberRead(QString numero)
{
    qDebug()<<"numero on : " << numero;
    ui->Current_PIN_NumberLE->setText(numero);
}

void MainWindow::receiveLogin(bool loginResponse)
{
    qDebug()<<"login funktiossa";
    if (loginResponse == false){
        qDebug()<< "Väärin meni";
        rfidPtr->openPort();
        connect(rfidPtr->serialPort, SIGNAL(readyRead()), this,SLOT(handleInserCardClick()));
    } else {
        pankkiPtr = new pankkiSivu();
        pankkiPtr->show();
        close();
    }
}

void MainWindow::receiveCardCheck(bool cardCheckResult)
{
    if (cardCheckResult == false){
        qDebug() << "Wrong card";
        rfidPtr->openPort();
        connect(rfidPtr->serialPort, SIGNAL(readyRead()), this,SLOT(handleInserCardClick()));
    }
    else {
        pinpointer = new pinUI(this);
        connect(pinpointer,SIGNAL(loginResultFromPinUI(bool)),this,SLOT(receiveLogin(bool)));
        pinpointer->show();
    }
}


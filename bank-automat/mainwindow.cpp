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
    rfidPtr->portInfo();
    rfidPtr->openPort();
    connect(rfidPtr->serialPort, SIGNAL(readyRead()), this,SLOT(handleInserCardClick())); // Täytyy käyttää että connectautuu readRead() signaliin, lukemista varten.
    restPtr = new REST_API;
    connect(restPtr, SIGNAL(cardChecked(bool)), this, SLOT(receiveCardCheck(bool)));
    this->setStyleSheet("background-color: darkred;");
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
    QByteArray rD = rfidPtr->readPort();        // Tallettaa luetun serialport datan
    rfidPtr->closePort();                       // Sulkee portin
    qDebug() << rD;                             // Debuggeri koko datalle mitä serialportista tulee
    userid=rD;                                  // Katsoo käyttäjää ja luo siitä käsiteltävän muodon.
    userid.remove(0,7);                         // Remove(*,*) katsoo 1 arvossa että mistä lähdetään liikkeelle ja luku 7 osoittaa poistettujen merkkien määrää
    userid.chop(3);                             // Poistaa 3 merkkiä datan loppupäästä
    qDebug() << userid;                         // Debuggeri leikatulle käyttäjä tunnukselle.
    restPtr->checkCard(userid);                 // Pointteri RestAPI:n checkCard functioon
}

void MainWindow::receiveLogin(bool loginResponse)
{
    qDebug()<<"login funktiossa";
    if (loginResponse == false){
        qDebug()<< "Väärin meni";
        rfidPtr->openPort();
        connect(rfidPtr->serialPort, SIGNAL(readyRead()), this,SLOT(handleInserCardClick()));
    }

    else {
        qDebug()<< "Oikein meni";
        pankkiPtr = new pankkiSivu(this,restPtr);
        connect(pankkiPtr,SIGNAL(testSignal()),this,SLOT(showWindow()));
        pankkiPtr->show();
        this->hide();
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
        pinpointer = new pinUI(this,restPtr);
        connect(pinpointer,SIGNAL(loginResultFromPinUI(bool)),this,SLOT(receiveLogin(bool)));
        pinpointer->show();
    }
}

void MainWindow::showWindow()
{
    qDebug() << "signaali läpi";
    this->show();
}

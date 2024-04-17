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

    QByteArray rD = rfidPtr->readPort();    // Tallettaa luetun serialport datan
    rfidPtr->closePort();                   // Sulkee portin
    qDebug() << rD;                         //
    userid=rD;                              // Katsoo käyttäjää ja luo siitä käsiteltävän muodon.
    userid.remove(0,7);                     // Remove(*,*) katsoo 1 arvossa että mistä lähdetään liikkeelle ja luku 7 osoittaa poistettujen merkkien määrää
    userid.chop(3);                         // Poistaa 3 merkkiä datan loppupäästä
    qDebug() << userid;                     //
    restPtr->checkCard(userid);             // Pointteri RestAPI:n checkCard functioon

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

<<<<<<< HEAD
void MainWindow::on_INSERT_CARD_BT_clicked()
{
    pinpointer = new pinUI(this);
    pinpointer->show();
}

=======
>>>>>>> origin
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

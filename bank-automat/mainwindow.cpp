#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "pinui.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->stackedWidget->setCurrentIndex(0);
    qDebug() << "menee tänne";
    rfidPtr = new rfid(this);
    rfidPtr->portInfo();
    rfidPtr->openPort();
    connect(rfidPtr->serialPort, SIGNAL(readyRead()), this,SLOT(handleInserCardClick())); // Täytyy käyttää että connectautuu readRead() signaliin, lukemista varten.
    restPtr = new REST_API;
    connect(restPtr, SIGNAL(cardChecked(bool)), this, SLOT(receiveCardCheck(bool)));
    this->setStyleSheet("background-color: lightblue;");
    QList<QPushButton*> accountButtonList = {ui->LOPETA_BT, ui->OTTO_BT, ui->SALDO_BT, ui->TAKAISIN_BT, ui->TILITAPAHTUMAT_BT, ui->OTTO_TAKAISIN, ui->TILITAPAHTUMAT_TAKAISIN, ui->SALDO_TAKAISIN};
    for(QPushButton *button:accountButtonList){
        connect(button,SIGNAL(clicked(bool)),
                this,SLOT(accountButtonHandler()));
    }
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
    // Tämä kusee korjattava ettei aukea portti kun pinui destructoituu kun pankkisivu on päällä.
    qDebug()<<"login funktiossa";
    if (loginResponse == false){
        qDebug()<< "Väärin meni";
        rfidPtr->openPort();
        connect(rfidPtr->serialPort, SIGNAL(readyRead()), this,SLOT(handleInserCardClick()));
    }

    else {
        qDebug()<< "Oikein meni";
        ui->stackedWidget->setCurrentIndex(1);
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

void MainWindow::accountButtonHandler()
{
    QPushButton *button =qobject_cast<QPushButton*>(sender());
    if(button->objectName()== "OTTO_BT"){
        ui->stackedWidget->setCurrentIndex(2);
    }

    else if(button->objectName()== "TILITAPAHTUMAT_BT"){
        ui->stackedWidget->setCurrentIndex(3);
    }
    else if(button->objectName()== "SALDO_BT"){
        ui->stackedWidget->setCurrentIndex(4);
    }
    else if(button->objectName()== "TAKAISIN_BT"){
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(button->objectName()== "OTTO_TAKAISIN"){
        ui->stackedWidget->setCurrentIndex(1);

    }
    else if(button->objectName()== "SALDO_TAKAISIN"){
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(button->objectName()== "TILITAPAHTUMAT_TAKAISIN"){
        ui->stackedWidget->setCurrentIndex(1);
    }
    else{
        this->close();
    }
}

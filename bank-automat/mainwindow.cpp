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

/*    if (userid.startsWith("C1A")){
        ui->INSERT_CARD_BT->animateClick();
        rfidPtr->closePort();
    }
    if (userid.startsWith(cardNumber)){
        ui->INSERT_CARD_BT->animateClick();
        // QString name="Aku Ankka";
        // qDebug() << "Aku Ankka";
        rfidPtr->closePort();
    }
*/

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
    pinpointer = new pinUI(this);
    pinpointer->show();
}

void MainWindow::receiveCardCheck(bool cardCheckResult)
{
    if (cardCheckResult == false){
        qDebug() << "Wrong card";
    }
    else {
        ui->INSERT_CARD_BT->animateClick();
    }
}


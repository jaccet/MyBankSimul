#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "pinui.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet("background-image: url();");
    QMovie *bengali = new QMovie(QApplication::applicationDirPath()+"\\pankkialoitus.gif");
    ui->KUVA_BENGALI->setMovie(bengali);
    bengali->start();
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->stackedWidget->setCurrentIndex(0);
    qDebug() << "menee tänne";
    rfidPtr = new rfid(this);
    rfidPtr->portInfo();
    rfidPtr->openPort();
    connect(rfidPtr->serialPort, SIGNAL(readyRead()), this,SLOT(handleInserCardClick())); // Täytyy käyttää että connectautuu readyRead() signaliin, lukemista varten.
    restPtr = new REST_API;
    connect(restPtr, SIGNAL(cardChecked(bool)), this, SLOT(receiveCardCheck(bool)));
    connect(restPtr, SIGNAL(connectionError()),this,SLOT(connectioErrorHandler()));
    connect(restPtr, SIGNAL(transactionInfoReceived(QString)),this,SLOT(transactionInfoReceiver(QString)));
    connect(restPtr, SIGNAL(accountLogisticsReceived(QString)),this,SLOT(accountLogisticsReceiver(QString)));
    connect(restPtr, SIGNAL(loginSuccessful(bool)),this,SLOT(loginCheck(bool)));
    this->setStyleSheet("background-color: lightblue;");
    QList<QPushButton*> accountButtonList = {ui->LOPETA_BT, ui->OTTO_BT, ui->SALDO_BT, ui->TAKAISIN_BT, ui->TILITAPAHTUMAT_BT, ui->OTTO_TAKAISIN, ui->TILITAPAHTUMAT_TAKAISIN, ui->SALDO_TAKAISIN};
    QList<QPushButton*> ottoButtonList = {ui->OTTO_10E_BT,ui->OTTO_20E_BT,ui->OTTO_50E_BT,ui->OTTO_100E_BT};
    for(QPushButton *button:accountButtonList){
        connect(button,SIGNAL(clicked(bool)),
                this,SLOT(accountButtonHandler()));
    }
    for(QPushButton *button:ottoButtonList){
        connect(button,SIGNAL(clicked(bool)),this,SLOT(ottoButtonHandler()));
    }
}


MainWindow::~MainWindow()
{
    delete ui;
    rfidPtr->closePort();
    stopTimer();
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

void MainWindow::receiveLogin(QString pinNmr)
{
    qDebug() << "numero on : " << pinNmr;
    restPtr->requestLogin(pinNmr);
}

void MainWindow::loginCheck(bool loginResponse)
{
    if (loginResponse == false && ui->stackedWidget->currentIndex() == 0){
        qDebug()<< "Väärin meni";
        rfidPtr->openPort();
        connect(rfidPtr->serialPort, SIGNAL(readyRead()), this,SLOT(handleInserCardClick()));
    }

    else {
        qDebug()<< "Oikein meni";
        ui->stackedWidget->setCurrentIndex(1);
        startTimer();
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
        connect(pinpointer,SIGNAL(PINFromPinUI(QString)),this,SLOT(receiveLogin(QString)));
        pinpointer->show();
    }
}

void MainWindow::accountButtonHandler()
{
    QPushButton *button =qobject_cast<QPushButton*>(sender());
    if(button->objectName()== "OTTO_BT"){
        ui->stackedWidget->setCurrentIndex(2);
        updateTimer();
    }

    else if(button->objectName()== "TILITAPAHTUMAT_BT"){
        ui->stackedWidget->setCurrentIndex(3);
        restPtr->getTransactions();
        updateTimer();
    }
    else if(button->objectName()== "SALDO_BT"){
        ui->stackedWidget->setCurrentIndex(4);
        restPtr->getAccountLogistics();
        updateTimer();
    }
    else if(button->objectName()== "TAKAISIN_BT"){
        ui->stackedWidget->setCurrentIndex(0);
        rfidPtr->openPort();
        connect(rfidPtr->serialPort, SIGNAL(readyRead()), this,SLOT(handleInserCardClick()));
        restPtr->resetAll();
        stopTimer();
    }
    else if(button->objectName()== "OTTO_TAKAISIN"){
        ui->stackedWidget->setCurrentIndex(1);
        updateTimer();

    }
    else if(button->objectName()== "SALDO_TAKAISIN"){
        ui->stackedWidget->setCurrentIndex(1);
        ui->SALDO_LABEL->setText("");
        updateTimer();
    }
    else if(button->objectName()== "TILITAPAHTUMAT_TAKAISIN"){
        ui->stackedWidget->setCurrentIndex(1);
        ui->TILITAPAHTUMAT_LABEL->setText("");
        updateTimer();
    }
    else{
        stopTimer();
        this->close();
    }
}

void MainWindow::ottoButtonHandler()
{
    QPushButton *button =qobject_cast<QPushButton*>(sender());

    if(button->objectName() == "OTTO_10E_BT"){
        restPtr->withdrawalOperation(10);
        updateTimer();
    } else if(button->objectName() == "OTTO_20E_BT"){
        restPtr->withdrawalOperation(20);
        updateTimer();
    } else if(button->objectName() == "OTTO_50E_BT"){
        restPtr->withdrawalOperation(50);
        updateTimer();
    } else {
        restPtr->withdrawalOperation(100);
        updateTimer();
    }
}

void MainWindow::connectioErrorHandler()
{
    QMessageBox msgBox;

    msgBox.setText("Connection Error!");
    msgBox.exec();
    ui->stackedWidget->setCurrentIndex(0);
    restPtr->resetAll();
}

void MainWindow::transactionInfoReceiver(QString transactionInfo)
{
    ui->TILITAPAHTUMAT_LABEL->setText(transactionInfo);
}

void MainWindow::accountLogisticsReceiver(QString logistics)
{
    ui->SALDO_LABEL->setText(logistics);
}

void MainWindow::startTimer()
{
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(checkRemainingTime()));
    timer->start(1000);
    qDebug() << "Timer aloitettu onnistuneesti";
}

void MainWindow::updateTimer()
{
    timer->stop();
    remainingTime = 30;
    timer->start();
    qDebug() << "Timer asetettu takaisin 30:een";
}

void MainWindow::stopTimer()
{
    timer->stop();
    delete timer;
    timer = nullptr;
    remainingTime = 30;
    qDebug() << "Ajastin pysäytetty onnistuneesti.";
}

void MainWindow::checkRemainingTime()
{
    if (remainingTime == 0){
        qDebug() << "Aikakatkaisu";
        ui->stackedWidget->setCurrentIndex(0);
        restPtr->resetAll();
        stopTimer();
        rfidPtr->openPort();
        connect(rfidPtr->serialPort, SIGNAL(readyRead()), this,SLOT(handleInserCardClick()));
    }
    remainingTime--;
    qDebug() << "Aikaa vähhennetty" << remainingTime;
}


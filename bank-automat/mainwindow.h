#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QString>
#include <QByteArray>
#include <QtSerialPort>
#include <QDebug>
#include <QMessageBox>
#include <QMovie>
#include <QTimer>

#include "rest_api.h"
#include "rifd.h"
#include "pinui.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sendDataToPin(QString);

private slots:
    void handleInserCardClick();
    void receiveLogin(QString);
    //RFID
    void receiveCardCheck(bool);
    void accountButtonHandler();
    void ottoButtonHandler();
    void connectioErrorHandler();
    void transactionInfoReceiver(QString);
    void accountLogisticsReceiver(QString);
    void loginCheck(bool);
    // Timerin lohkoja
    void startTimer();
    void updateTimer();
    void stopTimer();
    void checkRemainingTime();

private:
    Ui::MainWindow *ui;
    pinUI * pinpointer;
    rfid * rfidPtr;
    QByteArray userid;
    REST_API * restPtr;
    // Timerin osia
    QTimer * timer;
    short remainingTime = 30;

};
#endif // MAINWINDOW_H

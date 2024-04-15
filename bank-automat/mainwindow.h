#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QString>
#include <QByteArray>
#include <QtSerialPort>
#include <QDebug>

#include "rest_api.h"
#include "cardreader.h"
#include "pankkisivu.h"
#include "pinui.h"
#include "pinuitest.h"

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
    void handleCardNumberRead(short);
    void on_LoginBT_clicked();
    void handlePinNumberRead(QString);
    void on_LoginBT_toggled(bool checked);
    //RFID
    void dataHandler();
    void on_SignalSender_clicked();
    void openPort();

private:
    Ui::MainWindow *ui;
    short cardNumber;
    short correctCardNumber = 1234;
    cardReader * readerPtr;
    pankkiSivu * pankkiPtr;
    QSerialPort * serialPort;
    QString userid;
    QString name;
    Pinuitest * pinpointer;
};
#endif // MAINWINDOW_H

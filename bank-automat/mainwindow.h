#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QString>
#include <QByteArray>
#include <QtSerialPort>
#include <QDebug>

#include "rest_api.h"
#include "rifd.h"
#include "pankkisivu.h"
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
    void on_LoginBT_clicked();
    void handlePinNumberRead(QString);
    //RFID
    void openPort();
    void on_INSERT_CARD_BT_clicked();
    void openAgain();
private:
    Ui::MainWindow *ui;
    short cardNumber;
    short correctCardNumber = 1234;
    pankkiSivu * pankkiPtr;
    pinUI * pinpointer;
    rfid * rfidPtr;
    QByteArray userid;
    void uiluonti();
};
#endif // MAINWINDOW_H

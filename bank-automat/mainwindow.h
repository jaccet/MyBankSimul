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
    void receiveLogin(bool);
    //RFID
    void receiveCardCheck(bool);
    void showWindow();


private:
    Ui::MainWindow *ui;
    pankkiSivu * pankkiPtr;
    pinUI * pinpointer;
    rfid * rfidPtr;
    QByteArray userid;
    REST_API * restPtr;
};
#endif // MAINWINDOW_H

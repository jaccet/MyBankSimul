#ifndef RIFD_H
#define RIFD_H

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
#include <QString>
#include <QDebug>

class rfid : public QObject
{
    Q_OBJECT

public:

    explicit rfid(QObject *parent = nullptr);
    void openPort();
    void closePort();
    void portInfo();
    QByteArray readPort();
    QSerialPort * serialPort;

private:
    QString portNumber;
    QString serInfo;


};

#endif // RIFD_H

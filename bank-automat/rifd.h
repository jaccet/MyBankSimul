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
    QByteArray readPort();
    QSerialPort * serialPort;

};

#endif // RIFD_H

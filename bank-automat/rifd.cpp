#include "rifd.h"

rfid::rfid(QObject *parent)
    : QObject{parent}
{}

void rfid::openPort()
{
    qDebug() << "Port is now open";
    serialPort = new QSerialPort(this);
    serialPort->setPortName("COM3");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
  //  connect(serialPort, &QSerialPort::readyRead, this, &rfid::readPort);
        if (serialPort->open(QIODevice::ReadOnly)) {
            qDebug() << "Serialport opened successfully.";
        }
        else {
            qDebug() << "unexpected error occured on port opening.";
        }
}

void rfid::closePort()
{
    serialPort->close();
}

QByteArray rfid::readPort()
{
    return serialPort->readAll();
}

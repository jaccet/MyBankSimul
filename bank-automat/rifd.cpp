#include "rifd.h"

rfid::rfid(QObject *parent)
    : QObject{parent}
{}

void rfid::openPort()               // Opening ports for later use.
{

    qDebug() << "Handling port opening";
    serialPort = new QSerialPort(this);
    serialPort->setPortName("COM3");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);

        if (serialPort->open(QIODevice::ReadOnly)) {
            qDebug() << "Serialport opened successfully.";
        }
        else {
            qDebug() << "unexpected error occured on port opening.";
        }

}

void rfid::closePort()              // Function for closing serialport.
{

    serialPort->close();

}

QByteArray rfid::readPort()         // Returning data to mainprogram.
{

    return serialPort->readAll();

}
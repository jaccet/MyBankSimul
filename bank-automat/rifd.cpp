#include "rifd.h"
#include <QSerialPortInfo>

rfid::rfid(QObject *parent)
    : QObject{parent}
{}

void rfid::openPort()                                               // Funktio porttien määrittämiselle.
{
    qDebug() << "Handling port opening";
    serialPort = new QSerialPort(this);
    serialPort->setPortName(portNumber);
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);

    if (serialPort->open(QIODevice::ReadOnly)) {
        qDebug() << "Serialport opened successfully.";
    }
    else {
        qDebug() << "unexpected error occured on port opening.";
    }

}

void rfid::closePort()                                              // Portti suljetaan.
{
    qDebug() << "portti sulettu";
    serialPort->close();

}

QByteArray rfid::readPort()                                         // Tuodaan luettu data MainWindowille.
{

    return serialPort->readAll();

}

void rfid::portInfo()
{
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        qDebug() << "Manufacturer:" << portInfo.serialNumber();
        serInfo = portInfo.serialNumber();                          // tallettaa RFID-lukijan sarjanumeron.

        if(serInfo == "OL56E09005B8EC2") {                          // tarkistaa RFID-lukijan sarjanumeron ja tallettaa sillä käytössä olevan portin käyttöä varten.
            qDebug() << "Port:" << portInfo.portName();
            portNumber = portInfo.portName();
        }
    }
}

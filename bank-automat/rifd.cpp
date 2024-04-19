#include "rifd.h"
#include <QSerialPortInfo>
rfid::rfid(QObject *parent)
    : QObject{parent}
{}

void rfid::openPort()               // Opening ports for later use.
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

void rfid::closePort()              // Function for closing serialport.
{
    qDebug() << "portti sulettu";
    serialPort->close();

}

QByteArray rfid::readPort()         // Returning data to mainprogram.
{

    return serialPort->readAll();

}

void rfid::portInfo()
{
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        qDebug() << "Manufacturer:" << portInfo.serialNumber();
        serInfo = portInfo.serialNumber();

        if(serInfo == "OL56E09005B8EC2") {                  // Katso RFID lukijan sarjanumeron ja tallettaa sillä käytössä olevan portin käyttöä varten
            qDebug() << "Port:" << portInfo.portName();
            portNumber = portInfo.portName();
        }
    }
}

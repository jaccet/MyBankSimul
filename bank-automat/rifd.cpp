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
        SerInfo = portInfo.serialNumber();

<<<<<<< HEAD
        if(SerInfo == "OL56E09005B8EC2") {
=======
        if(SerInfo == "OL56E09005B8EC2") {                  // Täytyy testata eliaksen koneella.
>>>>>>> cbdb0f26d222fc64b131d87c24cac466f46eb87a
            qDebug() << "Port:" << portInfo.portName();
            portNumber = portInfo.portName();
        }
    }
}

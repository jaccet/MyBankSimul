#include "rifd.h"
#include <QSerialPortInfo>
rfid::rfid(QObject *parent)
    : QObject{parent}
{}

void rfid::openPort()                                                       // Porttien avaaminen ja katsotaan onnistuiko avaaminen.
{

    qDebug() << "Handling port opening";                                    //
    serialPort = new QSerialPort(this);                                     //
    serialPort->setPortName(portNumber);                                    //
    serialPort->setBaudRate(QSerialPort::Baud9600);                         //
    serialPort->setDataBits(QSerialPort::Data8);                            //

        if (serialPort->open(QIODevice::ReadOnly)) {                        //
            qDebug() << "Serialport opened successfully.";                  //
        }
        else {                                                              // Error viesti epäonnistuneen portin avaamisen yhteydessä
            qDebug() << "unexpected error occured on port opening.";        //
        }

}

void rfid::closePort()                                                      // Suljetaan avoin portti.
{

    serialPort->close();

}

QByteArray rfid::readPort()                                                 // Palautetaan kortista luettu data, MainWindowi:in.
{

    return serialPort->readAll();

}

void rfid::portInfo()                                                       // Ratkaisu portin tunnistamisen automatisoinnille (tätä voidaan ehkä vähän siivota)
{
    const auto serialPortInfos = QSerialPortInfo::availablePorts();         //
    for (const QSerialPortInfo &portInfo : serialPortInfos) {               //
        qDebug() << "Port:" << portInfo.portName();                         //
        portNumber = portInfo.portName();                                   //
    }
}

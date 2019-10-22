#include "udpgcs.h"

udpgcs::udpgcs(QObject *parent) : QObject(parent)
{
    // create a QUDP socket
    socketModem = new QUdpSocket(this);
    socketPilot= new QUdpSocket(this);
    socketGimbal= new QUdpSocket(this);
    // time= new QDateTime();

    // The most common way to use QUdpSocket class is
    // to bind to an address and port using bind()
    // bool QAbstractSocket::bind(const QHostAddress & address,
    //     quint16 port = 0, BindMode mode = DefaultForPlatform)
    //socket->connectToHost("127.0.0.1",1234);
    //socketPilot->bind(QHostAddress("192.168.27.50"), 14550);//gcs address
    //socketModem->bind(QHostAddress("192.168.27.50"), 14580);
    // socketModem->bind(QHostAddress("10.8.0.62"), 14581);;//gcs address
    // socketModem->connectToHost(QString("10.8.0.66"), 14582, QIODevice::ReadWrite, QAbstractSocket::AnyIPProtocol);//rpi address
    // socketPilot->connectToHost(QString("10.8.0.66"), 14552, QIODevice::ReadWrite, QAbstractSocket::AnyIPProtocol);//rpi address
    /*qDebug() <<*/ //socketPilot->close();

    connect(socketModem, SIGNAL(readyRead()), this, SLOT(readyReadModem()));
    connect(socketGimbal, SIGNAL(readyRead()), this, SLOT(readyReadGimbal()));
    socketPilot->bind(QHostAddress("10.8.0.62"), 14551); //gcs address
    connect(socketPilot, SIGNAL(readyRead()), this, SLOT(readyReadPilot()));

    //msec=0; msec1=0;msec2=0;
}

void udpgcs::WriteModem(QByteArray Data)
{

    //socketModem->writeDatagram(Data,QHostAddress("192.168.27.17"), 14550);//rpi address
    socketModem->writeDatagram(Data,QHostAddress("10.8.0.66"), 14582);//rpi address
    //msec1=time->currentMSecsSinceEpoch();
    //qDebug()<<"date1"<<msecs1;
    qDebug() << "Message sent: " << Data;
}

void udpgcs::WritePilot(QByteArray Data)
{
    QHostAddress receiver;
    quint16 receiverPort;
    receiverPort=14552;
    receiver.setAddress("10.8.0.66"); //rpi address


    // socketPilot->writeDatagram(Data,QHostAddress("192.168.27.17"), 14550);//rpi address
    // qint64 dataSent=socketPilot->write(Data);//rpi address
    qint64 dataSent= socketPilot->writeDatagram(Data,receiver, receiverPort);//rpi address
    //msec1=time->currentMSecsSinceEpoch();
    //qDebug()<<"date1"<<msecs1;

    //    qDebug() << "Message sent: " << Data;
    //    qDebug() << "UdpSent: " << dataSent;

}

void udpgcs::WriteGimbal(QByteArray Data)
{
    QHostAddress receiver;
    quint16 receiverPort;
    receiverPort=14592;
    receiver.setAddress("10.8.0.66"); //rpi address


    // socketPilot->writeDatagram(Data,QHostAddress("192.168.27.17"), 14550);//rpi address
    // qint64 dataSent=socketPilot->write(Data);//rpi address
    qint64 dataSent= socketGimbal->writeDatagram(Data,receiver, receiverPort);//rpi address
    //msec1=time->currentMSecsSinceEpoch();
    //qDebug()<<"date1"<<msecs1;

//    qDebug() << "Message sent: " << Data;
//     qDebug() << "Message size: " << Data.size();

    //    qDebug() << "UdpSent: " << dataSent;

}
void udpgcs::readyReadModem()
{

    QByteArray buffer;

    buffer.resize(socketModem->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    socketModem->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
    //msec2=time->currentMSecsSinceEpoch();
    //msec=msec2-msec1;
    //qDebug()<<"date receive gcs"<<msec2 << " ms";
    //qDebug() << "Message from: " << sender.toString();
    // qDebug() << "Message port: " << senderPort;
    //  qDebug() << "Message: " << buffer;
    emit onModemChanged(buffer);


}

void udpgcs::readyReadPilot()
{

    QByteArray buffer;

    buffer.resize(socketPilot->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    socketPilot->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
    //msec2=time->currentMSecsSinceEpoch();
    //msec=msec2-msec1;
    //qDebug()<<"date receive gcs"<<msec2 << " ms";
    // qDebug() << "Message from: " << sender.toString();
    //    qDebug() << "Message port: " << senderPort;
    //qDebug() << "Message: " << buffer;
    emit onPilotChanged(buffer);


}
void udpgcs::readyReadGimbal()
{

    QByteArray buffer;

    buffer.resize(socketGimbal->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    socketGimbal->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
    //msec2=time->currentMSecsSinceEpoch();
    //msec=msec2-msec1;
    //qDebug()<<"date receive gcs"<<msec2 << " ms";
    //qDebug() << "Message from: " << sender.toString();
    // qDebug() << "Message port: " << senderPort;
    //  qDebug() << "Message: " << buffer;
    // emit onGimbalChanged(buffer);
}

void udpgcs::bindHost()
{

    socketModem->bind(QHostAddress("10.8.0.62"), 14581);;//gcs address
    connect(socketModem, SIGNAL(readyRead()), this, SLOT(readyReadModem()));
    socketPilot->bind(QHostAddress("10.8.0.62"), 14551); //gcs address
    connect(socketPilot, SIGNAL(readyRead()), this, SLOT(readyReadPilot()));
    socketGimbal->bind(QHostAddress("10.8.0.62"), 14591); //gcs address
    connect(socketGimbal, SIGNAL(readyRead()), this, SLOT(readyReadGimbal()));
}

udpgcs::~udpgcs()
{
    //socketPilot->close();
    //socketModem->close();
}

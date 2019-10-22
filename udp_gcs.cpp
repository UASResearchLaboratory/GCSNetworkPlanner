#include "udp_gcs.h"

Udp_GCS::Udp_GCS(QObject *parent) : QObject(parent)
{
    // create a QUDP socket
       socket = new QUdpSocket(this);
      // time= new QDateTime();

       // The most common way to use QUdpSocket class is
       // to bind to an address and port using bind()
       // bool QAbstractSocket::bind(const QHostAddress & address,
       //     quint16 port = 0, BindMode mode = DefaultForPlatform)
       //socket->connectToHost("127.0.0.1",1234);
       socket->bind(QHostAddress("192.168.27.17"), 1234);

       connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
//msec=0; msec1=0;msec2=0;
}

void Udp_GCS::HelloUDP()
{
    QByteArray Data;
       Data.append("Hello from UDP");

       // Sends the datagram datagram
       // to the host address and at port.
       // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram,
       //                      const QHostAddress & host, quint16 port)
       socket->writeDatagram(Data,QHostAddress("192.168.27.31"), 1234);
       //msec1=time->currentMSecsSinceEpoch();
       //qDebug()<<"date1"<<msecs1;

}

void Udp_GCS::readyRead()
{

    // when data comes in
    QByteArray buffer;

    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
    //                 QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).

    socket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
    //msec2=time->currentMSecsSinceEpoch();
     //msec=msec2-msec1;

    //qDebug()<<"latency"<<msec << " ms";
    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
    socket->writeDatagram(buffer,QHostAddress("192.168.27.31"), 1234);

}

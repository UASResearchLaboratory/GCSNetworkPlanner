#include "network_linker.h"


network_linker::network_linker(QObject *parent) : QObject(parent)
{
  udpSocket = new QUdpSocket(this);
}

void network_linker::initSocket()
{

        udpSocket->bind(QHostAddress::LocalHost, 7755);

        connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
}

void network_linker::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
         QNetworkDatagram datagram = udpSocket->receiveDatagram();
         QByteArray replyData = processThePayload(datagram.data());
         udpSocket->writeDatagram(datagram.makeReply(replyData));
     }
}



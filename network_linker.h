#ifndef NETWORK_LINKER_H
#define NETWORK_LINKER_H

#include <QObject>
#include <QUdpSocket>

class network_linker : public QObject
{
    Q_OBJECT
public:
    explicit network_linker(QObject *parent = nullptr);
   QUdpSocket * udpSocket;

signals:

public slots:
    void initSocket();
    void readPendingDatagrams();

#endif // NETWORK_LINKER_H

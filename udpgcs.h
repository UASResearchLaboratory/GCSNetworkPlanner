#ifndef UDPGCS_H
#define UDPGCS_H

#include <QObject>
#include <QUdpSocket>
#include <QDateTime>

class udpgcs : public QObject
{
    Q_OBJECT
public:
    explicit udpgcs(QObject *parent = nullptr);
    ~udpgcs();
    
    
    
signals:
    void onModemChanged(QByteArray);
    void onPilotChanged(QByteArray);

    
public slots:
    void WriteModem(QByteArray Data);
    void WritePilot(QByteArray Data);
    void readyReadModem();
    void readyReadPilot();
    void bindHost();
    void WriteGimbal(QByteArray Data);
    void readyReadGimbal();

    
private:
    QUdpSocket *socketModem;
    QUdpSocket *socketPilot, *socketGimbal;
    QDateTime * time;
    qint64 msec2;
    qint64 msec;
    qint64 msec1;

    
};

#endif // UDPGCS_H

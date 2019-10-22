#ifndef MODEM_DECODE_H
#define MODEM_DECODE_H

#include <QObject>
#include"QtSerialPort"
#include <QDebug>
#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <iostream>
#include <QSerialPortInfo>
#include <QProcess>
#include <QtNetwork/QNetworkInterface>

class modem_decode : public QObject
{
    Q_OBJECT
public:
    explicit modem_decode(QObject *parent = nullptr);

signals:
    void    wcdmaParameters(int,int,int);
    void    lteParameters(double,double,double,double);
    void    gsmParameters(int);
    void    sendNetworkGraphicTypes(QVariant networkSignal,QVariant networkType);
    void    guiLTEparameters(QVariant rssi,QVariant rsrp,QVariant sinr,QVariant rsrq);
    void    guiWCDMAparameters(QVariant rssi,QVariant rscp,QVariant ecio);
    void    guiGSMparameters(QVariant rssi);
    void    guiRangeparameters(QVariant RSSI,QVariant RSRP,QVariant RSRQ,QVariant SINR);
    void    sendModemCommands(QByteArray data);

    // void    sendNetworkType(QVariant networkType);


public slots:
    void SignalAnalytics(QByteArray data);
    void receiveModemQML(QVariant data);

private:
    QVariant networkSignal,networkType,networkRange,networkRangeRSSI,networkRangeRSRP,networkRangeRSRQ,networkRangeSINR;


    char  network[10];
    int wcdma_rssi,wcdma_rscp,wcdma_ecio;
    double lte_rssi,lte_rsrp;
    double gsm_rssi;
    double lte_sinr,lte_sinr2,lte_rsrq;
    double decodedRSSI,decodedRSRP,decodedSINR,decodedRSRQ;
    QString decodedNetworkType;
    int sizeRSSI,sizeRSRP,sizeSINR,sizeRSRQ;
    QByteArray sendModemData;

};

#endif // MODEM_DECODE_H

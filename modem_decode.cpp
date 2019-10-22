#include "modem_decode.h"

modem_decode::modem_decode(QObject *parent) : QObject(parent)
{
    //AT^SYSCFGEX="00",3FFFFFFF,1,2,7FFFFFFFFFFFFFFF,, change modem mode 00 auto 01 gsm 02 umts 03 lte
}

void modem_decode::SignalAnalytics(QByteArray data)
{
    //---------------------------CHECKING NETWORK TYPE------------------------------//
    decodedNetworkType=QString::fromStdString(data.mid(0,3).toStdString());
    //---------------------------START PROCESSING------------------------------//
    //--------------------------------WCDMA-----------------------------------//
    if (data.indexOf("WCD")!=-1)
    {
        std::sscanf(QString(data).toStdString().c_str(),"\r\n^HCSQ: \"WCDMA\",%i,%i,%i\r\n\r\nOK\r\n",&wcdma_rssi,&wcdma_rscp,&wcdma_ecio);
        wcdma_rssi=wcdma_rssi-120;
        wcdma_rscp=wcdma_rscp-120;
        wcdma_ecio=(wcdma_ecio/2)-32;
        guiWCDMAparameters(QVariant(wcdma_rssi),QVariant(wcdma_rscp),QVariant(wcdma_ecio));
        emit wcdmaParameters(wcdma_rssi,wcdma_rscp,wcdma_ecio);
    }
    //--------------------------------LTE-----------------------------------//
    if (decodedNetworkType.indexOf("LTE")!=-1)
    {
        networkType=("LTE");
        //--------------------------------DECODING DATA-----------------------------------//
        sizeRSSI=data.mid(3,1).toInt();
        sizeRSRP=data.mid(4,1).toInt();
        sizeRSRQ=data.mid(5,1).toInt();
        sizeSINR=data.mid(6,1).toInt();
        lte_rssi=data.mid(data.size()-sizeRSSI-sizeRSRP-sizeRSRQ-sizeSINR,sizeRSSI).toDouble();
        lte_rsrp=data.mid(data.size()-sizeRSRP-sizeRSRQ-sizeSINR,sizeRSRP).toDouble();
        lte_rsrq=data.mid(data.size()-sizeRSRQ-sizeSINR,sizeRSRQ).toDouble();
        lte_sinr=data.mid(data.size()-sizeSINR,sizeSINR).toDouble();

        //        lte_rssi=data.mid(sizeRSSI,sizeRSSI-7).toDouble();
        //        lte_rsrp=data.mid(size,6).toDouble();
        //        lte_sinr=data.mid(20,5).toDouble();
        //        qDebug()<< lte_sinr;
        //        lte_rsrq=data.mid(15,5).toDouble();

        /////////////////////////////////////////////////////////////////////////////////////
        //--------------------------------PROCESSING DATA-----------------------------------//
        {
            if (lte_rssi>-65)
            {
                // qDebug()<<"RSSI LTE excellent";
                networkSignal=("EXCELLENT");
                networkRangeRSSI=("EXCELLENT");
            }
            else if (lte_rssi<=-65&&-75<lte_rssi)
            {
                //  qDebug()<<"RSSI LTE good";
                networkSignal=("GOOD");
                networkRangeRSSI=("GOOD");
            }
            else if (lte_rssi<=-75&& -85<lte_rssi)
            {
                networkSignal=("FAIR");
                networkRangeRSSI=("FAIR");
            }
            else if (lte_rssi<=-85&&-95<lte_rssi)
            {
                //qDebug()<<"RSSI LTE poor";
                networkSignal=("POOR");
                networkRangeRSSI=("POOR");

            }
            else if (lte_rssi<=-95)
            {
                //qDebug()<<"RSSI LTE poor";
                networkSignal=("NO SIGNAL");
            }

        }
        ////////////////////////////////////////////////////////////////////////////////////

        {
            if (lte_rsrp>-85)
            {
                networkRangeRSRP=("EXCELLENT");
            }
            else if (lte_rsrp<=-85&&lte_rsrp>=-102)
            {
                networkRangeRSRP=("GOOD");
            }
            else if (lte_rsrp<-102&&lte_rsrp>=-112)
            {
                networkRangeRSRP=("FAIR");
            }
            else if (lte_rsrp<-112)
            {
                networkRangeRSRP=("POOR");
            }

        }

        ////////////////////////////////////////////////////////////////////////////////////

        {
            if (lte_rsrq>-10)
            {
                networkRangeRSRQ=("EXCELLENT");
            }
            else if (-10>lte_rsrq&&lte_rsrq>=-15)
            {
                networkRangeRSRQ=("GOOD");
            }

            else if (-15>lte_rsrq&&lte_rsrq>=-20)
            {
                networkRangeRSRQ=("FAIR");
            }
            else if (lte_rsrq<-20)
            {
                networkRangeRSRQ=("POOR");

            }

        }
        ////////////////////////////////////////////////////////////////////////////////////
        {
            if (lte_sinr>20)
            {
                networkRangeSINR=("EXCELLENT");
            }
            else if (20>=lte_sinr&&lte_sinr>13)
            {
                networkRangeSINR=("GOOD");
            }
            else if (13>=lte_sinr&&lte_sinr>=0)
            {
                networkRangeSINR=("FAIR");
            }

            else if (lte_sinr<0)
            {
                networkRangeSINR=("POOR");
            }

        }
        ////////////////////////////////////////////////////////////////////////////////////
        //--------------------------------SENDING DATA-----------------------------------//
        guiRangeparameters(networkRangeRSSI,networkRangeRSRP,networkRangeRSRQ,networkRangeSINR);
        sendNetworkGraphicTypes(networkType,networkSignal);
        guiLTEparameters(QVariant(lte_rssi),QVariant(lte_rsrp),QVariant(lte_sinr),QVariant(lte_rsrq));
        lteParameters(lte_rssi,lte_rsrp,lte_rsrq,lte_sinr);
    }
    //--------------------------------GSM-----------------------------------//
    if (data.indexOf("GSM")!=-1)
    {//--------------------------------PROCESSING-----------------------------------//
        networkType=("GSM");
        sizeRSSI=data.mid(3,1).toInt();
        gsm_rssi=data.mid(data.size()-sizeRSSI,sizeRSSI).toDouble();
       // qDebug()<<"RSSI" << gsm_rssi;

        if (gsm_rssi>=-70)
        {
            // qDebug()<<"RSSI LTE excellent";
            networkSignal=("EXCELLENT");
            networkRangeRSSI=("EXCELLENT");
        }
        else if (-70>gsm_rssi&&gsm_rssi>-85)
        {
            //  qDebug()<<"RSSI LTE good";
            networkSignal=("GOOD");
            networkRangeRSSI=("GOOD");
        }//
        else if (-85>gsm_rssi && gsm_rssi>=-100)
        {
            // qDebug()<<"RSSI LTE fair";
            networkSignal=("FAIR");
            networkRangeRSSI=("FAIR");
        }

        else if (gsm_rssi<-100&&gsm_rssi>-110)
        {
            networkRangeRSSI=("POOR");
            networkSignal=("POOR");
        }else if (gsm_rssi<=-110)
        {
            networkSignal=("NO SIGNAL");
        }

        //--------------------------------SENDING DATA-----------------------------------//
        sendNetworkGraphicTypes(networkType,networkSignal);
        guiGSMparameters(QVariant(gsm_rssi));

    }
}

void modem_decode::receiveModemQML(QVariant data)
{
    sendModemData.append(data.toString());
    sendModemCommands(sendModemData);
    sendModemData.clear();
      qDebug()<< data.toString();
}

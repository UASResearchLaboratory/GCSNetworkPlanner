#include "logging.h"

logging::logging(QObject *parent) : QObject(parent)
{
    timeS=QDateTime::currentDateTime().toMSecsSinceEpoch();
    timeM=time.currentDateTime().toString("yyyy-MM-dd_hh:mm:ss,zzz");
    timeL=timeM;
    timeN2=0;



}

void logging::setFileNamePitch()
{
    filenameP="/home/moumou/pitch_"+timeL+"_.txt";
    QFile file( filenameP );
        internFileP=filenameP;
        timer.start();
}


void logging::setFileNameYaw()
{
    filenameY="/home/moumou/Yaw_"+timeL+"_.txt";
        QFile file( filenameY );
        internFileY=filenameY;
        timer.start();
}
void logging::setFileNameRoll()
{
    filenameR="/home/moumou/roll_"+timeL+"_.txt";
        QFile file( filenameR );
        internFileR=filenameR;
        timer.start();
}


void logging::setFileNameAltitude()
{
    filenameALT="/home/moumou/Alt_"+timeL+"_.txt";
        QFile file( filenameALT );
        internFileALT=filenameALT;
        timer.start();
}
void logging::setFileNameGPSLat()
{
    filenameALT="/home/moumou/GPSLat_"+timeL+"_.txt";
        QFile file( filenameGPSLat);
        internFileGPSLa=filenameGPSLat;
        timer.start();
}
void logging::setFileNameGPSLong()
{
    filenameALT="/home/moumou/GPSLong_"+timeL+"_.txt";
        QFile file( filenameGPSLong);
        internFileGPSLong=filenameGPSLong;
        timer.start();
}
////////////////////////////////////////////////////////////////////////////////////////
void logging::writeInTheFileYaw(float data)
{


    QFile intern(internFileY);
            if ( intern.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) )
            {
                timeN2=timeN;
                timeN=timer.elapsed();
                QTextStream stream( &intern );
                stream <<timeN<<" | " << data<<  endl;

            }
    }
void logging::writeInTheFileRoll(float data)
{


    QFile intern(internFileR);
            if ( intern.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) )
            {
                timeN2=timeN;
                timeN=timer.elapsed();
                QTextStream stream( &intern );
                stream <<timeN<<" | " << data<<  endl;

            }
    }
void logging::writeInTheFilePitch(float data)
{


    QFile intern(internFileP);
            if ( intern.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) )
            {
                timeN2=timeN;
                timeN=timer.elapsed();
                QTextStream stream( &intern );
                stream <<timeN<<" | " << data<<  endl;

            }
    }
void logging::writeInTheFileAltitude(float data)
{


    QFile intern(internFileALT);
            if ( intern.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) )
            {
                timeN2=timeN;
                timeN=timer.elapsed();
                QTextStream stream( &intern );
                stream <<timeN<<" | " << data<<  endl;

            }
    }
void logging::writeInTheFileGPSLat(double data)
{


    QFile intern(internFileGPSLa);
            if ( intern.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) )
            {
                timeN2=timeN;
                timeN=timer.elapsed();
                QTextStream stream( &intern );
                stream <<timeN<<" | " << data<<  endl;

            }
    }
void logging::writeInTheFileGPSLong(double data)
{


    QFile intern(internFileGPSLong);
            if ( intern.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) )
            {
                timeN2=timeN;
                timeN=timer.elapsed();
                QTextStream stream( &intern );
                stream <<timeN<<" | " << data<<  endl;

            }
    }

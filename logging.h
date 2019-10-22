#ifndef LOGGING_H
#define LOGGING_H

#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include "QTime"
#include "QElapsedTimer"

class logging : public QObject
{
    Q_OBJECT
public:
    explicit logging(QObject *parent = nullptr);

    QString  timeL,timeM ,internFileP,internFileY,internFileR,internFileALT,internFileGPSLa,internFileGPSLong,
              filenameY,filenameP,filenameR,filenameALT,filenameGPSLat,filenameGPSLong;
    QDateTime time;
    qint64 timeT,timeS,timeN, timeN2;
    QElapsedTimer timer;

signals:

public slots:

    void setFileNameYaw();
    void setFileNamePitch();
    void setFileNameRoll();
    void setFileNameAltitude();
    void setFileNameGPSLat();
    void setFileNameGPSLong();


    void writeInTheFileYaw(float data);
    void writeInTheFilePitch(float data);
    void writeInTheFileRoll(float data);
    void writeInTheFileAltitude(float data);
    void writeInTheFileGPSLat(double data);
    void writeInTheFileGPSLong(double data);
};

#endif // LOGGING_H

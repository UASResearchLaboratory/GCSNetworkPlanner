#ifndef DJIGCS_H
#define DJIGCS_H

#include <QObject>
#include <QtMath>
#include <QStringList>
#include <QString>
#include <QTimer>
#include <DJI_HardDriver.h>
#include <DJI_Camera.h>
#include <DJI_Flight.h>
#include <DJI_HotPoint.h>
#include <DJI_Follow.h>
#include <DJI_WayPoint.h>
#include <DJI_VirtualRC.h>
#include <DJI_API.h>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QItemDelegate>
#include <QMutex>
#include <QThread>
#include <QComboBox>
#include <QTextBrowser>
#include "djigcs/QonboardSDK.h"


namespace DJI
{
    namespace onboardSDK
    {
        class DjiGcs : public QObject
        {
            Q_OBJECT
        public:
            explicit DjiGcs(QObject *parent = 0);
            static void setControlCallback(CoreAPI *This, Header *header, UserData userData);
            static void activationCallback(CoreAPI *This, Header *header, UserData userData);
            void functionAlloc();
            void log(QString str);

            void updateObtainControlButton(QVariant var);
            void updateActivationButton(QVariant var);

            void startUpdateFlightInstruments(int msec);

        signals:
            void signalUpdateObtainControlButton(QVariant var);
            void signalUpdateActivationButton(QVariant var);
            void connectionStatus(QVariant);
            void appendDjiApiLogQML(QVariant);

            void sigUpdateUavRoll(float val);
            void sigUpdateUavPitch(float val);
            void sigUpdateUavHeading(float val);
            void sigUpdateUavAltitude(float val);
            void sigUpdateUavGPS(QVariant xc,QVariant yc);

        protected:
            void timerEvent(QTimerEvent *);

        public slots:
            void init(QVariant list);
            void apiCoreSetControl(QVariant var);
            void apiCoreActive(QVariant var);
            void apiCoreDroneVersion();
            void taskTakeOff();
            void taskLanding();
            void taskGoHome();

            void updateUavRoll();
            void updateUavPitch();
            void updateUavHeading();
            void updateUavAltitude();
            void updateUavGPS();
            void printValue();

        private:
            CoreAPI *api;
            QtOnboardsdkPortDriver *driver;
            QByteArray *key;
            Flight *flight;
            VirtualRC *vrc;
            HotPoint *hp;
            Camera *cam;
            Follow *follow;
            WayPoint *wp;
            WayPointData wayPointDataTmp;
            QTimer timerUpdateFlightInstruments;
        };
    }
}

#endif // DJIGCS_H

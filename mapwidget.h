#ifndef MAPWIDGET_H
#define MAPWIDGET_H
#include <QVBoxLayout>
#include <QObject>
#include <QWidget>
#include <QQuickView>
#include <QtQuick>
#include "mavlink/mavlink_raw_message.h"

#include "qquickwidget.h"

class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = nullptr);
    QObject *rootObject;

signals:
    void signalCoordinate(QVariant xc,QVariant yc);
    void angleCoordinate(QVariant anglec);
    void YawPitchRollValues(QVariant yawv,QVariant pitchv,QVariant rollv);
    void BatteryValuesSignal(QVariant volyagev, QVariant percentagev,QVariant currentv);

public slots:

    void slotLatitudeUpdate(QString valueLatitude);
    void slotLongitudeUpdate(QString valueLongitude);
    void slotAngleUpdate (QString valueAngle);
    void slotYawPitchRollUpdate (QString yaw,QString pitch, QString roll);
    void slotBatteryInfoUpdate(QString ValueVoltage,QString ValuePercentage, QString ValueCurrent);
private:

    QQuickView *view;
    QVBoxLayout *layout;
    QWidget *container;
    QVariant latitude,longitude;
    QVariant yaw,pitch,roll;
    QVariant voltage,percentage,current;
    QVariant angle;
    QQuickWidget *quickwidget;
    Mavlink_Raw_Message *rawMessage;
};

#endif // MAPWIDGET_H

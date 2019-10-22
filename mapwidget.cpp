#include "mapwidget.h"

MapWidget::MapWidget(QWidget *parent) : QWidget(parent)
{
    latitude=0;
    longitude=0;
    angle = 0;
    yaw=0;
    pitch=0;
    roll= 0;
    layout = new QVBoxLayout();
    rawMessage= new Mavlink_Raw_Message();

    view = new QQuickView();
    view->setSource(QUrl::fromLocalFile(":/QmlFiles/main.qml"));
    view->setResizeMode(QQuickView::SizeRootObjectToView);
   // view->resize(1024,768);
    view->lower();
    container = QWidget::createWindowContainer(view, this);
    layout->addWidget(container);
    setLayout(layout);
    resize(500,500);
    rootObject = view->rootObject();
     view->lower();






     QObject::connect(rootObject,SIGNAL(takeoff()),rawMessage,SLOT(arm()));
     QObject::connect(this,SIGNAL(signalCoordinate(QVariant,QVariant)),rootObject,SLOT(slotRefresh(QVariant,QVariant)));
     QObject::connect(this,SIGNAL(angleCoordinate(QVariant)),rootObject,SLOT(angleRefresh(QVariant)));
     QObject::connect(this,SIGNAL(YawPitchRollValues(QVariant,QVariant,QVariant)),rootObject,SLOT(yawpitchrollRefresh(QVariant,QVariant,QVariant)));
     QObject::connect(this,SIGNAL(BatteryValuesSignal(QVariant,QVariant,QVariant)),rootObject,SLOT(batteryInfoRefresh(QVariant,QVariant,QVariant)));


}

void MapWidget::slotLatitudeUpdate(QString valueLatitude)
{
    latitude = QVariant(valueLatitude.toDouble());
    emit signalCoordinate(latitude,longitude);
   // qDebug()<<111;
}

void MapWidget::slotLongitudeUpdate(QString valueLongitude)
{
    longitude = QVariant(valueLongitude.toDouble());
    emit signalCoordinate(latitude,longitude);
}
void MapWidget::slotAngleUpdate(QString valueAngle)
{
    angle=QVariant(valueAngle.toDouble());
    emit angleCoordinate(angle);

}

void MapWidget::slotYawPitchRollUpdate(QString ValueYaw,QString ValuePitch, QString ValueRoll)
{
    yaw=QVariant(ValueYaw.toDouble());
    pitch=QVariant(ValuePitch.toDouble());
    roll=QVariant(ValueRoll.toDouble());
    emit YawPitchRollValues(yaw,pitch,roll);
}
void MapWidget::slotBatteryInfoUpdate(QString ValueVoltage,QString ValuePercentage, QString ValueCurrent)
{
    voltage=QVariant(ValueVoltage.toDouble());
    percentage=QVariant(ValuePercentage.toDouble());
    current=QVariant(ValueCurrent.toDouble());
    emit BatteryValuesSignal(voltage,percentage,current);
}

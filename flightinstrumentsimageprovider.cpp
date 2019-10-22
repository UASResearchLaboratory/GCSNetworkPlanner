#include "flightinstrumentsimageprovider.h"
#include "QImage"
#include <QThread>
#include <QDebug>
#include <QtMath>

FlightInstrumentsImageProvider::FlightInstrumentsImageProvider():
    QQuickImageProvider(QQuickImageProvider::Image)
{
    int sizeWidget = 300;


    adi.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    adi.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    alt.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    alt.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    hsi.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    hsi.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    adi.setFixedSize(sizeWidget,sizeWidget);
    hsi.setFixedSize(sizeWidget,sizeWidget);
    alt.setFixedSize(sizeWidget,sizeWidget);

    vb.addWidget(&adi);
    vb.addWidget(&hsi);
    vb.addWidget(&alt);

    widget.setLayout(&vb);
    widget.setFixedSize(sizeWidget+20,sizeWidget*3);

    alpha_mask.load(":/images/alpha_mask.bmp");

    widget.show();
    QThread::msleep(5);
    widget.hide();
    QThread::msleep(5);
}
QImage FlightInstrumentsImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    QImage img = widget.grab().toImage().convertToFormat(QImage::Format_ARGB32);
    img=img.scaled(alpha_mask.size());
    img.setAlphaChannel(alpha_mask);
    return img;
}

void FlightInstrumentsImageProvider::updateUavRoll(float val)
{
    adi.setRoll(qRadiansToDegrees(val));
    adi.update();
}

void FlightInstrumentsImageProvider::updateUavPitch(float val)
{
    adi.setPitch(qRadiansToDegrees(val));
    adi.update();
}

void FlightInstrumentsImageProvider::updateUavHeading(float val)
{
    hsi.setHeading(qRadiansToDegrees(val));
    hsi.update();
}

void FlightInstrumentsImageProvider::updateUavAltitude(float val)
{
    alt.setAltitude(val);
    alt.update();
}

void FlightInstrumentsImageProvider::updateFlightInstruments()
{
    // adi.update();
    // hsi.update();
    // alt.update();
    emit sigUpdateFlightsInstruments();
}
void FlightInstrumentsImageProvider::startUpdateFlightInstruments(int msec)
{
    timer_updateFlightInstruments.setInterval(msec);
    QObject::connect(&timer_updateFlightInstruments,SIGNAL(timeout()),this,SLOT(updateFlightInstruments()));
    timer_updateFlightInstruments.start();
}

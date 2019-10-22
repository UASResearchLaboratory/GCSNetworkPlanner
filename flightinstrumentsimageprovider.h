#ifndef FIIP_H
#define FIIP_H

#include <QObject>
#include <QQuickItem>
#include <QQuickImageProvider>
#include <QTimer>
#include "QVBoxLayout"
#include "qfi_ADI.h"
#include "qfi_HSI.h"
#include "qfi_ALT.h"

class FlightInstrumentsImageProvider : public QObject, public QQuickImageProvider
{
    Q_OBJECT
public:
    FlightInstrumentsImageProvider();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    void startUpdateFlightInstruments(int msec);
public slots:
    void updateUavRoll(float val);
    void updateUavPitch(float val);
    void updateUavHeading(float val);
    void updateUavAltitude(float val);
    void updateFlightInstruments();

signals:
    void sigUpdateFlightsInstruments();
private:
    QImage img;
    qfi_ADI adi;
    qfi_HSI hsi;
    qfi_ALT alt;
    QWidget widget;
    QVBoxLayout vb;
    QImage alpha_mask;
    QTimer timer_updateFlightInstruments;

};

#endif // FIIP_H

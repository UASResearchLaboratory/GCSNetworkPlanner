#ifndef QMLPLOT_H
#define QMLPLOT_H

#include <QtQuick>
#include "qtimer.h"
#include "qcustomplot.h"

class QCustomPlot;
class QCPAbstractPlottable;
static int readyToPlot=0;
static double battery=0;
static double lte_rssi,lte_rsrp,lte_rsrq,lte_sinr=0;
static double _pitch,_yaw=0;
static QList<float> receivedPar;

class CustomPlotItem : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CustomPlotItem( QQuickItem* parent = 0 );
    Q_INVOKABLE void zoomX(double scale);
    virtual ~CustomPlotItem();

    void paint( QPainter* painter );

    Q_INVOKABLE void initCustomPlot();
    int indexed;

public slots:
    void uavParameters(float  data);
    void uavParameters2(float yaw,float pitch);
    void modemLteParameters(double rssi, double rsrp, double rsrq, double sinr);
    void realtimeDataSlot();
    void mavParameters(QList<float> data);
    void treatementQMLPlot(QVariant index);
    void treatementRT(int index);

protected:
    void routeMouseEvents( QMouseEvent* event );
    void routeWheelEvents( QWheelEvent* event );

    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );
    virtual void wheelEvent( QWheelEvent *event );

    virtual void timerEvent(QTimerEvent *event);

private:
    QCustomPlot*         m_CustomPlot,* customplot2;
    int                  m_timerId;
    QTimer * dataTimer;
    float  yaw,did;
    static float yaw2;
    double data =0;
    QCPAxis *xAxisL, *yAxisL, *xAxis2L, *yAxis2L;
    QCPLayoutGrid *subLayout;
    QCPAxisRect *ar, *ar2;


    QCPGraph *mainGraphCos;
    QVariant indexV;

private slots:
    void graphClicked( QCPAbstractPlottable* plottable );
    void onCustomReplot();
    void updateCustomPlotSize();



};

#endif // QMLPLOT_H

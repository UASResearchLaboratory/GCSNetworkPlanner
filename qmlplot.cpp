#include "qmlplot.h"
//#include "qcustomplot.h"
#include <QDebug>
#include <qmath.h>


CustomPlotItem::CustomPlotItem( QQuickItem* parent ) : QQuickPaintedItem( parent )
  , m_CustomPlot( nullptr ), m_timerId( 0 )
{
    setFlag( QQuickItem::ItemHasContents, true );
    setAcceptedMouseButtons( Qt::AllButtons );
    dataTimer=new QTimer();
    readyToPlot=0;
    battery=0;
    //indexed=0;
    connect( this, &QQuickPaintedItem::widthChanged, this, &CustomPlotItem::updateCustomPlotSize );
    connect( this, &QQuickPaintedItem::heightChanged, this, &CustomPlotItem::updateCustomPlotSize );
}

CustomPlotItem::~CustomPlotItem()
{
    delete m_CustomPlot;
    m_CustomPlot = nullptr;

    if(m_timerId != 0) {
        killTimer(m_timerId);
    }
}


void CustomPlotItem::initCustomPlot()
{
    m_CustomPlot = new QCustomPlot();
    ar = new QCPAxisRect(m_CustomPlot);
    ar2 = new QCPAxisRect(m_CustomPlot);
    subLayout=new QCPLayoutGrid;


    updateCustomPlotSize();
    m_CustomPlot->addGraph(ar->axis(QCPAxis::atBottom),ar->axis(QCPAxis::atLeft));
    m_CustomPlot->addGraph(ar2->axis(QCPAxis::atBottom),ar2->axis(QCPAxis::atLeft));
     m_CustomPlot->addGraph();
    m_CustomPlot->plotLayout()->addElement(1,0,ar2);
    m_CustomPlot->plotLayout()->addElement(2,0,ar);
    // ar->addAxis(QCPAxis::atLeft);
    ar->setupFullAxesBox();
    m_CustomPlot->graph( 0 )->setPen( QPen( Qt::red ) );
    m_CustomPlot->graph( 1 )->setPen( QPen( Qt::blue ) );
    m_CustomPlot->graph(2)->setPen(QPen(Qt::green));


    m_CustomPlot->xAxis->setLabel( "t" );
    m_CustomPlot->yAxis->setLabel( "S" );
    //m_CustomPlot->xAxis->setRange( 0, 10 );
    //m_CustomPlot->yAxis->setRange( 0, 5 );
    m_CustomPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom );
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ar->axis(QCPAxis::atBottom)->setTicker(timeTicker);
    m_CustomPlot->xAxis->setTicker(timeTicker);
    m_CustomPlot->axisRect()->setupFullAxesBox();
    m_CustomPlot->yAxis->setRange(-0.5,0.5);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(m_CustomPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_CustomPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_CustomPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_CustomPlot->yAxis2, SLOT(setRange(QCPRange)));
    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer->start(0); // Interval 0 means to refresh as fast as possible
    startTimer(100);

    connect( m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot );
    m_CustomPlot->replot();

    qDebug()<< "ready to plot: "<< readyToPlot;
}

void CustomPlotItem::uavParameters(float data)
{
    battery= (double)data*360/(2*M_PI);
    // qDebug()<<"battery 1 "<<battery;

    //    if (readyToPlot==1)
    //        realtimeDataSlot();
}

void CustomPlotItem::uavParameters2(float yaw, float pitch)
{
    _yaw=(double)qRadiansToDegrees(yaw) ;
    _pitch=(double)qRadiansToDegrees(pitch) ;

}

void CustomPlotItem::modemLteParameters(double rssi, double rsrp, double rsrq, double sinr)
{
    lte_rssi=rssi;
    lte_rsrp=rsrp;
    lte_rsrq=rsrq;
    lte_sinr=sinr;

}


void CustomPlotItem::treatementQMLPlot(QVariant index)
{
    indexed=index.toInt();
    qDebug()<< "C++ indexed:"<< indexed;
}
void CustomPlotItem::realtimeDataSlot()
{

    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

    static double lastPointKey = 0;

  //   qDebug()<<"yaw on func " << indexed;

        if (indexed==0)


        { if (key-lastPointKey > 0.002) // at most add point every 2 ms
            {

            m_CustomPlot->graph(0)->addData(key, lte_rssi);
        m_CustomPlot->graph(1)->addData(key,lte_rsrp);
        m_CustomPlot->graph(2)->addData(key,lte_sinr);
        // rescale value (vertical) axis to fit the current data:
        m_CustomPlot->graph(0)->rescaleValueAxis(true);
        m_CustomPlot->graph(1)->rescaleValueAxis(true);
        m_CustomPlot->graph(2)->rescaleValueAxis(true);
        lastPointKey = key;
        m_CustomPlot->replot();


            }}
        else if (indexed==1)

        {
            if (key-lastPointKey > 0.002) // at most add point every 2 ms
            {

            m_CustomPlot->graph(0)->data().clear();
            m_CustomPlot->graph(1)->data().clear();
            m_CustomPlot->graph(2)->data().clear();
            m_CustomPlot->clearGraphs();
            m_CustomPlot->graph(0)->addData(key, _yaw);
        // rescale value (vertical) axis to fit the current data:
        m_CustomPlot->graph(0)->rescaleValueAxis(true);
        lastPointKey = key;
        m_CustomPlot->replot();

       }
            else {
                m_CustomPlot->clearPlottables();
                m_CustomPlot->replot();

            }
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    m_CustomPlot->xAxis->setRange(key, 100, Qt::AlignRight);
    ar->axis(QCPAxis::atBottom)->setRange(key, 100, Qt::AlignRight);
    ar2->axis(QCPAxis::atBottom)->setRange(key, 100, Qt::AlignRight);

    m_CustomPlot->replot();

//treatementRT(indexed);
//    static QTime time(QTime::currentTime());
//    // calculate two new data points:
//    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

//    static double lastPointKey = 0;

//    // qDebug()<<"yaw on func " << yaw;
//    if (key-lastPointKey > 0.002) // at most add point every 2 ms
//    {
//        m_CustomPlot->graph(0)->addData(key, lte_rssi);
//        m_CustomPlot->graph(1)->addData(key,lte_rsrp);
//        m_CustomPlot->graph(2)->addData(key,lte_sinr);
//        // rescale value (vertical) axis to fit the current data:
//        m_CustomPlot->graph(0)->rescaleValueAxis(true);
//        m_CustomPlot->graph(1)->rescaleValueAxis(true);
//        m_CustomPlot->graph(2)->rescaleValueAxis(true);
//        lastPointKey = key;
//    }
//    // make key axis range scroll with the data (at a constant range size of 8):
//    m_CustomPlot->xAxis->setRange(key, 100, Qt::AlignRight);
//    ar->axis(QCPAxis::atBottom)->setRange(key, 100, Qt::AlignRight);
//    ar2->axis(QCPAxis::atBottom)->setRange(key, 100, Qt::AlignRight);

//    m_CustomPlot->replot();



//    //        // calculate frames per second:
//    //        static double lastFpsKey;
//    //        static int frameCount;
//    //        ++frameCount;
//    //        if (key-lastFpsKey > 2) // average fps over 2 seconds
//    //        {
//    //          ui->statusBar->showMessage(
//    //                QString("%1 FPS, Total Data points: %2")
//    //                .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
//    //                .arg(m_CustomPlot->graph(0)->data()->size()+m_CustomPlot->graph(1)->data()->size())
//    //                , 0);
//    //          lastFpsKey = key;
//    //          frameCount = 0;
//    //        }
}


void CustomPlotItem::treatementRT(int index)
{


}


void CustomPlotItem::mavParameters(QList<float> data)
{
    receivedPar=data;
}




void CustomPlotItem::paint( QPainter* painter )
{
    if (m_CustomPlot)
    {
        QPixmap    picture( boundingRect().size().toSize() );
        QCPPainter qcpPainter( &picture );

        m_CustomPlot->toPainter( &qcpPainter );

        painter->drawPixmap( QPoint(), picture );
    }
}

void CustomPlotItem::mousePressEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::mouseReleaseEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotItem::mouseDoubleClickEvent( QMouseEvent* event )
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents( event );
}

void CustomPlotItem::wheelEvent( QWheelEvent *event )
{
    routeWheelEvents( event );
}

void CustomPlotItem::timerEvent(QTimerEvent *event)
{
    static double t, U;
    U = battery; //((double)rand() / RAND_MAX) * 5;
    // m_CustomPlot->graph(0)->addData(t, U);
    //qDebug() << Q_FUNC_INFO << QString("Adding dot t = %1, S = %2").arg(t).arg(U);
    t++;
    m_CustomPlot->replot();
}

void CustomPlotItem::graphClicked( QCPAbstractPlottable* plottable )
{
    qDebug() << Q_FUNC_INFO << QString( "Clicked on graph '%1 " ).arg( plottable->name() );
}

void CustomPlotItem::routeMouseEvents( QMouseEvent* event )
{
    if (m_CustomPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
    }
}

void CustomPlotItem::routeWheelEvents( QWheelEvent* event )
{
    if (m_CustomPlot)
    {
        QWheelEvent* newEvent = new QWheelEvent( event->pos(), event->delta(), event->buttons(), event->modifiers(), event->orientation() );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
    }
}

void CustomPlotItem::updateCustomPlotSize()
{
    if (m_CustomPlot)
    {
        m_CustomPlot->setGeometry(0, 0, (int)width(), (int)height());
        m_CustomPlot->setViewport(QRect(0, 0, (int)width(), (int)height()));
    }
}


void CustomPlotItem::onCustomReplot()
{
    //qDebug() << Q_FUNC_INFO;
    update();
}
void CustomPlotItem::zoomX(double scale)
{
    auto rect = m_CustomPlot->axisRect(0);
    auto axis = rect->axis(QCPAxis::AxisType::atBottom);
    axis->scaleRange(scale, axis->pixelToCoord(rect->center().x()));
    m_CustomPlot->replot();
}

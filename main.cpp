
#include <QApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QObject>
#include <QTimer>

#include "flightinstrumentsimageprovider.h"
#include "udpgcs.h"
#include "djigcs.h"
#include <QJoysticks.h>
#include <QStyleFactory>
#include <QQmlApplicationEngine>
#include <QtSerialPort/QSerialPort>
#include <QPalette>
#include <QQmlContext>
#include "mavlink/serialportreader.h"
#include "mavlink/mavlink_raw_message.h"
#include "joystickparameters.h"
#include <QStandardPaths>
#include "qmlplot.h"
#include "qcustomplot.h"
#include "modem_decode.h"
#include "QDir"
#include "logging.h"
#include "mavlink/mav_gcs_manager.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // loading flightinstruments
    FlightInstrumentsImageProvider* fii = new FlightInstrumentsImageProvider();
    Mavlink_Raw_Message *mav_dec= new Mavlink_Raw_Message();
    SerialPortReader *serial=new SerialPortReader();
    JoystickParameters *joystick=new JoystickParameters();
    udpgcs * udp= new udpgcs();
    modem_decode * huawei= new modem_decode ();
    CustomPlotItem * plot = new CustomPlotItem();
    logging * log = new logging();
    QGimball *gimbal=new QGimball;







    // loading QML view
    QQuickView w;
    QQmlEngine * engine = w.engine();
    QDir dir("/home/dayaa/.cache/QtLocation");
   dir.removeRecursively();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //    QGuiApplication app(argc, argv);

    qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");

    QQmlApplicationEngine engineP;
    // engineP.load(QUrl(QLatin1String("qrc:/PlotMain.qml")));
    /*
     * QJoysticks is single instance, you can use the "getInstance()" function
     * directly if you want, or you can create a pointer to it to make code
     * easier to read;
     */
    QJoysticks* instance = QJoysticks::getInstance();

    /* Enable the virtual joystick */
    instance->setVirtualJoystickRange (1);
    instance->setVirtualJoystickEnabled (true);
    /*
     * Register the QJoysticks with the QML engine, so that the QML interface
     * can easilly use it.
     */
    engine->rootContext()->setContextProperty("QJoysticks", instance);
    engine->rootContext()->setContextProperty("mavJoy",mav_dec);
    engine->addImageProvider("FlightInstrumentsImageProvider",fii);
    w.setSource(QUrl("qrc:/UavMapForm.qml"));
    //log->setFileName();




    w.setResizeMode(QQuickView::SizeRootObjectToView);

    // qml root object instance
    QQuickItem *  item =w.rootObject();



    //loading DJI manager
    DJI::onboardSDK::DjiGcs dji;
    udp->bindHost();

    //    //    //--------UDP__Connection----------//
    QObject::connect(udp,SIGNAL(onPilotChanged(QByteArray)),mav_dec,SLOT(dds_mavlink_decode(QByteArray)),Qt::DirectConnection);
    QObject::connect(mav_dec,SIGNAL(dds_mavlink_encodeSignal(QByteArray)),udp,SLOT(WritePilot(QByteArray)),Qt::DirectConnection);
    QObject::connect(udp,SIGNAL(onModemChanged(QByteArray)),huawei,SLOT(SignalAnalytics(QByteArray)),Qt::DirectConnection);

    QObject::connect(mav_dec,SIGNAL(plotParameters(QList<float>)),plot,SLOT(mavParameters(QList<float>)),Qt::DirectConnection);
    QObject::connect(mav_dec,SIGNAL(attitudeyaw(float)),plot,SLOT(uavParameters(float)),Qt::DirectConnection);
    QObject::connect(mav_dec,SIGNAL(attitudegauges(float,float)),plot,SLOT(uavParameters2(float,float)),Qt::DirectConnection);
    QObject::connect(huawei,SIGNAL(lteParameters(double,double,double,double)),plot,SLOT(modemLteParameters(double,double,double,double)),Qt::DirectConnection);

    //QObject::connect(&meteo,SIGNAL(sizeCities()),item,SIGNAL(meteoSize()));
    QObject::connect(item,SIGNAL(plotIndexChanged(QVariant)),plot,SLOT(treatementQMLPlot(QVariant)),Qt::DirectConnection);
    QObject::connect(fii,SIGNAL(sigUpdateFlightsInstruments()),item,SLOT(updateFlightsInstruments()),Qt::DirectConnection);
    QObject::connect(item,SIGNAL(newDdsArgumentsDJI(QVariant)),&dji,SLOT(init(QVariant)));
    QObject::connect(&dji,SIGNAL(connectionStatus(QVariant)),item,SLOT(connectionStatusUpdate(QVariant)));
    QObject::connect(mav_dec,SIGNAL(signalCoordinate(QVariant,QVariant)),item,SLOT(updateUavGPS(QVariant,QVariant)));
    //    QObject::connect(&dji,SIGNAL(sigUpdateUavPitch(float)),fii,SLOT(updateUavPitch(float)));
    //    QObject::connect(&dji,SIGNAL(sigUpdateUavRoll(float)),fii,SLOT(updateUavRoll(float)));
    //    QObject::connect(&dji,SIGNAL(sigUpdateUavHeading(float)),fii,SLOT(updateUavHeading(float)));
    //    QObject::connect(&dji,SIGNAL(sigUpdateUavAltitude(float)),fii,SLOT(updateUavAltitude(float)));
    //--------Mavlink__Gauges----------//
    QObject::connect(mav_dec,SIGNAL(attitudeyaw(float)),log,SLOT(writeInTheFileYaw(float)));
    QObject::connect(mav_dec,SIGNAL(attitudepitch(float)),log,SLOT(writeInTheFilePitch(float)));
    QObject::connect(mav_dec,SIGNAL(attituderoll(float)),log,SLOT(writeInTheFileRoll(float)));
      QObject::connect(mav_dec,SIGNAL(attitudealtitude(float)),log,SLOT(writeInTheFileAltitude(float)));
        QObject::connect(mav_dec,SIGNAL(gpslatituderaw(double)),log,SLOT(writeInTheFileGPSLat(double)));
           QObject::connect(mav_dec,SIGNAL(gpslongituderaw(double)),log,SLOT(writeInTheFileGPSLong(double)));
   //////////////////
    QObject::connect(mav_dec,SIGNAL(attitudeyaw(float)),fii,SLOT(updateUavHeading(float)));
    QObject::connect(mav_dec,SIGNAL(attitudepitch(float)),fii,SLOT(updateUavPitch(float)));
    QObject::connect(mav_dec,SIGNAL(attituderoll(float)),fii,SLOT(updateUavRoll(float)));
    // QObject::connect(mav_dec,SIGNAL(attitude(float)),fii,SLOT(updateUavHeading(float)));
    QObject::connect(mav_dec,SIGNAL(angleCoordinate(QVariant)),item,SLOT(angleRefresh(QVariant)));
    //--------Mavlink__Commands----------//


    QObject::connect(item,SIGNAL(flightCommandTakeOff()),mav_dec,SLOT(arm()));
    QObject::connect(item,SIGNAL(flightCommandLand()),mav_dec,SLOT(disarm()));
  //  QObject::connect(item,SIGNAL(flightCommandRtl()),mav_dec,SLOT(returntolaunch()));
      QObject::connect(item,SIGNAL(flightCommandRtl()),mav_dec,SLOT(parameter_shrinker()));


    //--------END----------//

    QObject::connect(item,SIGNAL(buttonVersionClicked()),&dji,SLOT(apiCoreDroneVersion()));
    QObject::connect(item,SIGNAL(activateDjiUav(QVariant)),&dji,SLOT(apiCoreActive(QVariant)));
    QObject::connect(item,SIGNAL(djiObatainControl(QVariant)),&dji,SLOT(apiCoreSetControl(QVariant)));

    QObject::connect(&dji,SIGNAL(appendDjiApiLogQML(QVariant)),item,SLOT(appendDjiApiLogQML(QVariant)));
    QObject::connect(&dji,SIGNAL(signalUpdateActivationButton(QVariant)),item,SLOT(updateActivateButton(QVariant)));
    QObject::connect(&dji,SIGNAL(signalUpdateObtainControlButton(QVariant)),item,SLOT(updateObtainControlButton(QVariant)));

    QObject::connect(item,SIGNAL(flightCommandTakeOff()),mav_dec,SLOT(arm()));
    QObject::connect(item,SIGNAL(flightCommandLand()),mav_dec,SLOT(disarm()));
    // QObject::connect(item,SIGNAL(flightCommandRtl()),mav_dec,SLOT(returntolaunch()));

    //-------------Latititude_longitude_Signals_to_mission------------//
    QObject::connect(item,SIGNAL(sendSignalLatitude(QVariant)),mav_dec,SLOT(get_QML_test(QVariant)));
    QObject::connect(item,SIGNAL(sendSignalLongitude(QVariant)),mav_dec,SLOT(get_QML_test_long(QVariant)));

    //---------Joystick_Connections_____________//
    QObject::connect(item,SIGNAL(joystickParameters(double,double)),joystick,SLOT(get_axis_qml(double,double)));
    QObject::connect(item,SIGNAL(joystickValue(double,double)),joystick,SLOT(get_axis_value_qml(double,double)));
    QObject::connect(item,SIGNAL(joystickProtocolChanged(int)),joystick,SLOT(get_joystick_protocol_qml(int)));
    QObject::connect(joystick,SIGNAL(qmlMavLinkjoystickcontrols(int,int,int,int)),mav_dec,SLOT(ch3_joystick(int,int,int,int)));
    //---------Mission_Modes_____________//
    QObject::connect(item,SIGNAL(sendSignalFlightModes(int,int)),mav_dec,SLOT(setMode(int,int)));
    QObject::connect(mav_dec,SIGNAL(sendMissionSetResult(QVariant)),item,SLOT(resultFlightMode(QVariant)));
    //    QObject::connect(item,SIGNAL(missionResultSignal(int)),mav_dec,SLOT(setIndexMode(int)));
    //     QObject::connect(mav_dec,SIGNAL(indexModeAccepted(QVariant)),item,SLOT(resultIndex(QVariant)));
    //---------CELLULAR_NETWORK_PROCESSING_____________//
    QObject::connect(huawei,SIGNAL(sendNetworkGraphicTypes(QVariant,QVariant)),item,SIGNAL(sendNetworkIcons(QVariant,QVariant)));
    QObject::connect(huawei,SIGNAL(guiLTEparameters(QVariant,QVariant,QVariant,QVariant)),item,SIGNAL(guiQMLLTEParameters(QVariant,QVariant,QVariant,QVariant)));
    QObject::connect(huawei,SIGNAL(guiWCDMAparameters(QVariant,QVariant,QVariant)),item,SIGNAL(guiQMLWCDMAParameters(QVariant,QVariant,QVariant)));
    QObject::connect(huawei,SIGNAL(guiGSMparameters(QVariant)),item,SIGNAL(guiQMLGSMParameters(QVariant)));
    QObject::connect(huawei,SIGNAL(guiRangeparameters(QVariant,QVariant,QVariant,QVariant)),item,SIGNAL(guiQMLRangeParameters(QVariant,QVariant,QVariant,QVariant)));
    QObject::connect(item,SIGNAL(setTypeNetworkIndex(QVariant)),huawei,SLOT(receiveModemQML(QVariant)));
    QObject::connect(huawei,SIGNAL(sendModemCommands(QByteArray)),udp,SLOT(WriteModem(QByteArray)));
    //---------GIMBAL_PROCESSING_____________//
    QObject::connect(instance,SIGNAL(PovSend(QByteArray)),udp,SLOT(WriteGimbal(QByteArray)));
    QObject::connect(mav_dec,SIGNAL( qmlBatteryInfoSignal(QVariant,QVariant,QVariant)),item,SLOT(getBatteryData(QVariant,QVariant,QVariant)),Qt::DirectConnection);



    fii->startUpdateFlightInstruments(41);
    dji.startUpdateFlightInstruments(41);

    QString  momo= QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation);
    qDebug()<<momo;



    //qmlEngine.rootContext()->setContextProperty ("QJoysticks", instance);



    /*
     * Load main.qml and run the application.
     */
    //qmlEngine.load (QUrl (QStringLiteral ("qrc:/joystick.qml")));

    w.show();

    // QObject *rect = item->findChild<QObject*>("windowJoystick");



    return a.exec();
}

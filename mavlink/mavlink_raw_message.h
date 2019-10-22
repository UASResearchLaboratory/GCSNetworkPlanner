#ifndef MAVLINK_RAW_MESSAGE_H
#define MAVLINK_RAW_MESSAGE_H

#include <QObject>
#include "serialportreader.h"
#include "qtsdljoystick.h"
#include <QQuickView>
#include <QtQuick>
#include "QJoysticks.h"



class Mavlink_Raw_Message : public QObject
{
    Q_OBJECT
public:
    explicit Mavlink_Raw_Message(QObject *parent = 0);

    void    imu_scaled_values(mavlink_message_t message_2d);
    void    gps_int_values(mavlink_message_t message_2d);
    void    gps_raw_values(mavlink_message_t message_2d);
    void    sys_values(mavlink_message_t message_2d);
    void    heartbeat_values(mavlink_message_t message_2d);
    void    attitude_values(mavlink_message_t message_2d);
    void    altitude_values(mavlink_message_t message_2d);
    void    decode_joystick(mavlink_message_t message_2d);

signals:

    void    uav_type(QString);
    void    uav_autopilot(QString);
    void    sys_status(QString);

    void    batterypercentage(int);
    void    battery_voltage(double);
    void    battery_current(double);
    void    sys_packets_dropped_rate(double);

    void    timebootms(double);
    void    signalCoordinate(QVariant xc,QVariant yc);
    void    angleCoordinate(QVariant anglec);
    void    sendMissionSetResult(QVariant result);
    void     sendgimbal(int);

    void    gpslatitudeint(double);
    void    gpslongtitudeint(double);
    void    gpsaltitudeint(int32_t);
    void    gpsvxint(double);

    void    gpslatituderaw(double);
    void    gpslongtituderaw(double);
    void    gpsaltituderaw(double);
    void    gps_type_fix(QString);

    void    imuxacc(float);
    void    imuyacc(float);
    void    imuzacc(float);

    void    imuxgyro(float);
    void    imuygyro(float);
    void    imuzgyro(float);

    void    imuxmag(float);
    void    imuymag(float);
    void    imuzmag(float);

    void    abspressure(float);
    void    diffpressure(float);
    void    temperature(float);
    void    attitudegauges(float,float);
    void    attitudeyaw(float);
    void    attitudepitch(float);
    void    attituderoll(float);
    void    attitudeparams(float,float,float);
    double  attitudedoubleyaw(double);
    void    armSignal(QByteArray);
    void    disarmSignal(QByteArray);
    void    ch3HighSignal(QByteArray);
    void    ch3LowSignal(QByteArray);
    void    ch3JoySignal(QByteArray);
    void    dds_mavlink_encodeSignal(QByteArray);
    void    dds_mavlink_encodeSignalQML(QVariant);
    void    plotParameters(QList<float>);

    //GUI_Signals

    void    guibatterypercentage(QString);
    void    guigps_type_fix(QString);
    void    guiuav_type(QString);

    void    guibattery_voltage(QString);
    void    guibattery_current(QString);
    void    guisys_packets_dropped_rate(QString);
    void    guisys_status(QString);

    void    guigpslatitudeint(QString);
    void    guigpslongtitudeint(QString);
    void    guigpsaltitudeint(QString);
    void    guigpsvxint(QString);

    void    guigpslatituderaw(QString);
    void    guigpslongtituderaw(QString);
    void    guigpsaltituderaw(QString);

    void    guiimuxacc(QString);
    void    guiimuyacc(QString);
    void    guiimuzacc(QString);

    void    guiimuxgyro(QString);
    void    guiimuygyro(QString);
    void    guiimuzgyro(QString);

    void    guiimuxmag(QString);
    void    guiimuymag(QString);
    void    guiimuzmag(QString);

    void    guiabspressure(QString);
    void    guidiffpressure(QString);
    void    guitemperature(QString);

    void    guiattitudeyaw(QString);
    void    guiattitudepitch(QString);
    void    guiattituderoll(QString);
    //QML Signals
    void    qmlYawPitchRollSignal(QString,QString,QString);
    void    qmlBatteryInfoSignal(QVariant voltage,QVariant percentage,QVariant current);
    void    qmljoystickcontrols(int roll,int pitch,int yaw,int thorttle);
    void    indexModeAccepted(QVariant index);

public slots:

    void    dds_mavlink_decode(QByteArray array);
    void    arm();
    void    disarm();
    void    takeoff();
    void    returntolaunch();
    void    setMode(int baseMode, int customMode);
    void    heartbeat_slot();
    void    ch3_high();
    void    ch3_low();
    void    ch3_joystick(int roll, int pitch, int yaw, int throttle);
    void    mavlink_joystick();
    void    dds_mavlink_encode(mavlink_message_t message);
    void    test_joystick(int js,int axis,qreal value);
    void    get_joystick_protocol_qml(int index);
    void    get_axis_qml(double currentAxis,double currentParameter);
    void    get_axis_value_qml(double currentAxis,double currentValue);
   void    get_axis_combobx(QVariant combobox);
    void    countWP(int count);
    void    clearWP();
    void    get_QML_test(QVariant latitude);
    void    get_QML_test_long(QVariant longitude);
    void    send_ping();
    void    get_ping(mavlink_message_t message);
    void    set_message_interval(float message, float interval);
    void    set_stabilized_mode();
    void    decode_command_long(mavlink_message_t message);
    void    parameter_shrinker();
    void    handleSpeech(QByteArray data);
    void    decodeSpeech();
    void    setIndexMode(int index);
    void    setIndexModeResult();

    QStringList deviceNames() const;


private:
    mavlink_status_t lastStatus;
    uint8_t cp;
    mavlink_message_t message,message2,pingmessage;
    mavlink_status_t status;
    uint16_t msgReceived;
    uint64_t seq,seq2,seq1;

    QtSDLJoystick *sdljoy;
    QTimer * timer;
    int16_t _roll, _pitch, _yaw, _throttle,_throttle1, axisvalue,rollAxis,pitchAxis,yawAxis,thorttleAxis,rollValue,pitchValue,yawValue,thorttleValue,_thurst,_thurst1,throt2;
    QObject *qmlObject;
    QQuickView *view;
    QJoysticks * joystickEvent;
    QVariant latitude,longitude,angle;
    int pingsequence;
    float yawPlot;
    int custom_mode, base_mode,intMissionResult;
    QVariant mission_result,declinedIndex;
    int modeIndex;
float yaw,roll,pitch;
};

#endif // MAVLINK_RAW_MESSAGE_H

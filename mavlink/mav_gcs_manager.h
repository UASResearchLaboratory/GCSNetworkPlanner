#ifndef MAV_GCS_MANAGER_H
#define MAV_GCS_MANAGER_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QVariant>
#include <QMutex>
#include <QDebug>
#include <QSerialPort>
#include "mavlink/c_library_v1-master/common/mavlink.h"


class QGimball : public QObject
{
    Q_OBJECT
public:
    QGimball(QObject * parent = 0);
    void    slot_MAVLINK_MSG_ID_HEARTBEAT(mavlink_message_t  message_2d);
    void    slot_MAVLINK_MSG_ID_COMMAND_ACK(mavlink_message_t  message_2d);

    void    dds_mavlink_decode(QByteArray array);

    void    heartbeat_slot();
    void    dds_mavlink_encode(mavlink_message_t message);

public slots:
    void read();
    void set_gimbal_yaw(int value);
    void set_gimbal_pitch(int value);
    void set_gimbal_roll(int value);

    void set_pwm_speed();
signals:
   void sendcommand(QByteArray);
   void dds_mavlink_encodeSignal(QByteArray);
private:

    mavlink_status_t lastStatus;
    uint8_t cp;
    mavlink_message_t message,message2;
    mavlink_status_t status;
    uint16_t msgReceived;
    QStringList list;
    QByteArray array0,array1,array2;
    QThread * thread;
    char **arguments;
    QList<mavlink_mission_item_t> list_mission_item;
    int target_system_id;
    int target_component_id;
    int system_id;
    int timer_id;
    QSerialPort serial;
    float yaw,roll,pitch;
};

#endif // MAV_GCS_MANAGER_H

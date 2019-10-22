
#include "mav_gcs_manager.h"
#include "QtMath"

QGimball::QGimball(QObject *parent) : QObject(parent)
{
//    target_system_id = -1;
//    target_component_id = -1;
//    system_id = 255;
//    timer_id = -1;
//    serial.setPortName("/dev/ttyUSB0");
//    serial.setBaudRate(115200);
//    qDebug() << serial.open(QIODevice::ReadWrite);
//    QObject::connect(&serial,SIGNAL(readyRead()),this,SLOT(read()));
    roll = 0;
    pitch = 0;
    yaw = 0;
    set_pwm_speed();

}

void QGimball::dds_mavlink_encode(mavlink_message_t message)
{
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buffer, &message);
//    if(serial.isOpen())
//        serial.write(QByteArray::fromRawData((const char*)buffer,len));
//    else {
//        qDebug() <<"cant write";
//    }

 dds_mavlink_encodeSignal(QByteArray::fromRawData((const char*)buffer,len));
}


void QGimball::dds_mavlink_decode(QByteArray array)
{
    for(int i=0;i<array.size();i++)
    {
        msgReceived = mavlink_parse_char(MAVLINK_COMM_3, (uint8_t)array.at(i), &message, &status);
        if (lastStatus.packet_rx_drop_count != status.packet_rx_drop_count)
        {
            // printf("ERROR: DROPPED %d PACKETS! \n", status.packet_rx_drop_count);
        }
        lastStatus = status;
        if(msgReceived)
        {

            switch (message.msgid)
            {

            case MAVLINK_MSG_ID_HEARTBEAT:
                slot_MAVLINK_MSG_ID_HEARTBEAT(message);
                break;
            case MAVLINK_MSG_ID_COMMAND_ACK:
                slot_MAVLINK_MSG_ID_COMMAND_ACK(message);
            default:
                qDebug() << "msgid" << message.msgid;
                break;
            }
        }
    }
}

void QGimball::heartbeat_slot()
{
    mavlink_message_t msg;
    mavlink_msg_heartbeat_pack(71,67,&msg,26,83,0,0,4);
    dds_mavlink_encode(msg);

}

void QGimball::slot_MAVLINK_MSG_ID_HEARTBEAT(mavlink_message_t message_2d)
{
    mavlink_heartbeat_t heartbeat;
    target_system_id = message_2d.sysid;
    target_component_id = message_2d.compid;
    mavlink_msg_heartbeat_decode(&message_2d, &heartbeat);
    switch (heartbeat.type)
    {
    case 0:     qDebug() << "GENERIC";           break;
    case 1:     qDebug() << "FIXED WING";        break;
    case 2:     qDebug() << "QUADROTOR";         break;
    case 3:     qDebug() << "COAXIAL";           break;
    case MAV_TYPE_HELICOPTER:       qDebug() << "HELICOPTER";        break;
    case MAV_TYPE_ANTENNA_TRACKER:  qDebug() << "ANTENNA_TRACKER";   break;
    case MAV_TYPE_GCS:              qDebug() << "GCS";               break;
    case MAV_TYPE_GIMBAL:           qDebug() << "MAV_TYPE_GIMBAL";               break;
    default:    qDebug() << "unknown";           break;
    }
    switch (heartbeat.system_status)
    {
    case 0:     qDebug() << "UNINITIALIZED";   break;
    case 1:     qDebug() << "BOOTING";         break;
    case 2:     qDebug() << "CALIBRATING";     break;
    case 3:     qDebug() << "STANDBY";         break;
    case 4:     qDebug() << "ACTIVE";          break;
    case 5:     qDebug() << "CRITICAL";        break;
    case 6:     qDebug() << "EMERGENCY";       break;
    default:    qDebug() << "POWEROFF";        break;
    }
}

void QGimball::slot_MAVLINK_MSG_ID_COMMAND_ACK(mavlink_message_t message_2d)
{
    mavlink_command_ack_t cmd_ack_t;
    mavlink_msg_command_ack_decode(&message_2d, &cmd_ack_t);

    switch (cmd_ack_t.command)
    {
    case MAV_CMD_DO_MOUNT_CONTROL:
        qDebug() << "MAV_CMD_ACK";
        break;
    default:
        qDebug() << "MAV_CMD_UNKNOWN";
        break;
    }
    switch (cmd_ack_t.result)
    {
    case MAV_RESULT_ACCEPTED:               qDebug() << "MAV_RESULT_ACCEPTED";   break;
    case MAV_RESULT_DENIED:                 qDebug() << "MAV_RESULT_DENIED";   break;
    case MAV_RESULT_ENUM_END:               qDebug() << "MAV_RESULT_ENUM_END";   break;
    case MAV_RESULT_FAILED:                 qDebug() << "MAV_RESULT_FAILED";   break;
    case MAV_RESULT_TEMPORARILY_REJECTED:   qDebug() << "MAV_RESULT_TEMPORARILY_REJECTED";   break;
    case MAV_RESULT_UNSUPPORTED:            qDebug() << "MAV_RESULT_UNSUPPORTED";   break;
    }
}

void QGimball::read()
{
    QByteArray array = serial.readAll();
    this->dds_mavlink_decode(array);
}

void QGimball::set_pwm_speed()
{


        mavlink_message_t message;
        mavlink_msg_command_long_pack(255,1,&message,71,67,MAV_CMD_DO_SET_SERVO,0,0,2200,0,0,0,0,0);
        dds_mavlink_encode(message);


}

void QGimball::set_gimbal_yaw(int value)
{
//    target_system_id = 71;
//    target_component_id = 67;
//    system_id = 255;
//    timer_id = -1;

        yaw =yaw+ ((float)value*180/1000);
        mavlink_message_t message;
        mavlink_msg_command_long_pack(255,1,&message,71,67,MAV_CMD_DO_MOUNT_CONTROL,0,pitch,roll,yaw,0,0,0,0);
        dds_mavlink_encode(message);
       qDebug()<<"yaw sent";




}
void QGimball::set_gimbal_pitch(int value)
{

        pitch = pitch+ ((float)value*90/1000);

        mavlink_message_t message;
        mavlink_msg_command_long_pack(255,1,&message,71,67,MAV_CMD_DO_MOUNT_CONTROL,0,pitch,roll,yaw,0,0,0,0);
        dds_mavlink_encode(message);
        qDebug()<<"clicked gimbal";

}
void QGimball::set_gimbal_roll(int value)
{

        roll = roll+(float)value*60;
        qDebug() << roll;
        mavlink_message_t message;
        mavlink_msg_command_long_pack(255,1,&message,71,67,MAV_CMD_DO_MOUNT_CONTROL,0,pitch,roll,yaw,0,0,0,0);
        dds_mavlink_encode(message);
qDebug()<<"roll sent";

}

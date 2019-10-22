#include "mavlink_raw_message.h"
#include "QtMath"
#include "qtsdljoystick.h"
#include <QDateTime>




Mavlink_Raw_Message::Mavlink_Raw_Message(QObject *parent) : QObject(parent)
{

    sdljoy= new QtSDLJoystick();
    latitude=0;
    longitude=0;
    angle = 0;
    _roll=0;
    _pitch=0;
    _yaw=0;
    _throttle=0;
    axisvalue=0;
    rollAxis=0;
    pitchAxis=0;
    yawAxis=0;
    thorttleAxis=0;
    seq,seq2,seq1=0;
    pingsequence=0;
    rollValue,pitchValue,yawValue,thorttleValue=0;
    _thurst,_thurst1,_throttle1=0;

    timer= new QTimer(this);
    //connect(sdljoy,&QtSDLJoystick::manualCommandsSignal,this,&Mavlink_Raw_Message::ch3_joystick);
    connect(timer, SIGNAL(timeout()), this, SLOT(mavlink_joystick()));
    //   connect(timer, SIGNAL(timeout()), this, SLOT(send_ping()));

    connect(timer, SIGNAL(timeout()), this, SLOT(setIndexModeResult()));

    timer->start(41);
    yaw=0;roll=0;pitch=0;

}


void Mavlink_Raw_Message::get_axis_combobx(QVariant combobox)
{

    qDebug()<<"combobox"<< combobox;


}

void Mavlink_Raw_Message::get_QML_test(QVariant latitude)
{
    qDebug()<<latitude.toList() << "hello lat";

}
void Mavlink_Raw_Message::get_QML_test_long(QVariant longitude)
{
    qDebug()<<longitude.toList() << "hello long";

}

void Mavlink_Raw_Message::send_ping()
{
    mavlink_ping_t ping;

    ping.target_component=1;
    ping.target_system=1;
    ping.seq=pingsequence++;
    mavlink_msg_ping_encode(1,0,&pingmessage,&ping);
    dds_mavlink_encode(pingmessage);

}

void Mavlink_Raw_Message::get_ping(mavlink_message_t message_n)
{
    //    mavlink_ping_t ping2;
    //    mavlink_msg_ping_decode(&message_n,&ping2);
    //   // qDebug()<<"ping"<< ping2.time_usec;
    seq2=mavlink_msg_ping_get_time_usec(&message_n);
    //seq=seq2-seq;
    //seq=seq-10e6;
    //qDebug()<< "ping"<< seq2;




}


void Mavlink_Raw_Message::set_message_interval(float message, float interval)
{

    mavlink_message_t message_2d;
    mavlink_command_long_t change_rate_command;
    change_rate_command.target_system =1;
    change_rate_command.target_component = 1;
    change_rate_command.command          = MAV_CMD_SET_MESSAGE_INTERVAL;
    change_rate_command.confirmation     =  0;
    change_rate_command.param1            =  message;

    change_rate_command.param2            = interval; // microseconds
    change_rate_command.param3            =  interval; // microseconds
    mavlink_msg_command_long_encode(1,0, &message_2d, &change_rate_command);
    dds_mavlink_encode(message_2d);
    qDebug()<<"clicked confirmation";

}
void Mavlink_Raw_Message::decode_command_long(mavlink_message_t message)
{
    mavlink_command_ack_t cmd_ack_t;
    mavlink_msg_command_ack_decode(&message, &cmd_ack_t);

    switch (cmd_ack_t.command)
    {
    case MAV_CMD_DO_MOUNT_CONTROL:
        //  qDebug() << "MAV_CMD_ACK";
        break;
    case MAV_CMD_DO_SET_MODE:
        if (base_mode==81 && custom_mode==196608)

        {
            qDebug() << "SET MODE: POSITION ";
        }

        break;
    default:
        // qDebug() << "MAV_CMD_UNKNOWN. Number of the command: "<< cmd_ack_t.command;
        break;
    }
    emit sendMissionSetResult(QVariant((cmd_ack_t.result)));
    intMissionResult=cmd_ack_t.result;
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

void Mavlink_Raw_Message::parameter_shrinker()
{
    QList<int> data;
    data.insert(1,MAVLINK_MSG_ID_ATTITUDE_QUATERNION);
    data.insert(2,MAVLINK_MSG_ID_LOCAL_POSITION_NED);
    data.insert(3,MAVLINK_MSG_ID_SERVO_OUTPUT_RAW);
    data.insert(4,MAVLINK_MSG_ID_ESTIMATOR_STATUS);
    data.insert(5,MAVLINK_MSG_ID_WIND_COV);
    data.insert(6,MAVLINK_MSG_ID_ACTUATOR_CONTROL_TARGET);
    data.insert(7,MAVLINK_MSG_ID_HIGHRES_IMU);
    data.insert(8,MAVLINK_MSG_ID_VIBRATION);
    data.insert(9,MAVLINK_MSG_ID_VFR_HUD);
    // data.insert(5,MAVLINK_MSG_ID_WIND_COV);


    for (int i=0;i<data.size();i++)
    {
        set_message_interval(data.at(i),4100000.0);
    }

}

void Mavlink_Raw_Message::handleSpeech(QByteArray data)
{
    qDebug ()<< "spoken data" << data;
    if ( data=="TAKEOFF\n")
    {
        arm();
    }
    if ( data=="LAND\n"|| data=="DOWN\n")
    {
        disarm();
    }
}

void Mavlink_Raw_Message::decodeSpeech()
{
    // handleSpeech(speech->Recognize());

}



void Mavlink_Raw_Message::set_stabilized_mode()
{
    mavlink_message_t message_2d;
    mavlink_command_long_t change_rate_command;
    change_rate_command.target_system = 1;
    change_rate_command.target_component = 1;
    change_rate_command.command          = MAV_CMD_DO_SET_MODE;
    change_rate_command.confirmation     =  0;
    change_rate_command.param1            =  MAV_MODE_STABILIZE_DISARMED;
    //    change_rate_command.param2            =  410000.0; // microseconds
    //    change_rate_command.param3            =  410000.0; // microseconds
    mavlink_message_t ratio_changer_msg3;
    mavlink_msg_command_long_encode(1,0, &message_2d, &change_rate_command);
    dds_mavlink_encode(message_2d);
    // qDebug()<<"clicked confirmation";
}


void Mavlink_Raw_Message::get_joystick_protocol_qml(int index)
{
    if (index == 0)   qDebug()<<"MavLink";
    if (index == 1)   qDebug()<<"DJI";

}



void Mavlink_Raw_Message::get_axis_qml(double currentAxis,double currentParameter)
{

    if (currentParameter == 0)   qDebug()<<"none";
    if (currentParameter == 1)  {qDebug()<<"roll axis  "<<currentAxis;rollAxis=currentAxis;}
    if (currentParameter == 2)  {qDebug()<<"pitch axis  "<<currentAxis;pitchAxis=currentAxis;}
    if (currentParameter == 3)  {qDebug()<<"yaw axis  "<<currentAxis;yawAxis=currentAxis;}
    if (currentParameter == 4)  {qDebug()<<"thorttle axis  "<<currentAxis;thorttleAxis=currentAxis;}

}


void Mavlink_Raw_Message::get_axis_value_qml(double currentAxis,double currentValue)
{

    if(currentAxis==rollAxis)
    {
        qDebug()<<"roll axis"<< rollAxis<< "value"<<currentValue;
        rollValue=currentValue;
        qDebug()<<"roll value"<<rollValue;
    }
    if(currentAxis==pitchAxis)
    {
        //qDebug()<<"pitch axis"<< pitchAxis<< "value"<<currentValue;
        pitchValue=currentValue;
        //qDebug()<<"pitch value"<<pitchValue;
    }
    if(currentAxis==yawAxis)
    {
        // qDebug()<<"yaw axis"<< yawAxis<< "value"<<currentValue;
        yawValue=currentValue;
        //qDebug()<<"yaw value"<<yawValue;
    }
    if(currentAxis==thorttleAxis)
    {
        //qDebug()<<"thorttle axis"<< thorttleAxis<< "value"<<currentValue;
        thorttleValue=currentValue;
        // qDebug()<<"thorttle value"<<thorttleValue;
    }
    emit qmljoystickcontrols(rollValue,pitchValue,yawValue,thorttleValue);
}

QStringList Mavlink_Raw_Message::deviceNames() const
{
    QStringList names;

    names <<"none" <<"roll" << "Pitch" << "Yaw" << "Thorttle";

    return names;
}


void Mavlink_Raw_Message::dds_mavlink_encode(mavlink_message_t message)
{

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buffer, &message);
    emit dds_mavlink_encodeSignal(QByteArray::fromRawData((const char*)buffer,len));

}


void Mavlink_Raw_Message::dds_mavlink_decode(QByteArray array)
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
                heartbeat_values(message);

                break;
            case MAVLINK_MSG_ID_SYS_STATUS:
                sys_values(message);

                break;
            case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
                gps_int_values(message);

                break;
            case MAVLINK_MSG_ID_HIGHRES_IMU:
                imu_scaled_values(message);

                break;
                //                case MAVLINK_MSG_ID_PING:
                //                   // get_ping(message);


                //                break;

            case MAVLINK_MSG_ID_ATTITUDE:
                attitude_values(message);
                //seq=mavlink_msg_ping_get_time_usec(&message);


                break;
                //                case MAVLINK_MSG_ID_ACTUATOR_CONTROL_TARGET:

                //                break;
                //                case MAVLINK_MSG_ID_ADSB_VEHICLE:
                //                break;
            case MAVLINK_MSG_ID_GPS_RAW_INT:
                gps_raw_values(message);
                break;
            case MAVLINK_MSG_ID_COMMAND_ACK:
                decode_command_long(message);

                break;
            case MAVLINK_MSG_ID_ALTITUDE:
                altitude_values(message);
                break;

            default:
                //qDebug()<<message.msgid;
                //   qDebug()<<"base Mode: "<< mavlink_msg_set_mode_get_base_mode(&message);
                break;


            }
        }
    }
}

void Mavlink_Raw_Message::test_joystick(int js,int axis,qreal value)
{

    //   qDebug()<<"js"<<js<<"axis"<<axis<<"value"<<value;
    if (value!=0)
    {
        // qDebug()<<"axis number !"<< axis;

    }

}


void Mavlink_Raw_Message::clearWP()
{
    mavlink_message_t message;
    mavlink_mission_clear_all_t clear;
    clear.target_component=MAV_COMP_ID_MISSIONPLANNER;
    clear.target_system=1;
    clear.mission_type=MAV_MISSION_TYPE_MISSION;
    mavlink_msg_mission_clear_all_encode(1,0,&message,&clear);
}

void Mavlink_Raw_Message::countWP(int count)
{
    mavlink_message_t message;
    mavlink_mission_count_t count_msg;
    count_msg.target_component=MAV_COMP_ID_MISSIONPLANNER;
    count_msg.target_system=1;
    count_msg.mission_type=MAV_MISSION_TYPE_MISSION;
    count_msg.count=count;
    mavlink_msg_mission_count_encode(1,0,&message,&count_msg);
    dds_mavlink_encode(message);
}






void Mavlink_Raw_Message::arm()
{


    mavlink_message_t message_2d;
    mavlink_command_long_t arm_command_msg;
    arm_command_msg.command = MAV_CMD_COMPONENT_ARM_DISARM;
    arm_command_msg.target_system = 1;
    arm_command_msg.target_component = 1;
    arm_command_msg.confirmation = 0;
    arm_command_msg.param1 = 1;
    mavlink_msg_command_long_encode(1, 0, &message_2d, &arm_command_msg);
    dds_mavlink_encode(message_2d);
    qDebug()<<"clicked arm";
      parameter_shrinker();
    //  setMode(81,458752);

}




void Mavlink_Raw_Message::disarm()
{
    mavlink_message_t message_2d;

    mavlink_command_long_t arm_command_msg;
    arm_command_msg.command = MAV_CMD_COMPONENT_ARM_DISARM;
    arm_command_msg.target_system = 1;
    arm_command_msg.target_component = 1;
    arm_command_msg.confirmation = 0;
    arm_command_msg.param1 = 0;
    mavlink_msg_command_long_encode(1, 0, &message_2d, &arm_command_msg);
    dds_mavlink_encode(message_2d);

}
void Mavlink_Raw_Message::takeoff()
{
    mavlink_message_t message_2d;

    mavlink_command_long_t arm_command_msg;
    arm_command_msg.command = MAV_CMD_NAV_TAKEOFF;
    arm_command_msg.target_system = 1;
    arm_command_msg.target_component = 1;
    arm_command_msg.param1 = 0;
    arm_command_msg.param4 = 2;
    arm_command_msg.param7=30;
    mavlink_msg_command_long_encode(1, 0, &message_2d, &arm_command_msg);
    dds_mavlink_encode(message_2d);

}

void Mavlink_Raw_Message::returntolaunch()
{
    mavlink_message_t message_2d;

    mavlink_command_long_t arm_command_msg;
    arm_command_msg.command = MAV_CMD_NAV_RETURN_TO_LAUNCH;
    arm_command_msg.target_system = 1;
    arm_command_msg.target_component = 1;
    arm_command_msg.confirmation = 0;
    mavlink_msg_command_long_encode(1, 0, &message_2d, &arm_command_msg);
    dds_mavlink_encode(message_2d);


}

void Mavlink_Raw_Message::setMode(int baseMode, int customMode)
{
    //    baseMode=81;
    //    customMode=196608; // Position mode
    //  mode base:  81 mode custom:  65536 manual flight mode
    // mode base:  81 mode custom:  458752 stabilized
    //mode base:  81 mode custom:  327680 accro
    //mode base:  65 mode custom:  524288 ratitude
    //  mode base:  65 mode custom:  131072 altitude flight mode
    // 81 196608 position mode
    // mode base:  81 mode custom:  393216 offboard mode
    //mode base:  81 mode custom:  50593792 hold mode
    //mode base:  81 mode custom:  67371008 mission mode
    // mode base:  81 mode custom:  84148224 return mode
    //mode base:  81 mode custom:  134479872 follow me

    mavlink_message_t message_2d;
    mavlink_set_mode_t set;
    set.target_system=1;
    set.base_mode=baseMode;
    set.custom_mode=customMode;
    mavlink_msg_set_mode_encode(1,0,&message_2d,&set);
    dds_mavlink_encode(message_2d);
    // mavlink_msg_command_long_pack(255,1,&message_2d,71,67,MAV_CMD_DO_MOUNT_CONTROL,0,200,100,100,0,0,0,0);

    qDebug()<<"mode set";


}


void Mavlink_Raw_Message::setIndexMode(int index)
{
    mavlink_message_t message_2d;
    mavlink_set_mode_t set;
    set.target_system=1;
    switch (index)
    {
    //    baseMode=81;
    //    customMode=196608; // Position mode
    //  mode base:  81 mode custom:  65536 manual flight mode
    // mode base:  81 mode custom:  458752 stabilized
    //mode base:  81 mode custom:  327680 accro
    //mode base:  65 mode custom:  524288 ratitude
    //  mode base:  65 mode custom:  131072 altitude flight mode
    // 81 196608 position mode
    // mode base:  81 mode custom:  393216 offboard mode
    //mode base:  81 mode custom:  50593792 hold mode
    //mode base:  81 mode custom:  67371008 mission mode
    // mode base:  81 mode custom:  84148224 return mode
    //mode base:  81 mode custom:  134479872 follow me
    case 0:
        set.base_mode=81;
        set.custom_mode=65536;
        break;

    case 1:
        set.base_mode=81;
        set.custom_mode=458752;
        break;
    case 2:
        set.base_mode=81;
        set.custom_mode=327680;
        break;
    case 3:
        set.base_mode=65;
        set.custom_mode=524288;
        break;
    case 4:
        set.base_mode=65;
        set.custom_mode=131072;
        break;
    case 5:
        set.base_mode=81;
        set.custom_mode=196608;
        break;
    case 6:
        set.base_mode=81;
        set.custom_mode=393216;
        break;
    case 7:
        set.base_mode=81;
        set.custom_mode=50593792;
        break;
    case 8:
        set.base_mode=81;
        set.custom_mode=67371008;
        break;
    case 9:
        set.base_mode=81;
        set.custom_mode=84148224;
        break;
    case 10:
        set.base_mode=81;
        set.custom_mode=134479872;
        break;
    default:

        break;


    }
    mavlink_msg_set_mode_encode(1,0,&message_2d,&set);
    dds_mavlink_encode(message_2d);
    qDebug()<<"mode set";
    modeIndex=index;
}

void Mavlink_Raw_Message::setIndexModeResult()
{
    switch (intMissionResult)
    {
    case 0:
        indexModeAccepted(QVariant(modeIndex));
        declinedIndex=QVariant(modeIndex);
        break;

    default:
        indexModeAccepted(declinedIndex);
        break;
    }

}

void Mavlink_Raw_Message::ch3_joystick(int roll, int pitch, int yaw, int throttle)
{
    _thurst1=_thurst;
    _roll=roll;
    _pitch=pitch;
    _yaw=yaw;
    _thurst=throttle;
    //_throttle=_thurst;
    // qDebug()<<-_thurst1 <<" : : "<<-_thurst;

    if (throttle<=0)
    {
        if (_thurst>_thurst1)
        {

            (_thurst)= (_thurst1);
            _throttle1=(_thurst1);
            if (_throttle1<_throttle)
            {
                _throttle1=_throttle1*0.002;
                _throttle=(_throttle+_throttle1);

            }
        }
    }
    else  if (throttle>0)
    {
        if (_thurst<_thurst1)
        {
            _thurst= (_thurst1);
            _throttle1=_thurst1;
            if (_throttle1>_throttle)
            {
                _throttle1=_throttle1*0.002;
                _throttle=(_throttle+_throttle1);

            }
        }
    }
    while (_throttle<-1000)
    {
        _throttle=-1000;
    }
    while (_throttle>0)
    {
        _throttle=0;
    }
}

void Mavlink_Raw_Message::mavlink_joystick()
{
    mavlink_message_t message_2d;
    mavlink_manual_control_t manual;///Msg to override rc channels
    //_throttle=_throttle+_thurst;

    manual.r=_yaw;
    manual.x=_pitch;
    manual.y=_roll;
    manual.z=-_throttle;
    manual.target= 1; // Send command to MAV 001
    mavlink_msg_manual_control_encode(1, 0, &message_2d, &manual);
    dds_mavlink_encode(message_2d);
    mavlink_msg_manual_control_decode(&message_2d, &manual);
    //    qDebug()<<"throttle real value" <<manual.z;
    //    qDebug()<<"y real value" <<manual.y;
    //    qDebug()<<"x real value" <<manual.x;
    //    qDebug()<<"r real value" <<manual.r;

}


void Mavlink_Raw_Message::ch3_high()
{

    mavlink_message_t message_2d;
    mavlink_rc_channels_override_t rc_override;///Msg to override rc channels
    rc_override.chan1_raw=1100;
    rc_override.chan2_raw=1100;
    rc_override.chan3_raw=1600;//Lowest throttle
    rc_override.chan4_raw=1100;
    rc_override.chan5_raw=1100;
    rc_override.chan6_raw=1100;
    rc_override.chan7_raw=1100;
    rc_override.chan8_raw=1100;
    rc_override.target_system = 1; // Send command to MAV 001
    rc_override.target_component = 1;//PX_COMP_ID_ALL;
    mavlink_msg_rc_channels_override_encode(1, 0, &message_2d, &rc_override);

    dds_mavlink_encode(message_2d);


}

void Mavlink_Raw_Message::ch3_low()
{

    mavlink_message_t message_2d;
    mavlink_rc_channels_override_t rc_override;///Msg to override rc channels
    rc_override.chan1_raw=900;
    rc_override.chan2_raw=900;
    rc_override.chan3_raw=900;//Lowest throttle
    rc_override.chan4_raw=900;
    rc_override.chan5_raw=900;
    rc_override.chan6_raw=900;
    rc_override.chan7_raw=900;
    rc_override.chan8_raw=900;
    rc_override.target_system = 1; // Send command to MAV 001
    rc_override.target_component = 1;//PX_COMP_ID_ALL;
    mavlink_msg_rc_channels_override_encode(1, 0, &message_2d, &rc_override);
    dds_mavlink_encode(message_2d);

}

void Mavlink_Raw_Message::heartbeat_slot()

{
    mavlink_message_t msg;

    mavlink_msg_heartbeat_pack(2,1,&msg,6,0,1,1,1);
    dds_mavlink_encode(msg);

    //qDebug()<<"hello world";

}


void Mavlink_Raw_Message::heartbeat_values(mavlink_message_t message_2d)
{
    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&message_2d, &heartbeat);
    // qDebug() << heartbeat.system_status;
    switch (heartbeat.type)

    {
    case 0:     emit uav_type("GENERIC");           break;
    case 1:     emit uav_type("FIXED WING");        break;
    case 2:     emit uav_type("QUADROTOR");         break;
    case 3:     emit uav_type("COAXIAL");           break;
    case 4:     emit uav_type("HELICOPTER");        break;
    case 5:     emit uav_type("ANTENNA_TRACKER");   break;
    case 6:     emit uav_type("GCS");               break;
    default:    emit uav_type("unknown");           break;
    }
    switch (heartbeat.system_status)
    {
    case 0:     emit sys_status("UNINITIALIZED");   break;
    case 1:     emit sys_status("BOOTING");         break;
    case 2:     emit sys_status("CALIBRATING");     break;
    case 3:     emit sys_status("STANDBY");         break;
    case 4:     emit sys_status("ACTIVE");          break;
    case 5:     emit sys_status("CRITICAL");        break;
    case 6:     emit sys_status("EMERGENCY");       break;
    default:    emit sys_status("POWEROFF");        break;
    }
}
void Mavlink_Raw_Message::sys_values(mavlink_message_t message_2d)
{
    mavlink_sys_status_t sys_status;
    mavlink_msg_sys_status_decode(&message_2d, &sys_status);
    //GUI_Signals
    //   emit guibatterypercentage(QString::setNum(sys_status.battery_remaining));
    //RAW_Signals
    emit battery_voltage(sys_status.voltage_battery/10.0e3);
    emit batterypercentage(sys_status.battery_remaining);
    emit battery_current(sys_status.current_battery*10.0);
    emit sys_packets_dropped_rate(sys_status.drop_rate_comm);
    //QML Signals
    emit qmlBatteryInfoSignal(QVariant(sys_status.voltage_battery/10.0e3),QVariant(sys_status.battery_remaining),QVariant(sys_status.current_battery*10.0));

}

void Mavlink_Raw_Message::gps_int_values(mavlink_message_t message_2d)
{

    mavlink_global_position_int_t packet;
    mavlink_msg_global_position_int_decode(&message_2d, &packet);
    QString raw_msg ;
    //GUI_signals
    emit guigpslatitudeint(raw_msg.setNum(packet.lat/10.0e6,'g',12));
    emit guigpslongtitudeint(raw_msg.setNum(packet.lon/10.0e6,'g',12));
    emit guigpsaltitudeint(raw_msg.setNum(packet.alt/10.0e3,'g',6));
    //RAW_signals
    emit gpslatitudeint(packet.lat/10.0e6);
    emit gpslongtitudeint(packet.lon/10.0e6);
    emit gpslatitudeint(packet.alt/10.0e3);
}

void Mavlink_Raw_Message::gps_raw_values(mavlink_message_t message_2d)
{  QString raw_msg ;


    mavlink_gps_raw_int_t packet;
    mavlink_msg_gps_raw_int_decode(&message_2d, &packet);

    //GUI_signals
    emit guigpslatituderaw(raw_msg.setNum(packet.lat/10.0e6,'g',12));
    emit guigpslongtituderaw(raw_msg.setNum(packet.lon/10.0e6,'g',12));
    emit guigpsaltituderaw(raw_msg.setNum(packet.alt/10.0e3,'g',6));

    //RAW_signals
    emit gpslatituderaw(packet.lat/10.0e6);
    emit gpslongtituderaw(packet.lon/10.0e6);
    emit gpslatituderaw(packet.alt/10.0e3);
    //QVariant
    latitude = QVariant((packet.lat/10.0e6));
    longitude = QVariant((packet.lon/10.0e6));
    emit signalCoordinate(latitude,longitude);
    // qDebug()<<latitude << "   lat 2";


}


void Mavlink_Raw_Message::attitude_values(mavlink_message_t message_2d)
{

    mavlink_attitude_t attitude;
    mavlink_msg_attitude_decode(&message_2d, &attitude);
    QString raw_msg ;
    QVariant angle,angle2PI;
    angle=QVariant(attitude.yaw);
    angle2PI=QVariant(attitude.yaw+2*M_PI);


    emit guiattitudepitch(raw_msg.setNum((attitude.pitch)));
    if (attitude.yaw <0)

    {

        emit guiattitudeyaw(raw_msg.setNum((attitude.yaw)+ 2*M_PI));
        emit angleCoordinate(angle2PI);

        emit attitudegauges((attitude.yaw)+2*M_PI,attitude.pitch);

        emit attitudeyaw((attitude.yaw)+2*M_PI);
        emit attitudedoubleyaw((double)((attitude.yaw)+2*M_PI));

        yawPlot=((attitude.yaw)+2*M_PI);
        emit qmlYawPitchRollSignal(raw_msg.setNum((attitude.yaw)+ 2*M_PI),raw_msg.setNum((attitude.pitch)),raw_msg.setNum((attitude.roll)));

    }
    else
    {
        emit guiattitudeyaw(raw_msg.setNum((attitude.yaw)));

        emit attitudegauges((attitude.yaw),attitude.pitch);

        emit angleCoordinate(angle);
        emit attitudeyaw((attitude.yaw));
        yawPlot=(attitude.yaw);
        emit attitudeyaw((double)(attitude.yaw));
        //qDebug()<<attitude.yaw<< "yaw";
        emit qmlYawPitchRollSignal(raw_msg.setNum((attitude.yaw)),raw_msg.setNum((attitude.pitch)),raw_msg.setNum((attitude.roll)));

    }

    emit guiattituderoll(raw_msg.setNum((attitude.roll)));


    // qDebug()<<  qRadiansToDegrees(attitude.roll);



    emit attitudepitch((attitude.pitch));
    emit attituderoll((attitude.roll));
    QList <float> parIndex;
    parIndex.insert(1,attitude.pitch);parIndex.insert(2,yawPlot);parIndex.insert(3,attitude.roll);
    emit plotParameters(parIndex);



    //printf("actuator control %lu %lu\n",packet_in.altitude ,packet_in.group_mlx );
    // qDebug() <<"gps coordinates" <<gps_raw.lat<<"longtitude"<<gps_raw.lon <<"altitudegps"<<gps_raw.alt<<"visible Sat"<< gps_raw.satellites_visible <<"hdop"<< gps_raw.eph<<"vdop"<< gps_raw.epv ;
    // printf("altitudesea %f %f\n",altitude.bottom_clearance ,altitude.altitude_amsl );
    //printf("altitudesea %f %f\n",altitude.bottom_clearance ,altitude.altitude_amsl );
    //            gps_lat_raw.setNum((double)gps_raw.lat/10e6, 'g', 10);
    //            emit gpslatituderaw(gps_lat_raw);
    //            gps_long_raw.setNum((double)gps_raw.lon/10e6, 'g', 10);
    //            emit gpslongtituderaw(gps_long_raw);
    //            gps_alt_raw.setNum((float)gps_raw.alt);
    //            emit gpsaltituderaw(gps_alt_raw);


}

void Mavlink_Raw_Message::altitude_values(mavlink_message_t message_2d)
{  QString raw_msg ;

}

void Mavlink_Raw_Message::imu_scaled_values(mavlink_message_t message_2d)
{
    mavlink_highres_imu_t imu;
    mavlink_msg_highres_imu_decode(&message_2d, &imu);
    QString raw_msg ;
    //GUI_Signals
    emit guiimuxacc(raw_msg.setNum(imu.xacc/10.0e6,'g',9));
    // qDebug()<<"checking mySig";
    emit guiimuyacc(raw_msg.setNum(imu.yacc/10.0e6,'g',9));
    emit guiimuzacc(raw_msg.setNum(imu.zacc/10.0e6,'g',9));

    emit guiimuxgyro(raw_msg.setNum(imu.xgyro/10.0e6,'g',9));
    emit guiimuygyro(raw_msg.setNum(imu.ygyro/10.0e6,'g',9));
    emit guiimuzgyro(raw_msg.setNum(imu.zgyro/10.0e6,'g',9));

    emit guiimuxmag(raw_msg.setNum(imu.xmag/10.0e6,'g',9));
    emit guiimuymag(raw_msg.setNum(imu.ymag/10.0e6,'g',9));
    emit guiimuzmag(raw_msg.setNum(imu.zmag/10.0e6,'g',9));
    //RAW_Signals
    emit imuxacc(imu.xacc/10.0e6);
    emit imuyacc(imu.yacc/10.0e6);
    emit imuzacc(imu.zacc/10.0e6);

    emit imuxgyro(imu.xgyro/10.0e6);
    emit imuygyro(imu.ygyro/10.0e6);
    emit imuzgyro(imu.zgyro/10.0e6);

    emit imuxmag(imu.xmag/10.0e6);
    emit imuymag(imu.ymag/10.0e6);
    emit imuzmag(imu.zmag/10.0e6);


}


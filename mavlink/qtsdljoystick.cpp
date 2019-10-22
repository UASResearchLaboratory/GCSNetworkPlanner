
#include "qtsdljoystick.h"




QtSDLJoystick::QtSDLJoystick()
{
    timer = new QTimer();

    flag_start_stop = 1;
    SDL_Init(SDL_INIT_JOYSTICK);
    this->start();
    //connect(timer,SIGNAL(timeout()),this,SLOT(run()));
    //timer->start(40);
}

//void QtSDLJoystick::run()
//{

//        int roll,yaw,pitch,throttle=0;
//      SDL_Event event;
//          while((SDL_WaitEvent(&event)) && flag_start_stop )
//          {
//            switch(event.type)
//            {
//                case SDL_JOYDEVICEADDED:
//                {
//                    SDL_Joystick * joy = SDL_JoystickOpen(event.jdevice.which);
//                    if(joy==0) qDebug() << "ERROR, could not open the joystick. idx = " << event.jdevice.which;
//                    else joy_list.append(joy);
//                    QString str_name_joy = "Joystick Number ";
//                    if(SDL_JoystickName(joy)==NULL) str_name_joy= str_name_joy + event.jdevice.which;
//                    else str_name_joy = SDL_JoystickName(joy);
//                    stringJoyList.append(str_name_joy);
//                    emit signalJoystickList(stringJoyList);
//                   // qDebug() << str_name_joy;
//                    //qDebug() <<"axes"<< SDL_JoystickNumAxes(joy); ;

//                    break;
//                }
//                case SDL_JOYDEVICEREMOVED:
//                {
//                    qDebug() << "Joystick removed. " << joy_list.size();
//                    for(int i=0;i<joy_list.size();i++)
//                    {
//                        qDebug() << SDL_JoystickInstanceID(joy_list.at(i)) << " " << event.jdevice.which;
//                        if(SDL_JoystickInstanceID(joy_list.at(i))==event.jdevice.which)
//                        {
//                            SDL_JoystickClose(joy_list.at(i));
//                            joy_list.removeAt(i);
//                            stringJoyList.removeAt(i);
//                            emit signalJoystickList(stringJoyList);
//                            break;
//                        }
//                    }
//                    break;
//                }



//                                case SDL_JOYAXISMOTION:
//                                {

//                                    switch(event.jaxis.axis)
//                                    {
//                                        case 0 :


//                                         yaw=axisScaling(event.jaxis.value,0);
//                                            emit signalRoll(axisScaling(event.jaxis.value,0));
//                                         // qDebug() << "SDL_axis0"<<axisScaling(event.jaxis.value,0);
//                                        break;
//                                        case 1 :

//                                             throttle=axisScaling(event.jaxis.value,1);
//                                            emit signalThrottle(axisScaling(event.jaxis.value,1) );
//                                       qDebug() << "SDL_axis1"<<axisScaling(event.jaxis.value,1);
//                                        break;
//                                        case 2 :

//                                            pitch=axisScaling(event.jaxis.value,0);
//                                            emit signalPitch(axisScaling(event.jaxis.value,0));
//                                     // qDebug() << "SDL_axis2"<<axisScaling(event.jaxis.value,0);
//                                        break;
//                                        case 3 :
//                                            emit signalYaw(event.jaxis.value);
//                                       qDebug() << "SDL_axis3"<<axisScaling(event.jaxis.value,0);
//                                        break;
//                                    case 4 :
//                                       // emit signalYaw(event.jaxis.value);
//                                 // qDebug() << "SDL_axis4"<<axisScaling(event.jaxis.value,0);
//                                    break;
//                                    case 5 :
//                                            roll=axisScaling(event.jaxis.value,0);
//                                       // emit signalYaw(event.jaxis.value);
//                                  //qDebug() << "SDL_axis5"<<axisScaling(event.jaxis.value,0);

//                                            //qDebug() << "yaw"<<yaw;
//                                    break;

//                                        default:
//                                        break;

//                                    }
//                                     //qDebug() << "yaw"<<yaw;
//                                     emit manualCommandsSignal(roll,pitch,yaw,throttle);
//                                    //msleep(25);

//                                    break;
//                                }






//                case SDL_JOYBALLMOTION:
//                {
//                    qDebug() << "SDL_JOYBALLMOTION";
//                    qDebug() << event.jball.which;
//                    qDebug() << event.jball.ball;
//                    break;
//                }
//                case SDL_JOYBUTTONDOWN:
//                {

//                    qDebug() << "SDL_JOYBUTTONDOWN";
//                    qDebug() << event.button.which-256;
//                    qDebug() << event.button.button;
//                    qDebug() << event.button.state;
//                    qDebug() << event.button.timestamp;

//                    break;
//                }
//                case SDL_JOYBUTTONUP:
//                {
//                    switch(event.button.which)
//                    {
//                        case 0:
//                            emit signalExcuteTask();
//                        qDebug() << "signalExuteTask";
//                        break;

//                        case 1:
//                            emit signalMode1();
//                        break;
//                        case 2:
//                            emit signalMode2();
//                        break;
//                        case 4:
//                            emit signalMode3();
//                        break;

//                        case 3:
//                            emit signalGear1();
//                        break;
//                        case 5:
//                            emit signalGear2();
//                        break;

//                        default:
//                        break;
//                    }

//                    break;
//                }


//                case SDL_JOYHATMOTION:
//                {
//                    switch(event.jhat.value)
//                    {
//                        case SDL_HAT_LEFTUP:

//                        break;
//                        case SDL_HAT_UP:
//                        emit signalTakeOff();
//                          qDebug() << "SDL_HAT_UP";
//                        break;
//                        case SDL_HAT_RIGHTUP:
//                          qDebug() << "SDL_HAT_RU";
//                        break;
//                        case SDL_HAT_LEFT:
//                        emit signalGoHome();
//                        qDebug() << "SDL_HAT_LEFT";
//                        break;
//                        case SDL_HAT_CENTERED:
//                        break;
//                        case SDL_HAT_RIGHT:
//                          qDebug() << "SDL_HAT_Right";
//                        break;
//                        case SDL_HAT_LEFTDOWN:
//                        break;
//                        case SDL_HAT_DOWN:
//                        emit signalLanding();
//                          qDebug() << "SDL_HAT_Down";
//                        break;
//                        case SDL_HAT_RIGHTDOWN:
//                        break;
//                        default:
//                        break;
//                    }
//                    break;
//                }
//                default:
//                break;

//            }
//          }


//}
void QtSDLJoystick::slotStop(bool bl)
{
}

int QtSDLJoystick::axisScaling(int event_value, bool sign)
{
    return (int)((((((float)(event_value*pow(-1,sign)))+32768)/65536)*2000)-1000);
}

int QtSDLJoystick::axisScalingThrottle(int event_value, bool sign)
{
    return (int)((((((float)(event_value*pow(-1,sign)))+32768)/65536)*4000)-3000);
}
//int QtSDLJoystick::axisScaling(int event_value, bool sign)
//{
//    return (int)((((((float)(event_value*pow(-1,sign)))+32768)/65536)*1320)+364);
//}

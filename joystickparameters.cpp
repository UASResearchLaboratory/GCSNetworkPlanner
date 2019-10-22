#include "joystickparameters.h"
#include"QDebug"

JoystickParameters::JoystickParameters(QObject *parent) : QObject(parent)
{

    axisvalue=0;
     rollAxis=0;
     pitchAxis=0;
     yawAxis=0;
     thorttleAxis=0;
     rollValue,pitchValue,yawValue,thorttleValue=0;
     connect(this,SIGNAL(qmljoystickcontrols(int,int,int,int)),SIGNAL(qmlMavLinkjoystickcontrols(int,int,int,int)));
}




void JoystickParameters::get_axis_qml(double currentAxis,double currentParameter)
{
    //roll=roll.toDouble();

//    qDebug()<<"axis "<< currentAxis;
//    qDebug()<<"parameter"<< currentParameter;

    if (currentParameter == 4)   qDebug()<<"none";
    if (currentParameter == 2)  {qDebug()<<"roll axis  "<<currentAxis;rollAxis=currentAxis;}
    if (currentParameter == 3)  {qDebug()<<"pitch axis  "<<currentAxis;pitchAxis=currentAxis;}
    if (currentParameter == 0)  {qDebug()<<"yaw axis  "<<currentAxis;yawAxis=currentAxis;}
    if (currentParameter == 1)  {qDebug()<<"thorttle axis  "<<currentAxis;thorttleAxis=currentAxis;}


}
void JoystickParameters::get_axis_value_qml(double currentAxis, double currentValue)
{
    if(currentAxis==rollAxis)
    {
    //qDebug()<<"roll axis"<< rollAxis<< "value"<<currentValue;
    rollValue=currentValue;
   // qDebug()<<"roll value"<<rollValue;
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
void JoystickParameters::get_joystick_protocol_qml(int index)
{
    if (index == 0)   {
        qDebug()<<"MavLink";

        emit qmlMavLinkjoystickcontrols(rollValue,pitchValue,yawValue,thorttleValue);
                       }

    if (index == 1)   qDebug()<<"DJI";

}

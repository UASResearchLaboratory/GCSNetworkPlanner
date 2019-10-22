#ifndef JOYSTICKPARAMETERS_H
#define JOYSTICKPARAMETERS_H

#include <QObject>

class JoystickParameters : public QObject
{
    Q_OBJECT
public:
    explicit JoystickParameters(QObject *parent = nullptr);

signals:
       void    qmljoystickcontrols(int roll,int pitch,int yaw,int thorttle);
       void    qmlMavLinkjoystickcontrols(int roll,int pitch,int yaw,int thorttle);
       void    qmlDJIjoystickcontrols(int roll,int pitch,int yaw,int thorttle);

public slots:


    void    get_joystick_protocol_qml(int index);
    void    get_axis_qml(double currentAxis,double currentParameter);
    void    get_axis_value_qml(double currentAxis,double currentValue);

private:
    int _roll, _pitch, _yaw, _throttle, axisvalue,rollAxis,pitchAxis,yawAxis,thorttleAxis,rollValue,pitchValue,yawValue,thorttleValue;




};



#endif // JOYSTICKPARAMETERS_H

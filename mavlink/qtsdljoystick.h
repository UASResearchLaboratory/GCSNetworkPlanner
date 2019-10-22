#ifndef QTSDLJOYSTICK_H
#define QTSDLJOYSTICK_H

#include <QObject>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <QThread>
#include <QDebug>
#include <QWidget>
#include <cmath>
#include "QTimer"

class QtSDLJoystick : public QThread
{
    Q_OBJECT
public:
    explicit QtSDLJoystick();
   // void run();
    static int axisScaling(int event_value, bool sign);
    static int axisScalingThrottle(int event_value, bool sign);

signals:
    void signalJoystickList(QStringList list);
    void signalRoll(int roll);
    void signalPitch(int pitch);
    void signalThrottle(int throttle);
    void signalYaw(int yaw);

    void signalMode1();
    void signalMode2();
    void signalMode3();
    void signalGear1();
    void signalGear2();
    void signalTakeOff();
    void signalLanding();
    void signalGoHome();
    void signalExcuteTask();
    void manualCommandsSignal(int roll, int pitch, int yaw, int throttle);

public slots:
    void slotStop(bool bl);

private:
    QList<SDL_Joystick *>joy_list;
    bool flag_start_stop;
    QStringList stringJoyList;
    QTimer * timer;

};

#endif // QTSDLJOYSTICK_H

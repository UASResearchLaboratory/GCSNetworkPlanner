#include "djigcs.h"


DJI::onboardSDK::DjiGcs::DjiGcs(QObject *parent) : QObject(parent)
{
    driver = new QtOnboardsdkPortDriver();
    api = new CoreAPI(driver);
    key = new QByteArray;
    flight = new Flight(api);
    follow = new Follow(api);
    vrc = new VirtualRC(api);
    cam = new Camera(api);
    hp = new HotPoint(api);
    wp = new WayPoint(api);
    QObject::connect(driver,SIGNAL(appendDjiApiLogQML(QVariant)),this,SIGNAL(appendDjiApiLogQML(QVariant)));
    startTimer(2);
}

void DJI::onboardSDK::DjiGcs::startUpdateFlightInstruments(int msec)
{
    timerUpdateFlightInstruments.setInterval(msec);

    QObject::connect(&timerUpdateFlightInstruments,SIGNAL(timeout()),this,SLOT(updateUavRoll()));
    QObject::connect(&timerUpdateFlightInstruments,SIGNAL(timeout()),this,SLOT(updateUavPitch()));
    QObject::connect(&timerUpdateFlightInstruments,SIGNAL(timeout()),this,SLOT(updateUavHeading()));
    QObject::connect(&timerUpdateFlightInstruments,SIGNAL(timeout()),this,SLOT(updateUavAltitude()));
    QObject::connect(&timerUpdateFlightInstruments,SIGNAL(timeout()),this,SLOT(updateUavGPS()));
    //QObject::connect(&timerUpdateFlightInstruments,SIGNAL(timeout()),this,SLOT(printValue()));

    timerUpdateFlightInstruments.start();
}

void DJI::onboardSDK::DjiGcs::timerEvent(QTimerEvent *)
{
    api->sendPoll();
    api->readPoll();
}

void DJI::onboardSDK::DjiGcs::init(QVariant list)
{
    QStringList str_list = list.toStringList();
    if(str_list.size()==3)
    driver->init();

}

void DJI::onboardSDK::DjiGcs::setControlCallback(CoreAPI *This, Header *header, UserData userData)
{
    DJI::onboardSDK::DjiGcs *sdk = (DJI::onboardSDK::DjiGcs *)userData;
    unsigned short ack_data = ACK_COMMON_NO_RESPONSE;
    unsigned char data = 0x1;

    if (header->length - EXC_DATA_SIZE <= 2)
    {
        memcpy((unsigned char *)&ack_data, ((unsigned char *)header) + sizeof(Header),
               (header->length - EXC_DATA_SIZE));
    }
    else
    {
        API_LOG(sdk->driver, ERROR_LOG, "ACK is exception,seesion id %d,sequence %d\n",
                header->sessionID, header->sequenceNumber);
    }

    switch (ack_data)
    {
        case ACK_SETCONTROL_ERROR_MODE:
            if (sdk)  {
                if (sdk->api->getFwVersion() > MAKE_VERSION(3,2,0,0))
                {
                     sdk->log("Switch to mode P");
                     sdk->updateObtainControlButton(QVariant("Switch to mode P"));
                }
                else
                {
                    sdk->log("Switch to mode F");
                    sdk->updateObtainControlButton(QVariant("Switch to mode F"));
                }
            }
            else
                API_LOG(sdk->driver, ERROR_LOG, "known SDK pointer 0.");
            break;
        case ACK_SETCONTROL_RELEASE_SUCCESS:
            if (sdk)
            {
                sdk->log("Obtain Control");
                sdk->updateObtainControlButton(QVariant("Obtain Control"));
            }
            else
                API_LOG(sdk->driver, ERROR_LOG, "known SDK pointer 0.");
            break;
        case ACK_SETCONTROL_OBTAIN_SUCCESS:
            if (sdk)
            {
                sdk->log("Release Control");
                sdk->updateObtainControlButton(QVariant("Release Control"));
            }
            else
            {
                API_LOG(sdk->driver, ERROR_LOG, "known SDK pointer 0.");
            }
            break;
        case ACK_SETCONTROL_OBTAIN_RUNNING:
            This->send(2, DJI::onboardSDK::encrypt, SET_CONTROL, CODE_SETCONTROL, &data, 1, 500, 2,
                       DJI::onboardSDK::DjiGcs::setControlCallback, userData);
            break;
        case ACK_SETCONTROL_RELEASE_RUNNING:
            data = 0;
            This->send(2, DJI::onboardSDK::encrypt, SET_CONTROL, CODE_SETCONTROL, &data, 1, 500, 2,
                       DJI::onboardSDK::DjiGcs::setControlCallback, userData);
            break;
    }
}

void DJI::onboardSDK::DjiGcs::activationCallback(CoreAPI *This, Header *header, UserData userData)
{
    DJI::onboardSDK::DjiGcs *sdk = (DJI::onboardSDK::DjiGcs *)userData;
    volatile unsigned short ack_data;
    if (header->length - EXC_DATA_SIZE <= 2)
    {
        memcpy((unsigned char *)&ack_data, ((unsigned char *)header) + sizeof(Header),
               (header->length - EXC_DATA_SIZE));
        if (ack_data == ACK_ACTIVE_NEW_DEVICE)
        {
            sdk->log("New Device");
            sdk->updateActivationButton(QVariant("New Device"));
        }
        else
        {
            if (ack_data == ACK_ACTIVE_SUCCESS)
            {
                sdk->log("Activation Okay");
                sdk->updateActivationButton(QVariant("Activation Okay"));
            }
            else
            {
                sdk->log("Activation Error");
                sdk->updateActivationButton(QVariant("Activation Error"));
            }
        }
    }
    else
    {
        sdk->log("Decode Error");
        sdk->updateActivationButton(QVariant("Decode Error"));
    }
    This->activateCallback(This, header);
    sdk->functionAlloc();
}

void DJI::onboardSDK::DjiGcs::apiCoreActive(QVariant var)
{
    QStringList str_list = var.toStringList();
    ActivateData data;
    data.ID = str_list.at(0).toInt();
    *key = str_list.at(1).toLocal8Bit();
    data.encKey = key->data();
    api->activate(&data, DJI::onboardSDK::DjiGcs::activationCallback, this);
}

void DJI::onboardSDK::DjiGcs::apiCoreSetControl(QVariant var)
{
    bool boolean = var.toBool();

    if (boolean)
        api->setControl(true, DJI::onboardSDK::DjiGcs::setControlCallback, this);
    else
        api->setControl(false, DJI::onboardSDK::DjiGcs::setControlCallback, this);
}

void DJI::onboardSDK::DjiGcs::apiCoreDroneVersion()
{
    api->getDroneVersion();
}

void DJI::onboardSDK::DjiGcs::log(QString str)
{/*
    qDebug() << str;
    emit appendDjiApiLogQML(QVariant(str));*/
}

void DJI::onboardSDK::DjiGcs::functionAlloc()
{
    this->log(QString(api->getFwVersion()));
    /*if (api->getFwVersion() < MAKE_VERSION(3,1,0,0))
    {
        this->log(api->getFwVersion())
        ui->gb_CoreData->setEnabled(false);
        ui->gb_VRC->setEnabled(false);
        ui->gb_RTK->setEnabled(false);
        ui->gb_GPS->setEnabled(false);
        ui->gb_Mission->setEnabled(false);
        ui->gb_wp->setEnabled(false);
    }
    else if (api->getFwVersion() < MAKE_VERSION(3,1,50,0))
    {
        ui->gb_CoreData->setEnabled(true);
        ui->gb_VRC->setEnabled(true);
        ui->gb_RTK->setEnabled(false);
        ui->gb_GPS->setEnabled(false);
        ui->gb_Mission->setEnabled(true);
        ui->gb_wp->setEnabled(true);
    }
    else
    {
        ui->gb_CoreData->setEnabled(true);
        ui->gb_VRC->setEnabled(true);
        ui->gb_RTK->setEnabled(true);
        ui->gb_GPS->setEnabled(true);
        ui->gb_Mission->setEnabled(true);
        ui->gb_wp->setEnabled(true);
    }*/
}

void DJI::onboardSDK::DjiGcs::taskTakeOff()
{
    Flight::TASK type = Flight::TASK_TAKEOFF;
    flight->task(type);
}

void DJI::onboardSDK::DjiGcs::taskLanding()
{
    Flight::TASK type = Flight::TASK_LANDING;
    flight->task(type);
}

void DJI::onboardSDK::DjiGcs::taskGoHome()
{
    Flight::TASK type = Flight::TASK_GOHOME;
    flight->task(type);
}

void DJI::onboardSDK::DjiGcs::updateUavRoll()
{
    emit sigUpdateUavRoll(flight->getRoll());
}

void DJI::onboardSDK::DjiGcs::updateUavPitch()
{
    emit sigUpdateUavPitch(flight->getPitch());
}

void DJI::onboardSDK::DjiGcs::updateUavHeading()
{
    emit sigUpdateUavHeading(flight->getYaw());
}

void DJI::onboardSDK::DjiGcs::updateUavAltitude()
{
    emit sigUpdateUavAltitude(flight->getPosition().altitude);
}

void DJI::onboardSDK::DjiGcs::updateUavGPS()
{
    emit sigUpdateUavGPS(QVariant(flight->getPosition().latitude),QVariant(flight->getPosition().longitude));
}

void DJI::onboardSDK::DjiGcs::updateObtainControlButton(QVariant var)
{
    emit signalUpdateObtainControlButton(var);
}

void DJI::onboardSDK::DjiGcs::updateActivationButton(QVariant var)
{
    emit signalUpdateActivationButton(var);
}

void DJI::onboardSDK::DjiGcs::printValue()
{
   // qDebug() <<  qRadiansToDegrees(flight->getPitch()) << qRadiansToDegrees(flight->getRoll()) << qRadiansToDegrees(flight->getYaw());
}

#include "QonboardSDK.h"
#include <QDateTime>
#include <QScrollBar>
#include <QDebug>

QtOnboardsdkPortDriver::~QtOnboardsdkPortDriver()
{
    if(thread!=NULL)      delete thread;
}

QtOnboardsdkPortDriver::QtOnboardsdkPortDriver()
{

    thread = NULL;
}
QTextBrowser *QtOnboardsdkPortDriver::getDisplay() const { return display; }

void QtOnboardsdkPortDriver::setDisplay(QTextBrowser *value) { display = value; }


//_________________________
//_________________________


void QtOnboardsdkPortDriver::init()
{

}

//_________________________
//_________________________
//_________________________
//_________________________
//_________________________
//_________________________


DJI::time_ms QtOnboardsdkPortDriver::getTimeStamp() { return QDateTime::currentMSecsSinceEpoch(); }
//_________________________
//_________________________

//_________________________
//_________________________

size_t QtOnboardsdkPortDriver::send(const uint8_t *buf, size_t len)
{
    sendLock.lock();
    size_t sent = 0;
    if(false)
    {
        QByteArray arr = QByteArray((char *)buf, len);

        sent=len;
    }
    sendLock.unlock();
    return sent;
}
//_________________________
//_________________________
//_________________________
//_________________________
//_________________________
//_________________________

//_________________________
//_________________________
//_________________________
//________dds_read_________
//________dds_read_________
//_________________________
//_________________________
//_________________________

size_t QtOnboardsdkPortDriver::readall(uint8_t *buf, size_t maxlen)
{
    readalllock.lock();
    size_t ans = 0;
    if(false)
    {

//        memcpy(buf,all.data(),all.count());
//        ans = all.count();
    }
    readalllock.unlock();
    return ans;
}

//_________________________
//_________________________
//_________________________
//_________________________
//_________________________
//_________________________


void QtOnboardsdkPortDriver::lockMemory() { memory.lock(); }
void QtOnboardsdkPortDriver::freeMemory() { memory.unlock(); }
void QtOnboardsdkPortDriver::lockMSG() { msg.lock(); }
void QtOnboardsdkPortDriver::freeMSG() { msg.unlock(); }
void QtOnboardsdkPortDriver::lockACK() {ack.lock();}
void QtOnboardsdkPortDriver::freeACK() {ack.unlock();}
void QtOnboardsdkPortDriver::notify() {}
void QtOnboardsdkPortDriver::wait(int timeout) {}

void QtOnboardsdkPortDriver::displayLog(const char *buf)
{
    if (buf)
        qDebug("%s", buf);
    else
    {
        if (display)
        {
            bufferLock.lock();
            QString data = QString(DJI::onboardSDK::buffer);
            size_t len = data.length();
            if (len < DJI::onboardSDK::bufsize)
                emit appendDjiApiLogQML(QVariant(data));
            bufferLock.unlock();
        }
        else
        {
            bufferLock.lock();
            emit appendDjiApiLogQML(QVariant(DJI::onboardSDK::buffer));
            bufferLock.unlock();
        }
    }
}

APIThread::APIThread(CoreAPI *API, int Type, QObject *parent) : QThread(parent)
{
    api = API;
    type = Type;
}

void APIThread::run()
{
    while (1)
    {
        callTimes++;
        if (type == 1)
            api->sendPoll();
        else if (type == 2)
            api->readPoll();
        msleep(1);
    }
}
size_t APIThread::getCallTimes() const { return callTimes; }

void APIThread::setCallTimes(const size_t &value) { callTimes = value; }

APIThread::APIThread()
{
    api = 0;
    type = 0;
}

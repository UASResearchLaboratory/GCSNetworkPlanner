
#include "serialportreader.h"




QT_USE_NAMESPACE

SerialPortReader::SerialPortReader()
{
    counter=0;
    batteryPercentage=0;

    m_serialPort = new QSerialPort();
    QString serialPortName = "/dev/ttyUSB0";
    m_serialPort->setPortName(serialPortName);

    int serialPortBaudRate = QSerialPort::Baud115200;
    m_serialPort->setBaudRate(serialPortBaudRate);
    m_serialPort->setReadBufferSize(100);

    if (!m_serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << QObject::tr("Failed to open port %1, error: %2").arg(serialPortName).arg(m_serialPort->errorString()) << endl;
    }
    else
    {
        connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);
        connect(m_serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),this, &SerialPortReader::handleError);
        connect(&m_timer, &QTimer::timeout, this, &SerialPortReader::handleTimeout);
    }


}




SerialPortReader::~SerialPortReader()
{



}


void SerialPortReader::wrirtetoserial(QByteArray msg)

{  /* QByteArray msg;
    msgb.setNum(msg);*/

    m_serialPort->write(msg);
    m_serialPort->flush();
  qDebug()<<"wrote s "<<msg ;

}


void SerialPortReader::handleReadyRead()
{




   // m_readData.append(m_serialPort->readAll());
    emit serialrawdata(m_serialPort->readAll());







    //qDebug() << "readall" << m_readData ;
    if (!m_timer.isActive())
        m_timer.start(5000);
}

void SerialPortReader::handleTimeout()

{
   //qDebug() << "SerialPortReader::handleTimeout";
    if (m_readData.isEmpty()) {
       qDebug() << QObject::tr("No data was currently available for reading from port %1").arg(m_serialPort->portName()) << endl;
    } else {
       // qDebug() << QObject::tr("Data successfully received from port %1").arg(m_serialPort->portName()) << endl;
       // qDebug() << m_readData << endl;
    }
}

void SerialPortReader::handleError(QSerialPort::SerialPortError serialPortError)
{
    // qDebug() << "SerialPortReader::handleError";
    if (serialPortError == QSerialPort::ReadError) {
        qDebug() << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
    }
}
























/* int im= 0;
 while (im= -1)

{

     output = "AT+csq\r\n";
m_serialPort->write(output);
 m_serialPort->flush();
m_serialPort->waitForReadyRead(200);
 input = m_serialPort->readAll();
//qDebug() << input;

 QRegExp rx("(\\d+)");
 QStringList list;
 int pos = 0;

 while ((pos = rx.indexIn(QString(input), pos)) != -1) {
     list << rx.cap(1);
     pos += rx.matchedLength();
 }

qDebug() << list;

 }*/


/*
// Text message mode
output = "AT+CGACT=1,1\r\n";
m_serialPort->write(output);

m_serialPort->flush();

// read the response of the modem
m_serialPort->waitForReadyRead(200);
input = m_serialPort->readAll();
qDebug() << input;

// set phone number and Message
output = "AT+ZGACT=1,1\r\n";
m_serialPort->write(output);
m_serialPort->flush();

// get reponse
m_serialPort->waitForReadyRead(200);
input = m_serialPort->readAll();
qDebug() << input;

int im= 0;
 while (im= -1)

{

     output = "AT+csq\r\n";
m_serialPort->write(output);
 m_serialPort->flush();
m_serialPort->waitForReadyRead(200);
 input = m_serialPort->readAll();
//qDebug() << input;

 QRegExp rx("(\\d+)");
 QStringList list;
 int pos = 0;

 while ((pos = rx.indexIn(QString(input), pos)) != -1) {
     list << rx.cap(1);
     pos += rx.matchedLength();
 }

qDebug() << list;
}
*/

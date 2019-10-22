#-------------------------------------------------
#
# Project created by QtCreator 2017-08-20T13:05:09
#
#-------------------------------------------------

QT       += core gui quick widgets quickwidgets qml serialport network svg printsupport multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../bin/NetworkPlannerGCS
TEMPLATE = app


INCLUDEPATH= ../include \
             ../include/dji_sdk \
                src_qfi \
                src_qfi/example \
                dji_sdk/inc \
                /OpenDDS3.12/include \
INCLUDEPATH += /usr/local/include/sphinxbase\
                /usr/local/include/pocketsphinx
INCLUDEPATH += /usr/include/gstreamer-1.0/\
               /usr/include/glib-2.0/\
        /usr/lib/x86_64-linux-gnu/glib-2.0/include




SOURCES += main.cpp\
    src_qfi/qfi_VSI.cpp \
    src_qfi/qfi_TC.cpp \
    src_qfi/qfi_PFD.cpp \
    src_qfi/qfi_NAV.cpp \
    src_qfi/qfi_HSI.cpp \
    src_qfi/qfi_ASI.cpp \
    src_qfi/qfi_ALT.cpp \
    src_qfi/qfi_ADI.cpp \
    flightinstrumentsimageprovider.cpp \
    djigcs.cpp \
    djigcs/QonboardSDK.cpp \
    mavlink/serialportreader.cpp \
    mavlink/qtsdljoystick.cpp \
    mavlink/mavlink_raw_message.cpp \
    joystickparameters.cpp \
    udpgcs.cpp \
    qcustomplot.cpp \
    qmlplot.cpp \
    modem_decode.cpp \
    file_writer.cpp \
    logging.cpp \
    mavlink/mav_gcs_manager.cpp

HEADERS  += \
    src_qfi/qfi_VSI.h \
    src_qfi/qfi_TC.h \
    src_qfi/qfi_PFD.h \
    src_qfi/qfi_NAV.h \
    src_qfi/qfi_HSI.h \
    src_qfi/qfi_ASI.h \
    src_qfi/qfi_ALT.h \
    src_qfi/qfi_ADI.h \
    flightinstrumentsimageprovider.h \
    djigcs.h \
    djigcs/QonboardSDK.h \
    mavlink/serialportreader.h \
    mavlink/qtsdljoystick.h \
    mavlink/mavlink_raw_message.h \
    joystickparameters.h \
    network_linker.h \
    udpgcs.h \
    qcustomplot.h \
    qmlplot.h \
    modem_decode.h \
    file_writer.h \
    logging.h \
    mavlink/mav_gcs_manager.h


RESOURCES += \
    src_qfi/qfi.qrc \
    icon.qrc \
    qml.qrc

DISTFILES += \
    Plot/qtquickcontrols2.conf

FORMS +=

LIBS +=  -L../bin/ \
    -ldjisdk \
    -lSDL2
LIBS += -L/usr/lib/x86_64-linux-gnu/gstreamer-1.0 -lgstreamer-1.0  -lgobject-2.0 -lglib-2.0 \
                    -lgio-2.0


include ($$PWD/QJoysticks/QJoysticks.pri)


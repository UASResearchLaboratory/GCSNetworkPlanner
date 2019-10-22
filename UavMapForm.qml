
import QtQuick 2.11
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import QtQuick.Extras 1.4
import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2
import QtMultimedia 5.11
Item
{
    id: item1

    signal flightCommandTakeOff();
    signal connectSerial();
    signal connectRJ();
    signal connectCellular();
    signal decodeSpeak();
    signal disconnectSpeak();
    signal flightCommandLand()
    signal flightCommandRtl()
    signal flightCommandAddDrone()
    signal newDdsArgumentsDJI(var list)
    signal newDdsArgumentsMAV(var list)
    signal activateDjiUav(var list)
    signal djiObatainControl(var state)
    signal buttonVersionClicked()
    signal joystickParameters(double axis,double currentParameter)
    signal joystickValue(double axis,double Value)
    signal joystickProtocolChanged(int index)
    signal sendSignalLatitude(var latitude)
    signal sendSignalLongitude(var longitude)
    signal sendSignalFlightModes(int base, int custom)
    property double joystickaxis :0
    property double joystickoption:0
    property double anglec: 0
    property double batteryPercentage
    property double batteryVoltage
    property double batteryCourrant

    signal cellrows(var rows)
    signal sendCellsCoordinates(var latitude, var longitude)
    signal antennasCl();
    signal meteoSize();
    signal missionResultSignal(int result)
    signal sendModeIndex(int index)
    signal sendNetworkIcons(var type, var quality)
    signal guiQMLLTEParameters(var rssi,var rsrp,var sinr,var rsrq)
    signal guiQMLWCDMAParameters(var rssi,var rscp,var ecio)
    signal guiQMLGSMParameters (var rssi )
    signal guiQMLRangeParameters (var rssi,var rsrp,var sinr,var rsrq )
    signal setTypeNetworkIndex(var index)
    signal plotIndexChanged(var index)






    height: 480
    clip: true
    width: 640

    property var componentDds
    property var windowDds

    property var componentNetwork
    property var windowNetwork

    property var componentPlanner
    property var windowPlanner

    property var componentDjiActivate
    property var windowDjiActivate

    property var componentJoystick
    property var windowJoystick

    property var componentPlot
    property var windowPlot

    property var componentSpeak
    property var windowSpeak
    property var missionResult
    property real acceptedIndex
    property real declinedIndex
    property real currentIndexMission


    Component.onCompleted:
    {
        item1.createUdpConnect()
        item1.createDjiActivateMenu()
        item1.createJoystickMenu()
        item1.createPlannerMenu()
        item1.createPlotMenu()
        item1.createNetworkMenu()
        uavMap1.signalAppenList.connect(item1.sendCellsCoordinates)
        uavMap1.clearAntennas.connect(item1.antennasCl)
        timer.start()
        item1.windowNetwork.visible = true



        //  item1.meteoSize.connect(uavMap1.weatherParams)

    }



    UavMap
    {
        id: uavMap1
        anchors.fill: parent
    }
    ListModel
    {   id:batteryInfoList
    }
    //    Rectangle {
    //        id: window
    //        width: 600
    //        height: 300

    //        Video {
    //            id: video
    //            y : 10;
    //            width: window.width
    //            height: 260
    //            source: "qrc:/ico/video.mp4"
    //            MouseArea {
    //                anchors.fill: parent
    //                onClicked: {
    //                    video.play()
    //                }
    //            }

    //            focus: true
    //              Keys.onSpacePressed: video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
    //              Keys.onLeftPressed: video.seek(video.position - 5000)
    //              Keys.onRightPressed: video.seek(video.position + 5000)
    //        }

    //    }
    Image {
        id:batteryInfo

        fillMode: Image.PreserveAspectFit
        enabled: true
        smooth: false
        antialiasing: true
        anchors.horizontalCenterOffset: 21
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        sourceSize.width: 56

        //opacity: 0.7
        source: {
            if (batteryPercentage>=75)
            {
                "qrc:/ico/full battery.png"
            }
            else if(batteryPercentage<75&&batteryPercentage>=50)
            {
                "qrc:/ico/75 battery.png"
            }
            else if(batteryPercentage<50&&batteryPercentage>=25)
            {
                "qrc:/ico/50 battery.png"
            }
            else
            {
                "qrc:/ico/25 battery.png"

            }


        }




    }

    MouseArea
    {   anchors.fill: batteryInfo
        id:batteryInfoMouseArea
        width: 56
        height: 32
        hoverEnabled: true
        // acceptedButtons: Qt.LeftButton

        onEntered: {
            batteryInfoRect.visible=true
            seqModem.running=true
        }
        onExited: {
            batteryInfoRect.visible=false
            seqModem.running=true
        }

    }
    Rectangle {
        id:batteryInfoRect
        width: 200
        height: 200
        anchors.top: batteryInfo.bottom
        anchors.left: batteryInfo.left
        radius: 17
        border.color:"black" //"#7CC7FF"
        border.width: 2
        color: "#7CC7FF"
        visible: false
        Label
        {
            Text {
                id: textbattery
                text: {text:batteryInfoList.key+ ": " +batteryInfoList.value }
            }
        }

        // anchors.fill: parent

    }

    ComboBox {
        id:modesList
        x: 400
        y: 0
        width: 147
        height: 50
        font.underline: false
        font.italic: false
        font.bold: false
        opacity: 0.6
        //spacing: -5
        flat: true
        currentIndex: 0
        antialiasing: false
        //clip: true
        // wheelEnabled: false
        focusPolicy: Qt.StrongFocus
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.leftMargin: 109
        anchors.left: imageUAVCommands.right
        textRole: "name"
        model: ListModel
        {   id:flightModesModel

            ListElement
            {
                name:"Manual"
                base:81
                custom:65536
            }

            ListElement
            {
                name:"Stabilized"
                base:81
                custom:458752
            }

            ListElement
            {
                name:"Accro"
                base:81
                custom:327680
            }
            ListElement
            {
                name:"Ratitude"
                base:65
                custom:524288
            }
            ListElement
            {
                name:"Altitude"
                base:65
                custom:131072
            }
            ListElement
            {
                name:"Position"
                base:81
                custom:196608
            }
            ListElement
            {
                name:"OffBoard"
                base:81
                custom:393216
            }
            ListElement
            {
                name:"Hold"
                base:81
                custom:50593792
            }
            ListElement
            {
                name:"Mission"
                base:81
                custom:67371008
            }
            ListElement
            {
                name:"Return"
                base:81
                custom:84148224
            }
            ListElement
            {
                name:"Follow Me"
                base:81
                custom:134479872
            }
        }

        background:
            Rectangle {
            id:backgroundRect
            radius: 17
            border.color:"black" //"#7CC7FF"
            border.width: 2
            color: "#7CC7FF"
            // anchors.fill: parent
        }

        //delegate: backgroundRect

        delegate:   ItemDelegate {
            width: parent.width
            height:50


            //  highlighted: modesList.isCurrentIndex
            background: Rectangle {
                opacity: 0.6
                radius: 17
                border.color:"black"//"#7CC7FF"
                border.width: 2
                color:  "#577284"
                anchors.fill: parent


            }
            contentItem: Text {
                opacity: 0.6
                text:{text:name }
                color: "black"
                font: parent.font
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
            }

        }
        onCurrentIndexChanged:  {



            //            currentIndexMission=currentIndex
            getIndexMode(currentIndex)
            //currentIndex=currentIndexMission

            // sendModeIndex(currentIndex)


            delay(200,function delayedMissionIndex()
            {
                if (missionResult===0)
                {
                    currentIndex=acceptedIndex
                    declinedIndex=acceptedIndex
                }
                else
                {
                    currentIndex=declinedIndex

                }
            })


        }


    }



    Timer {
        id: timer
    }

    function delay(delayTime, cb) {
        timer.interval = delayTime;
        timer.repeat = false;
        timer.triggered.connect(cb);
        timer.start();

    }

    Image
    {
        id: imageUAVCommands
        x: 0
        y: 0

        width: 50
        height: 50
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit
        sourceSize.height: 50
        sourceSize.width: 50

        source: "qrc:/ico/dr1.png"


        SequentialAnimation {
            id:seqAnim1
            running: false
            NumberAnimation { target: imagePlanner; property: "opacity" ;from:0; to: 1; duration: 250 }
            NumberAnimation { target: imageTakeOff; property: "opacity" ;from:0; to: 1; duration: 250 }
            NumberAnimation { target: imageRTL; property: "opacity" ;from:0; to: 1; duration: 250}
            NumberAnimation { target: imageLand; property: "opacity" ;from:0; to: 1; duration: 250 }
        }
        SequentialAnimation {
            id:seqClose1
            running: false
            NumberAnimation { target: imageLand; property: "opacity" ;from:1; to: 0; duration: 250 }
            NumberAnimation { target: imageRTL; property: "opacity" ;from:1; to: 0; duration: 250}
            NumberAnimation { target: imageTakeOff; property: "opacity" ;from:1; to: 0; duration: 250 }
            NumberAnimation { target: imagePlanner ;property: "opacity" ;from:1; to: 0; duration: 250 }
        }

        SequentialAnimation {
            id:seqModem
            running: false
            NumberAnimation { target: windowNetwork; property: "x" ;from:0; to: 400; duration: 1000 }
        }


        RotationAnimator
        {
            id:rotationPar1
            target: imageUAVCommands;
            from: 0;
            to: 360;
            duration: 1000
            running: false
        }
        RotationAnimator
        {
            id:rotationPari1
            target: imageUAVCommands
            from: 360;
            to: 0;
            duration: 1000
            running: false
        }
        MouseArea
        {
            id: mouseareaImageUAVcommands
            x: 140
            width: 37
            height: 34
            anchors.fill: parent
            hoverEnabled: true
            onEntered:
            {
                imageUAVCommands.source = "qrc:/ico/dr1.png";
                // rowLayout1.visible=true;


            }
            onExited:
            {
                imageUAVCommands.source = "qrc:/ico/dr1.png";

            }
            onClicked:
            {

                if (rowLayoutFlightCommand.visible==true)
                {
                    seqClose1.running=true;
                    rotationPari1.running=true;

                    delay(1000,function disableLayout2()
                    {
                        rowLayoutFlightCommand.visible=false;
                    });

                }
                else if (rowLayoutFlightCommand.visible==false)
                {
                    rowLayoutFlightCommand.visible=true;
                    seqAnim1.running=true;
                    rotationPar1.running=true;
                    console.log("enabled");

                }

            }
        }
    }
    Image
    {
        id: imageUAVConnect

        width: 50
        height: 50
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.leftMargin: 103
        fillMode: Image.PreserveAspectFit
        sourceSize.height: 50
        sourceSize.width: 50

        source: "qrc:/ico/connect.png"


        SequentialAnimation {
            id:seqAnim2
            running: false
            NumberAnimation { target: imageSerial; property: "opacity" ;from:0; to: 1; duration: 250 }
            NumberAnimation { target: imageRJ; property: "opacity" ;from:0; to: 1; duration: 250 }
            NumberAnimation { target: imageCellular; property: "opacity" ;from:0; to: 1; duration: 250}

        }
        SequentialAnimation {
            id:seqClose2
            running: false
            NumberAnimation { target: imageCellular; property: "opacity" ;from:1; to: 0; duration: 250 }
            NumberAnimation { target: imageRJ; property: "opacity" ;from:1; to: 0; duration: 250}
            NumberAnimation { target: imageSerial; property: "opacity" ;from:1; to: 0; duration: 250 }






        }

        RotationAnimator
        {
            id:rotationPar2
            target: imageUAVConnect;
            from: 0;
            to: 360;
            duration: 1000
            running: false
        }
        RotationAnimator
        {
            id:rotationPari2
            target: imageUAVConnect
            from: 360;
            to: 0;
            duration: 1000
            running: false
        }
        MouseArea
        {
            id: mouseareaImageUAVConnect
            x: 140
            width: 37
            height: 34
            anchors.fill: parent
            hoverEnabled: true
            onEntered:
            {
                imageUAVConnect.source = "qrc:/ico/connecti.png";
                // rowLayout1.visible=true;


            }
            onExited:
            {
                imageUAVConnect.source = "qrc:/ico/connect.png";

            }
            onClicked:
            {

                if (rowLayoutConnect.visible==true)
                {
                    seqClose2.running=true;
                    rotationPari2.running=true;

                    delay(1000,function disableLayout3()
                    {
                        rowLayoutConnect.visible=false;
                    });

                }
                else if (rowLayoutConnect.visible==false)
                {
                    rowLayoutConnect.visible=true;
                    seqAnim2.running=true;
                    rotationPar2.running=true;
                    console.log("enabled");

                }

            }
        }
    }


    ColumnLayout
    {
        id: rowLayoutFlightCommand
        width: 35
        height: 146
        anchors.top: parent.top
        anchors.topMargin: 48
        anchors.left: parent.left
        anchors.leftMargin: 8
        visible:false


        Image {
            id: imagePlanner
            y: 111
            width: 40
            height: 40
            opacity: 0
            sourceSize.height: 50
            sourceSize.width: 50
            source: "qrc:/ico/planner.png"
            MouseArea
            {
                id: mouseareaimagePlanner

                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    image_flight_instruments.visible=false
                    windowPlanner.visible=true
                }

                onDoubleClicked: {
                    image_flight_instruments.visible=true
                    windowPlanner.visible=false
                }

                onEntered:
                {
                    imagePlanner.source = "qrc:/ico/planneri.png";
                }
                onExited:
                {
                    imagePlanner.source = "qrc:/ico/planner.png";


                }
            }

            Component.onCompleted:
            {
                //mouseareaimageTakeOff.clicked.connect(item1.flightCommandTakeOff)

            }
        }


        Image {
            id: imageTakeOff
            y: 0
            width: 35
            height: 35
            sourceSize.height: 50
            sourceSize.width: 50
            opacity: 0
            source: "qrc:/ico/takeoff.ico"
            MouseArea
            {
                id: mouseareaimageTakeOff
                anchors.fill: parent
                hoverEnabled: true
                onEntered:
                {
                    imageTakeOff.source = "qrc:/ico/takeoffi.ico";
                }
                onExited:
                {
                    imageTakeOff.source = "qrc:/ico/takeoff.ico";


                }
            }

            Component.onCompleted:
            {
                mouseareaimageTakeOff.clicked.connect(item1.flightCommandTakeOff)
            }
        }

        Image {
            id: imageRTL
            y: 37
            width: 35
            height: 35
            sourceSize.height: 50
            sourceSize.width: 50
            opacity: 0
            source: "qrc:/ico/rtl.ico"
            MouseArea
            {
                id: mouseareaimageRTL
                anchors.fill: parent
                hoverEnabled: true
                onEntered:
                {
                    imageRTL.source = "qrc:/ico/rtli.ico";
                }
                onExited:
                {
                    imageRTL.source = "qrc:/ico/rtl.ico";
                }

            }
            Component.onCompleted:
            {
                mouseareaimageRTL.clicked.connect(item1.flightCommandRtl)
            }
        }

        Image {
            id: imageLand
            y: 74
            width: 35
            height: 35
            sourceSize.height: 50
            sourceSize.width: 50
            opacity: 0
            source: "qrc:/ico/land.ico"
            MouseArea
            {
                id: mouseareaimageLand
                anchors.fill: parent
                hoverEnabled: true
                onEntered:
                {
                    imageLand.source = "qrc:/ico/landi.ico";
                }
                onExited:
                {
                    imageLand.source = "qrc:/ico/land.ico";
                }
            }
            Component.onCompleted:
            {
                mouseareaimageLand.clicked.connect(item1.flightCommandLand)
            }
        }



    }



    ColumnLayout
    {
        id: rowLayoutConnect

        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 100
        visible:false


        Image {
            id: imageSerial
            y: 111
            width: 35
            height: 35
            opacity: 1
            sourceSize.height: 50
            sourceSize.width: 50
            source: "qrc:/ico/serial.png"
            MouseArea
            {
                id: mouseareaimageSerial

                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    imageSerial.source = "qrc:/ico/seriali.png";
                    imageRJ.source = "qrc:/ico/rj45.png";
                    imageCellular.source = "qrc:/ico/cellular.png";
                    //                    mouseareaimageSerial.clicked.disconnect(item1.connectCellular)
                    //                    mouseareaimageSerial.clicked.disconnect(item1.connectRJ)
                    mouseareaimageSerial.clicked.connect(item1.connectSerial)

                }
            }

            Component.onCompleted:
            {
                //mouseareaimageTakeOff.clicked.connect(item1.flightCommandTakeOff)

            }
        }


        Image {
            id: imageRJ
            y: 0
            width: 35
            height: 35
            sourceSize.height: 50
            sourceSize.width: 50
            opacity: 1
            source: "qrc:/ico/rj45.png"
            MouseArea
            {
                id: mouseareaimageRJ
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    imageRJ.source = "qrc:/ico/rj45i.png";
                    imageSerial.source= "qrc:/ico/serial.png"
                    imageCellular.source= "qrc:/ico/cellular.png"
                    //                    mouseareaimageRJ.clicked.disconnect(item1.connectCellular)
                    //                    mouseareaimageRJ.clicked.disconnect(item1.connectSerial)
                    mouseareaimageRJ.clicked.connect(item1.connectRJ)

                }

            }

            Component.onCompleted:

            {


            }
        }

        Image {
            id: imageCellular
            y: 37
            width: 35
            height: 35
            sourceSize.height: 50
            sourceSize.width: 50
            opacity: 1
            source: "qrc:/ico/cellular.png"
            MouseArea
            {
                id: mouseareaimageCellular
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {

                    imageRJ.source = "qrc:/ico/rj45.png";
                    imageSerial.source= "qrc:/ico/serial.png"
                    imageCellular.source = "qrc:/ico/cellulari.png";
                    //                    mouseareaimageCellular.clicked.disconnect(item1.connectRJ)
                    //                    mouseareaimageCellular.clicked.disconnect(item1.connectSerial)
                    mouseareaimageCellular.clicked.connect(item1.connectCellular)
                }



            }
            Component.onCompleted:
            {

            }
        }


    }



    Image {
        id: image_flight_instruments
        x: 525
        cache: false
        width: 170
        height: 450
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        source: "image://FlightInstrumentsImageProvider/zig"
    }


    Image
    {
        id: imageParameters
        y: 0

        width: 50
        height: 50
        anchors.left: parent.left
        anchors.leftMargin: 51
        fillMode: Image.PreserveAspectFit
        sourceSize.height: 50
        sourceSize.width: 50
        source: "qrc:/ico/parameters.png"


        SequentialAnimation {
            id:seqAnim
            running: false
            NumberAnimation { target: imageDroneAdd; property: "opacity" ;from:0; to: 1; duration: 200 }
            NumberAnimation { target: imageControlPanel; property: "opacity" ;from:0; to: 1; duration: 200 }
            NumberAnimation { target: imageJoystick; property: "opacity" ;from:0; to: 1; duration: 200}
            NumberAnimation { target: imageSpeak; property: "opacity" ;from:0; to: 1; duration: 200 }
            NumberAnimation { target: imagePlot; property: "opacity" ;from:0; to: 1; duration: 200 }

        }
        SequentialAnimation {
            id:seqClose
            running: false
            NumberAnimation { target: imagePlot; property: "opacity" ;from:1; to: 0; duration: 250 }
            NumberAnimation { target: imageSpeak; property: "opacity" ;from:1; to: 0; duration: 250 }
            NumberAnimation { target: imageJoystick; property: "opacity" ;from:1; to: 0; duration: 250}
            NumberAnimation { target: imageControlPanel; property: "opacity" ;from:1; to: 0; duration: 250 }
            NumberAnimation { target: imageDroneAdd; property: "opacity" ;from:1; to: 0; duration: 250 }





        }

        RotationAnimator
        {
            id:rotationPar
            target: imageParameters;
            from: 0;
            to: 360;
            duration: 1000
            running: false
        }
        RotationAnimator
        {
            id:rotationPari
            target: imageParameters;
            from: 360;
            to: 0;
            duration: 1000
            running: false
        }
        MouseArea
        {
            id: mouseareaImageParameters
            x: 140
            width: 37
            height: 34
            anchors.fill: parent
            hoverEnabled: true
            onEntered:
            {
                imageParameters.source = "qrc:/ico/parametersi.png";
                // rowLayout1.visible=true;


            }
            onExited:
            {
                imageParameters.source = "qrc:/ico/parameters.png";

            }
            onClicked:
            {

                if (rowLayout1.visible===true)
                {
                    seqClose.running=true;
                    rotationPari.running=true;

                    delay(1000,function disableLayout()
                    {
                        rowLayout1.visible=false;
                        imageUAVConnect.visible=true
                    });

                }
                else if (rowLayout1.visible===false)
                {
                    imageUAVConnect.visible=false
                    rowLayout1.visible=true;
                    seqAnim.running=true;
                    rotationPar.running=true;
                    console.log("enabled");

                }

            }
        }
    }

    ColumnLayout
    {
        id: rowLayout1
        x: 0
        width: 100
        height: 50
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 50
        visible: false

        Image
        {
            id: imageDroneAdd
            x: 0
            y: 0
            width: 50
            height: 50
            opacity: 0;

            fillMode: Image.PreserveAspectFit
            sourceSize.height: 50
            sourceSize.width: 50
            source: "qrc:/ico/droneadd.ico"
            MouseArea
            {
                id: mouseareaimageDroneAdd
                width: 37
                height: 34
                anchors.fill: parent
                hoverEnabled: true
                onEntered:
                {
                    imageDroneAdd.source = "qrc:/ico/droneaddi.ico";
                }
                onExited:
                {
                    imageDroneAdd.source = "qrc:/ico/droneadd.ico";
                }
                onClicked: {
                    item1.windowDds.visible = true
                }
            }
            Component.onCompleted:
            {
                mouseareaimageDroneAdd.clicked.connect(item1.flightCommandAddDrone)
            }
        }




        Image
        {
            id: imageControlPanel
            x: 50
            y: 0
            width: 50
            height: 50
            opacity: 0;
            fillMode: Image.PreserveAspectFit
            sourceSize.height: 50
            sourceSize.width: 50
            source: "qrc:/ico/controlpanel.ico"
            MouseArea
            {
                id: mouseareaImageControlPanel
                width: 37
                height: 34
                anchors.fill: parent
                hoverEnabled: true
                onEntered:
                {
                    imageControlPanel.source = "qrc:/ico/controlpaneli.ico";

                }
                onExited:
                {
                    imageControlPanel.source = "qrc:/ico/controlpanel.ico";
                }
                onClicked:
                {
                    if(item1.windowDds.getConnectionStatus() === "Connected")
                        if(item1.windowDds.getUavType() === "DJI")
                            item1.windowDjiActivate.visible = true
                }
            }
        }
        Image {
            id: imageJoystick
            y: 74
            width: 35
            height: 35
            opacity: 0;
            sourceSize.height: 50
            sourceSize.width: 50
            source: "qrc:/ico/rc.png"
            MouseArea
            {
                id: mouseareaimageJoystick
                anchors.bottomMargin: -4
                anchors.leftMargin: 0
                anchors.rightMargin: -5
                anchors.topMargin: 0
                anchors.fill: parent
                hoverEnabled: true
                onEntered:
                {
                    imageJoystick.source = "qrc:/ico/rci.png";
                }
                onExited:
                {
                    imageJoystick.source = "qrc:/ico/rc.png";
                }
                onClicked: {
                    // item1.windowPlot.visible = true

                    switch
                    (item1.windowJoystick.visible)


                    {case true :
                         item1.windowJoystick.visible=false
                         break;
                     case false:
                         item1.windowJoystick.visible=true
                         break;
                    }

                }
                Component.onCompleted: {

                }
            }
        }
        Image {
            id: imageSpeak
            y: 120
            width: 35
            height: 35
            opacity: 0;
            sourceSize.height: 50
            sourceSize.width: 50
            source: "qrc:/ico/speak.png"
            MouseArea
            {
                id: mouseareaimageSpeak
                anchors.bottomMargin: -4
                anchors.leftMargin: 0
                anchors.rightMargin: -5
                anchors.topMargin: 0
                anchors.fill: parent
                hoverEnabled: true
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onEntered:
                {
                    imageSpeak.source = "qrc:/ico/speaki.png";

                }
                onExited:
                {
                    imageSpeak.source = "qrc:/ico/speak.png";
                }
                onClicked: {
                    if (mouse.button == Qt.RightButton)
                    {
                        disconnectSpeak();
                    }
                    else
                    {
                        mouseareaimageSpeak.clicked.connect(item1.decodeSpeak);
                    }
                }
                Component.onCompleted: {
                }
            }
        }

        Image {
            id: imagePlot
            y: 160
            width: 35
            height: 35
            opacity: 0;
            sourceSize.height: 50
            sourceSize.width: 50
            source: "qrc:/ico/graph.png"
            MouseArea
            {
                id: mouseareaimagePlot
                anchors.bottomMargin: -4
                anchors.leftMargin: 0
                anchors.rightMargin: -5
                anchors.topMargin: 0
                anchors.fill: parent
                hoverEnabled: true
                onEntered:
                {
                    imagePlot.source = "qrc:/ico/graphi.png";
                }
                onExited:
                {
                    imagePlot.source = "qrc:/ico/graph.png";
                }
                onClicked: {
                    if(item1.windowPlot.visible===false)
                    {
                        item1.windowPlot.visible = true;
                    }
                    else
                        item1.windowPlot.visible=false;
                }
                Component.onCompleted: {
                }
            }
        }
    }
    RowLayout
    {   id:swipperLayout
        width: 254
        height: 124
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        visible: false

        Rectangle {
            id: rectangle1
            x: 121
            y: 183
            width: 259
            height: 124
            radius: 12
            opacity: 0.7
            scale: 1
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#56a3e0"
                }

                GradientStop {
                    position: 0.831
                    color: "#98b7d0"
                }
            }


            Rectangle {
                id: rectangle
                x: 32
                y: 82
                width: 196
                height: 34
                radius: 17
                visible: true
                clip:true
                color: Material.color(swiper.swipe.complete ? Material.Green : Material.Red, Material.Shade200)


                Image {

                    source:swiper.swipe.complete ?"qrc:/ico/accepted.png"
                                                 : "\ue801"
                    sourceSize.width: 16
                    sourceSize.height: 16
                    anchors.horizontalCenter: parent
                }

                gradient: Gradient {
                    GradientStop {
                        position: 0.1
                        color: "#d5d5d8"
                    }

                    GradientStop {
                        position: 1
                        color: "#000000"
                    }
                }
                border.color: "#00000000"
                RowLayout{
                    id:layoutSwipped

                    Rectangle {
                        id: rectangleSww
                        radius: 17
                        visible: true
                    }

                    Image {

                        id:imageSwiper
                        source: "qrc:/ico/Propeller.png"
                        sourceSize.width: 32
                        sourceSize.height: 32
                    }
                    transform: Translate {x:(swiper.swipe.position)*150}
                }
            }
            SwipeDelegate {
                id: swiper
                x: 32
                y: 82
                width: 196
                height: 34
                clip: true

                spacing: 10
                opacity: 0
                font.wordSpacing: -0.1
                swipe.left:
                    Rectangle {
                    id: rectangleSw
                    x: 32
                    y: 82
                    width: 196
                    height: 34
                    radius: 17
                    visible: false
                    clip:true
                }
            }
        }
        ScrollIndicator.vertical: ScrollIndicator { }
    }
    function updateFlightsInstruments()
    {
        if(image_flight_instruments.source=="image://flightinstrumentsimageprovider/zag")
            image_flight_instruments.source="image://flightinstrumentsimageprovider/zig"
        else
            image_flight_instruments.source="image://FlightInstrumentsImageProvider/zag"
    }



    function createUdpConnect()
    {
        item1.componentDds = Qt.createComponent("qrc:/UdpConnect.qml")
        item1.windowDds    = componentDds.createObject(item1)
        item1.windowDds.anchors.horizontalCenter = item1.horizontalCenter
        item1.windowDds.anchors.verticalCenter   = item1.verticalCenter
        item1.windowDds.visible = false
        item1.windowDds.newDdsArgumentsDJI.connect(item1.newDdsArgumentsDJI)
        item1.windowDds.newDdsArgumentsMAV.connect(item1.newDdsArgumentsMAV)
    }
    function createNetworkMenu()
    {
        item1.componentNetwork = Qt.createComponent("qrc:/NetworkBanner.qml")
        item1.windowNetwork    = componentNetwork.createObject(item1)
        item1.windowNetwork.anchors.top=image_flight_instruments.bottom
        // item1.windowNetwork.anchors.right=image_flight_instruments.left
        item1.windowNetwork.anchors.left=image_flight_instruments.left
        item1.windowNetwork.anchors.leftMargin=-80
        item1.windowNetwork.visible = false
        item1.sendNetworkIcons.connect(item1.windowNetwork.getNetworkParameters)
        item1.guiQMLLTEParameters.connect(item1.windowNetwork.getLteParameters)
        item1.guiQMLWCDMAParameters.connect(item1.windowNetwork.getWCDMAParameters)
        item1.guiQMLGSMParameters.connect(item1.windowNetwork.getGSMParameters)
        item1.guiQMLRangeParameters.connect(item1.windowNetwork.getCellularRangeParameters)
        item1.windowNetwork.setTypeNetworkIndex.connect(item1.setTypeNetworkIndex)

    }

    function createDjiActivateMenu()
    {
        item1.componentDjiActivate = Qt.createComponent("qrc:/DjiActivateUI.qml")
        item1.windowDjiActivate    = componentDjiActivate.createObject(item1)
        item1.windowDjiActivate.parentWin = item1
        item1.windowDjiActivate.anchors.horizontalCenter = item1.horizontalCenter
        item1.windowDjiActivate.anchors.verticalCenter   = item1.verticalCenter
        item1.windowDjiActivate.visible = false
        item1.windowDjiActivate.activateDjiUav.connect(item1.activateDjiUav)

    }

    function createJoystickMenu()
    {

        item1.componentJoystick = Qt.createComponent("qrc:/Joystick.qml")
        item1.windowJoystick    = componentJoystick.createObject(item1)

        item1.windowJoystick.anchors.horizontalCenter = item1.horizontalCenter
        item1.windowJoystick.anchors.bottom  = item1.bottom
        //item1.windowJoystick.parentWin = item1
        //item1.windowJoystick.anchors.horizontalCenter = item1.horizontalCenter
        //        item1.windowJoystick.anchors.verticalCenter   = item1.verticalCenter
        item1.windowJoystick.visible = false
        item1.windowJoystick.axisCd.connect(item1.joystickParameters)
        item1.windowJoystick.axisValueChanged.connect(item1.joystickValue)
        item1.windowJoystick.joystickProtocolChanged.connect(item1.joystickProtocolChanged)



    }


    function createPlotMenu()
    {
        item1.componentPlot = Qt.createComponent("qrc:/PlotMain.qml")
        item1.windowPlot    = componentPlot.createObject(item1)
        item1.windowPlot.visible = false
        item1.windowPlot.indexplot.connect(item1.fPlotIndexChanged)
    }

    function createPlannerMenu()
    {

        item1.componentPlanner = Qt.createComponent("qrc:/Planner.qml")
        item1.windowPlanner   = componentPlanner.createObject(item1)

        item1.windowPlanner.anchors.top = item1.top
        item1.windowPlanner.anchors.topMargin = 10
        item1.windowPlanner.anchors.right = item1.right
        item1.windowPlanner.anchors.rightMargin = 10
        item1.windowPlanner.visible = false
        uavMap1.signalAppenList.connect(item1.windowPlanner.addCoordinate)
        item1.windowPlanner.polylineCoordinates.connect(uavMap1.polylineAdd)
        item1.windowPlanner.polylineRemove.connect(uavMap1.polylineRemove)
        item1.windowPlanner.sendSignalLatitude.connect(item1.sendSignalLatitude)
        item1.windowPlanner.sendSignalLongitude.connect(item1.sendSignalLongitude)
        uavMap1.distanceCalculated.connect(item1.windowPlanner.receiveDistance)
        item1.windowPlanner.distanceUpdate.connect(uavMap1.updatePointsMap)
    }


    function connectionStatusUpdate(status)
    {
        console.log(status)
        item1.windowDds.connectionStatusUpdate(status)
    }

    function appendDjiApiLogQML(log)
    {
        windowDjiActivate.appendDjiApiLogQML(log)
    }

    onFlightCommandLand: console.log("Land");
    onFlightCommandRtl: console.log("rtl")
    onFlightCommandTakeOff: console.log("takeoff")
    onFlightCommandAddDrone: console.log("addDrone")

    function functionButtonVersionClicked()
    {
        buttonVersionClicked()
        console.log("UavMapForm.onButtonVersionClicked")
    }

    function functionDjiObatainControl()
    {
        djiObatainControl(state)
        console.log("UavMapForm.onDjiObatainControl")
    }

    function updateObtainControlButton(status)
    {
        windowDjiActivate.updateObtainControlButton(status)
    }

    function updateActivateButton(status)
    {
        windowDjiActivate.updateActivateButton(status)
    }
    function updateUavGPS(xc,yc)
    {
        uavMap1.updateUavGPS(xc,yc)

        // console.log(xc)
        //        console.log("UavMapForm.updateUavGPS(xc,yc)")
        //        console.log(xc,yc)
    }
    function updatingjoystick()
    {
        //joystickaxis=joystick1.currentAxis

        //        console.log("printed  "+ joystickaxis)
        //         joystickParameters(joystickaxis)



    }



    function angleRefresh(xca)
    {
        uavMap1.angleRefresh(xca)




    }

    function cellinfo(latitude,longitude,range)


    {
        uavMap1.cellInformation(latitude,longitude,range)


    }
    function getRowCell(row)

    {
        console.log("entred here")
        uavMap1.cellRow(row)

    }


    function resultFlightMode(result)
    {

        missionResult=result
        console.log("received result: "+ result)



    }



    function getIndexMode(row)
    {
        acceptedIndex=row
        console.log("accepted index: "+ acceptedIndex )
        console.log("Mode flight number " + row +" "+ flightModesModel.get(row).base )
        sendSignalFlightModes(flightModesModel.get(row).base, flightModesModel.get(row).custom)
        //       missionResultSignal(row)

    }

    function  resultIndex(result)
    {
        console.log("received Index result: "+ result)
        currentIndexMission =result

    }

    function fPlotIndexChanged(index)
    {
        console.log("indexchanged2" + index )
        plotIndexChanged(index)
    }


    function getBatteryData(voltage, percentage,courant)
    {
        batteryVoltage=voltage
        batteryCourrant=courant
        batteryPercentage=percentage
        console.log("battery 1" +percentage)
        console.log("battery 2" + voltage/1000)

        batteryInfoList.set(0,{key: "Percentage", value: percentage})
        batteryInfoList.set(1,{key: "Voltage", value: voltage})
        batteryInfoList.set(2,{key: "Courant", value: courant})

    }

}



















































































/*##^## Designer {
    D{i:2;anchors_y:0}D{i:75;anchors_width:254}D{i:73;anchors_width:254}
}
 ##^##*/

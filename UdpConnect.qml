
import QtQuick 2.0
import QtQml 2.2
import QtQml.Models 2.2
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2


Item {
    id:udpConnect
    opacity: 1
    width: 200
    height: 200

    signal newDdsArgumentsDJI(var args)
    signal newDdsArgumentsMAV(var args)

    /*Component.onCompleted:
    {
        ddsMenu.createDjiActivateMenu()
    }*/

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        nameFilters: [ "Config files (*.ini)", "All files (*)" ]
        onAccepted:
        {
            var path = fileDialog.fileUrl.toString();
            path = path.replace(/^(file:\/{2})/,"");
            var cleanPath = decodeURIComponent(path);
            textFieldDdsPath.text = cleanPath
            Qt.quit()
        }
        onRejected: {
            console.log("Canceled")
            Qt.quit()
        }
        Component.onCompleted: visible = false
    }

    Rectangle {
        id: rectangle1
        color: "#80ffffff"
        radius: 5
        anchors.rightMargin: 0
        anchors.topMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.fill: parent

        Text {
            id: ddsparameters
            x: 45
            width: 110
            height: 17
            text: qsTr("UAV SELECTION")
            anchors.top: parent.top
            anchors.topMargin: 8
            font.pixelSize: 15
        }

//        Button {
//            id: buttonBrowse
//            x: -17
//            text: qsTr("browse")
//            anchors.top: ddsparameters.bottom
//            anchors.topMargin: 10
//            anchors.left: parent.left
//            anchors.leftMargin: 8
//            onClicked:
//            {
//                fileDialog.visible = true
//            }
//        }

//        TextField {
//            id: textFieldDdsPath
//            x: 76
//            anchors.top: ddsparameters.bottom
//            anchors.topMargin: 10
//            anchors.right: parent.right
//            anchors.rightMargin: 8
//            anchors.left: buttonBrowse.right
//            anchors.leftMargin: 8
//            placeholderText: qsTr("")
//            text: "/home/faycal/Desktop/UAVPROJECT/dds_net_conf.ini"
//        }

        Text {
            id: textUavName
            x: -15
            y: 75
            text: qsTr("UAV Name")
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 15
        }

        Text {
            id: textDomainId
            x: -15
            y: 108
            text: qsTr("UAV ID")
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 15
        }

//        Text {
//            id: textTopicName
//            x: -21
//            y: 141
//            text: qsTr("Topic Name")
//            anchors.left: parent.left
//            anchors.leftMargin: 4
//            font.pixelSize: 15
//        }

        TextField {
            id: textFieldUavName
            x: 65
            y: 71
            anchors.left: textUavName.right
            anchors.leftMargin: 8
            anchors.top: textFieldDdsPath.bottom
            anchors.topMargin: 8
            anchors.right: parent.right
            anchors.rightMargin: 8
            placeholderText: qsTr("")
            validator: RegExpValidator { regExp: /[0-9_A-Za-z]{1,10}/ }
            text:"UAV_MAV"
        }

        TextField {
            id: textFieldDomainID
            x: 64
            y: 104
            height: 23
            text: "0"
            anchors.left: textDomainId.right
            anchors.leftMargin: 33
            anchors.top: textFieldUavName.bottom
            anchors.topMargin: 8
            anchors.right: parent.right
            anchors.rightMargin: 8
            placeholderText: qsTr("")
            validator: RegExpValidator { regExp: /[0-9]{1,3}/ }
        }

//        TextField {
//            id: textFieldTopicName
//            x: 67
//            y: 137
//            anchors.left: textTopicName.right
//            anchors.leftMargin: 8
//            anchors.top: textFieldDomainID.bottom
//            anchors.topMargin: 11
//            anchors.right: parent.right
//            anchors.rightMargin: 8
//            placeholderText: qsTr("")
//            validator: RegExpValidator { regExp: /[0-9_A-Za-z]{1,10}/ }
//            text:"0"
//        }

        Button {
            id: buttonConnect
            x: -17
            y: 168
            width: 130
            text: qsTr("Connect")
            anchors.right: parent.right
            anchors.rightMargin: 8
            onClicked:
            {
                var argumentsList = []
                argumentsList.push(textFieldDdsPath.text)
                argumentsList.push(textFieldDomainID.text)
                argumentsList.push(textFieldTopicName.text)
                if(buttonConnect.text == "Connect" || buttonConnect.text == "Reconnect")
                    if(toggleButton1.text == "MAV")
                        ddsMenu.newDdsArgumentsMAV(argumentsList)
                    else
                        ddsMenu.newDdsArgumentsDJI(argumentsList)
            }
        }
        ToggleButton {
            id: toggleButton1
            x: 10
            y: 164
            width: 40
            height: 36
            text: qsTr("DJI")
            Layout.maximumHeight: 50
            Layout.maximumWidth: 50
            transformOrigin: Item.Center
            onCheckedChanged: {
                if(toggleButton1.text=="MAV")
                    toggleButton1.text = qsTr("DJI")
                else
                    toggleButton1.text = qsTr("MAV")
            }
        }
    }
    ToolButton {
        id: toolButtonClose
        x: 8
        width: 23
        height: 17
        text: "X"
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        onClicked:
        {
            ddsMenu.visible = false
        }
    }
    function connectionStatusUpdate(status)
    {
        if(status==="Reconnect" || status==="Connect")
            toggleButton1.visible = true
        else
            toggleButton1.visible = false
        buttonConnect.text = status
    }
    function getUavType()
    {
        return toggleButton1.text
    }
    function getConnectionStatus()
    {
        return buttonConnect.text
    }
}

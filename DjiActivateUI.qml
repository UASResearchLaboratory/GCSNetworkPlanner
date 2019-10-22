import QtQuick 2.0
import QtQml 2.2
import QtQml.Models 2.2
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import QtQuick.Extras 1.4
import QtQuick.Dialogs 1.2

Item {
    id: djiActivate

    signal activateDjiUav(var list)

    property var parentWin

    height: 280
    width: 285
    Rectangle {
        id: rectangleDjiActivate
        height: 285
        color: "#80ffffff"
        radius: 5
        anchors.topMargin: 0
        anchors.fill: parent
        TextField {
            id: textFieldID
            x: 247
            text: "1042403"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 220
            width: 106
            anchors.top: textName.bottom
            anchors.topMargin: 4
            anchors.left: textID.right
            anchors.leftMargin: 6
            placeholderText: qsTr("Text Field")
        }

        TextField {
            id: textFieldKEY
            y: 64
            text: "8cb2ae9a083219473aa648ff54bd99ad8ec6b198953243d661f31b8b9929fa59"
            anchors.bottom: buttonObtainControl.top
            anchors.bottomMargin: 4
            anchors.right: parent.right
            anchors.rightMargin: 8
            height: 25
            anchors.left: textKey.right
            anchors.leftMargin: 6
            placeholderText: qsTr("Text Field")
        }

        Text {
            id: textKey
            y: 66
            width: 50
            height: 25
            text: qsTr("KEY")
            anchors.bottom: buttonObtainControl.top
            anchors.bottomMargin: 4
            anchors.left: parent.left
            anchors.leftMargin: 8
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 15
        }

        Text {
            id: textID
            y: 35
            width: 50
            height: 25
            text: qsTr("UAV ID")
            anchors.bottom: textKey.top
            anchors.bottomMargin: 4
            anchors.left: parent.left
            anchors.leftMargin: 8
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 15
        }

        Button {
            id: buttonActivate
            y: 34
            height: 27
            text: qsTr("Activate")
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.left: textFieldID.right
            anchors.leftMargin: 1
            onClicked:
            {
                var argumentsList = []
                argumentsList.push(textFieldID.text)
                argumentsList.push(textFieldKEY.text)
                activateDjiUav(argumentsList)
            }
        }

        Button {
            id: buttonVersion
            x: 171
            width: 106
            height: 27
            text: qsTr("Version")
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.right: parent.right
            anchors.rightMargin: 8
            onClicked:
            {
                functionButtonVersionClicked()
            }
        }

        TextArea {
            id: textAreaDjiDisplay
            y: 124
            height: 150
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 6
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
        }

        Button {
            id: buttonObtainControl
            x: 8
            y: 91
            width: 269
            height: 27
            text: qsTr("Obtain Control")
            anchors.bottom: textAreaDjiDisplay.top
            anchors.bottomMargin: 4
            onClicked:
            {
                if(buttonObtainControl==="Release Control")
                    functionDjiObatainControl(false)
                else
                    functionDjiObatainControl(true)
            }
        }

        Text {
            id: textName
            x: -2
            width: 130
            height: 25
            text: qsTr("DJI Control Panel")
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 40
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
        }
        ToolButton {
            id: toolButtonClose
            text: "X"
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8
            onClicked:
            {
                djiActivate.visible = false
            }
        }
    }

    function appendDjiApiLogQML(log)
    {
        textAreaDjiDisplay.append(log)
    }

    function functionButtonVersionClicked()
    {
        parentWin.functionButtonVersionClicked()
    }

    function functionDjiObatainControl(state)
    {
        parentWin.functionDjiObatainControl(state)
    }

    function updateObtainControlButton(status)
    {
        buttonObtainControl.text = status
    }

    function updateActivateButton(status)
    {
        buttonActivate.text = status
    }
}
//8cb2aae9a083219473aa648ff54bd99ad8ec6b198953243d661f31b8b9929fa59

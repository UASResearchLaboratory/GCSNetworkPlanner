/*
 * Copyright (c) 2015-2016 Alex Spataru <alex_spataru@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.3


Item {

    id:mainwindow
    objectName: "window"
    property int currentJoystick: 0
    property int currentPitch: 0
    property int currentYaw: 0
    property int currentRoll: 0
    property int currentThorttle: 0
    property double axisn: 0
    property double currentAxis:0
    property double axisvalue: 0
    property int currentBarIndex: 0
    signal  axisCd (double currentAxis,double currentParameter)
    signal  axisValueChanged(double currentAxis,double valueAxis)
    signal  joystickProtocolChanged(int index)
    
    width: 640
    height: 480

    function generateJoystickWidgets (id) {
        /* Clear the joystick indicators */
        axes.model = 0
        povs.model = 0
        buttons.model = 0

        /* Change the current joystick id */
        currentJoystick = id

        /* Get current joystick information & generate indicators */
        if (QJoysticks.joystickExists (id)) {
            //            axes.model = QJoysticks.getNumAxes (id)
            //            povs.model = QJoysticks.getNumPOVs (id)
            //            buttons.model = QJoysticks.getNumButtons (id)
            axes.model = 4
            povs.model =4
            buttons.model =1
        }

        /* Resize window to minimum size */
        //        width = minimumWidth
        //        height = minimumHeight
    }

    ListModel {
    id:listparameters


    ListElement { key: "yaw"; value: 0 }
    ListElement { key: "thorttle"; value: 1 }
    ListElement { key: "roll"; value: 2 }
    ListElement { key: "pitch"; value: 3 }
    ListElement { key: "none"; value: 4}


}






    // Display all the widgets in a vertical layout
    //
    ColumnLayout {
        spacing: 5
        anchors.bottomMargin: -300
        anchors.fill: parent


        //
        // Joystick selector combobox
        //

        RowLayout {
            width: 596

            spacing: 5
            anchors.margins: 10
            anchors.fill: parent
            visible: false


            ComboBox {
                id: joysticks
                Layout.fillWidth: true
                model: QJoysticks.deviceNames
                onCurrentIndexChanged: generateJoystickWidgets (currentIndex)

            }

            ComboBox {
                id: joysticksProtocol
                Layout.maximumHeight: 65523
                Layout.fillHeight: false
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: true
                textRole: "key"
                model: ListModel {
                    id:listprotocols

                    ListElement { key: "MavLink"; value: 0}
                    ListElement { key: "DJI"; value: 1 }


                }
                onCurrentIndexChanged: joystickProtocolChanged(currentIndex)
            }
        }



        //

        //
        // Buttons indicator
        //
        GroupBox {
            id: buttonsgroupbox
            //            title: qsTr ("Buttons")
            //            Layout.fillWidth: true
            //            Layout.fillHeight: true
            visible: false

            GridLayout {
                id:buttonslayout
                rows: 6
                rowSpacing: 5
                columnSpacing: 5
                Layout.fillWidth: true
                Layout.fillHeight: true
                flow: GridLayout.TopToBottom

                //
                // Generate a checkbox for each joystick button
                //
                Repeater {
                    id: buttons
                    delegate:
                        Row {
                        id:rowbuttons
                        CheckBox {
                            id:buttonschkbx
                            enabled: false
                            Layout.fillWidth: true
                            text: qsTr ("Button %1").arg (index)

                            //
                            // React to QJoystick signals
                            //
                            Connections {
                                id:buttonsconnexions
                                target: QJoysticks
                                onButtonChanged: {
                                    if (currentJoystick === js && button === index)
                                        buttonschkbx.checked = QJoysticks.getButton (js, index)
                                }
                            }
                        }

                        ComboBox
                        {   id:buttonsassignements
                            Layout.fillWidth: true
                            //model:MavJoy.deviceNames()


                        }



                    }

                }

            }
        }

        //
        // POVs indicator
        //
        GroupBox {
            //            title: qsTr ("POVs")
            //            Layout.fillWidth: true
            //            Layout.fillHeight: true
            visible: false

            ColumnLayout {
                spacing: 5
                Layout.fillWidth: true
                Layout.fillHeight: true

                //
                // Generate a spinbox for each joystick POV
                //
                Repeater {
                    id: povs
                    delegate: SpinBox {
                        enabled: false
                        from: 0
                        to: 360
                        Layout.fillWidth: true

                        //
                        // React to QJoystick signals
                        //
                        Connections {
                            target: QJoysticks
                            onPovChanged: {
                                if (currentJoystick === js && pov === index)
                                    value = QJoysticks.getPOV (js, index)
                            }
                        }
                    }
                }
            }
        }



        // Axes indicator
        //
        GroupBox {
            //            title: qsTr ("Axes")
            //            Layout.fillWidth: true
            //            Layout.fillHeight: true


            ColumnLayout {
                spacing: 5
                //                Layout.fillWidth: true
                //                Layout.fillHeight: true

                //
                // Generate a progressbar for each joystick axis
                //
                Repeater {
                    id: axes
                    onItemAdded:

                    {
                        console.log(index)
                        currentBarIndex=index
                       //stickParam(index)

                    }


                    delegate:
                        Row

                    {
                        id:rowBar
                        property int outerIndex: index


                        ProgressBar
                        {

                            id: control
                            from: -100
                            to: 100
                            Layout.fillWidth: true


                            value: 0


                            background: Rectangle {
                                implicitWidth: 200
                                implicitHeight: 20
                                color: "#e6e6e6"
                                radius: 17
                            }
                            contentItem: Item {
                                implicitWidth: 200
                                implicitHeight: 19

                                Rectangle {
                                    width: control.visualPosition * parent.width
                                    height: parent.height
                                    radius: 17
                                    color: "#17a81a"
                                }
                            }
                            //                                background: Rectangle {
                            //                                    implicitWidth: 200
                            //                                    implicitHeight: 12
                            //                                    color: "#e6e6e6"
                            //                                    radius: 17
                            //                                }

                            //                                contentItem: Item {
                            //                                    implicitWidth: 200
                            //                                    implicitHeight: 10

                            //                                    Rectangle {
                            //                                        width: progressbar.visualPosition * parent.width
                            //                                        height: parent.height
                            //                                        radius: 16
                            //                                        color: "#17a81a"
                            //                                    }
                            //                                }

                            Behavior on value {NumberAnimation{}}

                            Connections {
                                target: QJoysticks
                                onAxisChanged: {
                                    if (currentJoystick === js && index === axis)
                                        control.value = QJoysticks.getAxis (js, index) * 100
                                    axisvalue=QJoysticks.getAxis (js, index) * 1000
                                    // console.log(axisvalue)

                                    mainwindow.axisValueChanged(index,axisvalue)
                                }
                            }
                        }
                        ComboBox
                        {    id:axesassignements

                            objectName: "axesObject"
                            property int assignementIndex: index


                            // signal comboboxindex (int indexx)


                            textRole: "key"
                            Layout.fillWidth: true
                            model: listparameters




                            Connections {
                                target: axesassignements
                                onActivated: {
                                    currentAxis=rowBar.outerIndex
                                    mainwindow.axisCd(rowBar.outerIndex,index)
                                    listparam()

                                    axismanager(rowBar.outerIndex,index)
                                    //axisNumbersChanged(currentRoll, currentPitch, currentYaw,currentThorttle)
                                    //  comboboxindex(index)
                                    //  console.log("axxx",listparameters.index)

                                    //console.log(currentAxis+"num")
                                    //joystickOptionChanged(index)
                                    // axesassignements.currentIndex=currentBarIndex


                                }

                            }

                        }
                    }
                }
            }
        }





    }


    function axismanager(axisname, comboboxaxe)
    {
        //   currentAxis=axisname
        //        currentOptionJoystick=comboboxaxe

        // console.log ("selecting variable",comboboxaxe)
        switch (comboboxaxe)
        {

        case 0:
            currentYaw=currentAxis
            console.log("axis yaw " + currentYaw)
            break
        case 1:
            currentThorttle=currentAxis
            console.log("axis thorttle " + currentThorttle)
            break

        case 2:
            currentRoll=currentAxis
            console.log("axis roll " + currentRoll)
            console.log("currentvalue " + axisvalue)
            break
        case 3:
            currentPitch=currentAxis
            console.log("axis pitch " + currentPitch)

            break
        case 4:
            console.log("none button")

            break




        }



    }


    function listparam()
    {

        //    if (!listparameters.value )
        //    {   listparameters.append(value)

        //    }

    }
    function stickParam (param)

    {


        switch (param)
        {

        case 0:
            listparameters.remove(1)
            listparameters.remove(2)
            listparameters.remove(3)
            listparameters.set(0,{key: "yaw", value: 0})


            break
        case 1:
            listparameters.remove(0)
            listparameters.remove(2)
            listparameters.remove(3)
            listparameters.set(1,{key: "Throttle", value: 1})
            break

        case 2:
            listparameters.remove(0)
            listparameters.remove(1)
            listparameters.remove(3)
            listparameters.set(2,{key: "Roll", value: 2})
            break
        case 3:
            listparameters.remove(0)
            listparameters.remove(1)
            listparameters.remove(2)
            listparameters.set(3,{key: "Pitch", value: 3})

            break
        case 4:


            break


        }




    }


}


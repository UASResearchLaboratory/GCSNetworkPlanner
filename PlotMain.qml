import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtGraphicalEffects.private 1.0

ApplicationWindow {
    id:windowPlot
    visible: true
    width: 1024
    height: 768
    color: "#ffffff"
    title: qsTr("U.A.V. Parameters Plot")
    //opacity: 0.8
    signal indexplot(var index)

    //    Item {
    //        id: mainView
    //        anchors.fill: parent
    //        PlotView {
    //        }
    //    }
    header: Item {
        id: itemHeader



        ComboBox {
            currentIndex: 0
            id:modesList

            width: 130
            height: 30
            model:    ListModel
            {
                id:changeTypePlot
                ListElement
                {
                    name:"Cellular"
                    value:1
                }
                    ListElement
                    {
                        name:"GyroScope"
                        value:2
                    }
                    ListElement
                    {
                        name:"Accelerometer"
                        value:3
                    }
                    ListElement
                    {
                        name:"Battery"
                        value:4
                    }
                }


            textRole: "name"
            background:Rectangle
            {
                id:backgroundRect
                radius: 17
                border.color:"black" //"#7CC7FF"
                border.width: 2
                color: "#ff842a"
                opacity:0.8
            }
                            onCurrentIndexChanged:
                            {
                                indexplot(currentIndex)
                                console.log("indexchanged" + currentIndex )

                            }


        }}

        SwipeView {
            id: swipeView
            anchors.rightMargin: 0
            anchors.topMargin: 64
            Layout.fillWidth: false
            anchors.bottomMargin: 135
            anchors.leftMargin: 145
            anchors.fill: parent
            //currentIndex: tabBar.currentIndex
            interactive: true

            PlotView {


            }


            //        TabBar
            //        {
            //            id: tabBar2

            //           // currentIndex: swipeView.currentIndex

            //            TabButton {
            //                text: qsTr("plot 1")
            //            }
            //            TabButton {
            //                text: qsTr("Info")
            //            }


            //        }

            //        Page {
            //            Label {
            //                text: qsTr("This is implementation of http://www.qcustomplot.com/index.php/support/forum/172\n" +
            //                           "Adding random data on 500 ms tick to plot")
            //                anchors.centerIn: parent
            //            }
            //        }
        }



        //        TabBar {
        //            id: tabBar
        //            currentIndex: swipeView.currentIndex
        //            TabButton {
        //                text: qsTr("plot 1")
        //            }
        //            TabButton {
        //                text: qsTr("Info")
        //            }
        //        }
    }


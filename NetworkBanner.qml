import QtQuick 2.4
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import QtPositioning 5.9
import QtLocation 5.9
import QtQuick.Controls 2.4


Item {

    id:networkBanner
    property variant networkType:0
    property variant networkQuality:0
    signal setTypeNetworkIndex(var index)
    width: 250
    height: 250
    clip: false

    transformOrigin: Item.Left
    Rectangle
    {
        id:networkRectangle
        border.color:"black" //"#7CC7FF"
        border.width: 2
        color: "#D69C2F"
        anchors.fill: parent
        visible: true
        opacity: 0.7
        radius: 17
        ListModel
        {
            id:parametersListModelnames
        }
        ListModel
        {
            id:parametersListModelvalues
        }
        ListModel
        {
            id:parametersListModelRange
        }
        ListModel
        {
            id:changeTypeNetwork
            ListElement
            {
                name:"AUTO"
                value:"AT^SYSCFGEX=\"00\",3FFFFFFF,1,2,7FFFFFFFFFFFFFFF,,\r\n"
            }
            ListElement
            {
                name:"ONLY LTE"
                value:"AT^SYSCFGEX=\"03\",3FFFFFFF,1,2,7FFFFFFFFFFFFFFF,,\r\n"
            }
            ListElement
            {
                name:"ONLY WCDMA"
                value:"AT^SYSCFGEX=\"02\",3FFFFFFF,1,2,7FFFFFFFFFFFFFFF,,\r\n"
            }
            ListElement
            {
                name:"ONLY GSM"
                value:"AT^SYSCFGEX=\"01\",3FFFFFFF,1,2,7FFFFFFFFFFFFFFF,,\r\n"
            }
        }
        ColumnLayout
        {

            RowLayout
            {
                spacing: 10
                Image
                {
                    id:networkTypeImage
                    sourceSize.width: 45
                    sourceSize.height: 45
                    //opacity: 0.7
                    source: {
                        switch (networkType)
                        {
                        case "LTE":
                            "qrc:/ico/4g.png"
                            break;

                        case "WCDMA":
                            "qrc:/ico/3g.png"
                            break;
                        case "GSM":
                            "qrc:/ico/2g.png"
                            break;
                        default:
                            "qrc:/ico/nosignal.png"
                            break;
                        }
                    }
                }
                Image
                {
                    id:networkQualityImage
                    sourceSize.width: 45
                    sourceSize.height: 45

                    source: {
                        switch (networkQuality)
                        {
                        case "EXCELLENT":
                            "qrc:/ico/5bars.png"
                            break;

                        case "GOOD":
                            "qrc:/ico/4bars.png"
                            break;
                        case "FAIR":
                            "qrc:/ico/3bars.png"
                            break;
                        case "POOR":
                            "qrc:/ico/2bars.png"
                            break;
                        default:
                            "qrc:/ico/nosignal.png"
                            break;

                        }
                    }
                    ComboBox {

                        id:modesList
                        x: 8
                        width: 130
                        height: 30
                        anchors.top: parent.top
                        anchors.topMargin: 8
                        anchors.rightMargin: -138
                        anchors.right: parent.right
                        model:changeTypeNetwork
                        textRole: "name"
                        background:Rectangle
                        {
                            id:backgroundRect
                            radius: 17
                            border.color:"black" //"#7CC7FF"
                            border.width: 2
                            color: "#00539C"

                        }
                        onCurrentIndexChanged:
                        {
                            getTypeNetworkIndex(currentIndex)

                        }

                    }

                }
            }

            RowLayout{
                ListView {
                    spacing:3
                    width: 180; height: 200
                    model: parametersListModelnames
                    delegate: ItemDelegate
                    {
                        background: Rectangle {
                            opacity: 0.9
                            radius: 17
                            border.color:"black"//"#7CC7FF"
                            border.width: 2
                            color: "#FF6F61"
                            anchors.fill: parent


                        }
                        contentItem: Text {
                            opacity: 0.9
                            text:{text:name + ": " }
                            color: "black"
                            font: parent.font
                            elide: Text.ElideRight
                            verticalAlignment: Text.AlignVCenter
                        }
                    }



                }
                ListView {
                    spacing: 3
                    width: 180; height: 200
                    model: parametersListModelvalues
                    delegate: ItemDelegate
                    {
                        x:-110
                        background: Rectangle {

                            opacity: 0.9
                            radius: 17
                            border.color:"black"//"#7CC7FF"
                            border.width: 2
                            color: switch(colour)
                                   {  case "EXCELLENT":
                                          "#3CFE6E"
                                          break;
                                      case "GOOD":
                                          "#FFFF33"
                                          break;
                                      case "FAIR":
                                          "#E8612C"
                                          break;
                                      case "POOR":
                                          "#ED192D"
                                          break;
                                      default:
                                          "#E94B3C"
                                          break;
                                   }
                            anchors.fill: parent


                        }
                        contentItem: Text {
                            opacity: 0.9
                            text:{text:value }
                            color: "black"
                            font: parent.font
                            elide: Text.ElideRight
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }

                ListView {
                    spacing: 3
                    width: 180; height: 200
                    model: parametersListModelRange
                    delegate: ItemDelegate
                    {
                        x:-230
                        background: Rectangle {

                            opacity: 0.9
                            radius: 17
                            border.color:"black"//"#7CC7FF"
                            border.width: 2
                            color: switch(value)
                                   {  case "EXCELLENT":
                                          "#3CFE6E"
                                          break;
                                      case "GOOD":
                                          "#FFFF33"
                                          break;
                                      case "FAIR":
                                          "#E8612C"
                                          break;
                                      case "POOR":
                                          "#ED192D"
                                          break;
                                      default:
                                          "#E94B3C"
                                          break;
                                   }

                            anchors.fill: parent


                        }
                        contentItem: Text {
                            opacity: 0.9
                            text:{text: value }
                            color: "black"
                            font: parent.font
                            elide: Text.ElideRight
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }

        }
    }
    function getNetworkParameters(type,quality)
    {
        networkType=type
        networkQuality=quality
        // console.log("quality checked")
    }
    function getLteParameters(rssi,rsrp,sinr,rsrq)
    {
        parametersListModelnames.set(0,{"name":"RSSI" })
        parametersListModelnames.set(1,{"name":"RSRP"})
        parametersListModelnames.set(2,{"name":"SINR" })
        parametersListModelnames.set(3,{"name":"RSRQ"})
        parametersListModelvalues.set(0,{"value":rssi })
        parametersListModelvalues.set(1,{"value":rsrp })
        parametersListModelvalues.set(2,{"value":sinr })
        parametersListModelvalues.set(3,{"value":rsrq })
        parametersListModelvalues.set(0,{"colour":parametersListModelRange.get(0).value})
        parametersListModelvalues.set(1,{"colour":parametersListModelRange.get(1).value })
        parametersListModelvalues.set(2,{"colour":parametersListModelRange.get(2).value })
        parametersListModelvalues.set(3,{"colour":parametersListModelRange.get(3).value })
    }
    function getWCDMAParameters(rssi,rscp,ecio)
    {
        parametersListModelnames.set(0,{"name":"RSSI" })
        parametersListModelnames.set(1,{"name":"RSCP"})
        parametersListModelnames.set(2,{"name":"ECIO" })
        parametersListModelvalues.set(0,{"value":rssi })
        parametersListModelvalues.set(1,{"value":rscp })
        parametersListModelvalues.set(2,{"value":ecio })
        parametersListModelvalues.set(0,{"colour":parametersListModelRange.get(0).value})
        parametersListModelvalues.set(1,{"colour":parametersListModelRange.get(1).value })
        parametersListModelvalues.set(2,{"colour":parametersListModelRange.get(2).value })
    }
    function getGSMParameters(rssi)
    {
        parametersListModelnames.set(0,{"name":"RSSI" })
        parametersListModelvalues.set(0,{"value":rssi })
       // parametersListModelvalues.set(0,{"colour":parametersListModelRange.get(0).value})
    }
    function getCellularRangeParameters(rssi,rsrp,rsrq,sinr)
    {
        parametersListModelnames.set(0,{"name":"RSSI" })
        parametersListModelnames.set(1,{"name":"RSRP"})
        parametersListModelnames.set(2,{"name":"SINR" })
        parametersListModelnames.set(3,{"name":"RSRQ"})
        parametersListModelRange.set(0,{"value":rssi })
        parametersListModelRange.set(1,{"value":rsrp })
        parametersListModelRange.set(2,{"value":sinr })
        parametersListModelRange.set(3,{"value":rsrq })

    }
    function getTypeNetworkIndex(index)
    {

    setTypeNetworkIndex(changeTypeNetwork.get(index).value)


    }
}





















/*##^## Designer {
    D{i:11;anchors_y:0}D{i:7;anchors_y:0}
}
 ##^##*/

import QtQuick 2.4
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import QtPositioning 5.9
import QtLocation 5.9
import QtQuick.Controls 2.4


Item {

    property double valueLatitude: 39.904459
    property double valueLongitude: 116.406847
    property double maptype: 0
    property double pathlen: 1
    property double mouseLatitude: 0
    property double mouseLongitude:0
    property Rectangle highlightItem : null;
    property double distance: 0
    property double tiltValue:0
    property double anglec: 0
    property variant listWP: []
    property int indexR:0


    signal signalAppenList(var x,var y)
    signal signalCalculateDistance(var lat1,var latn,var long1,var longn)
    signal  distanceCalculated(double distance)
    signal notifyAddDistance()
    property variant locationOslo: QtPositioning.coordinate( 59.93, 10.76)
    property int cellindex:0
    signal clearAntennas()
    property int weatherIndex:0
    property real topleftRLat:0
    property real topleftRLon:0
    property real bottomrightRLat:0
    property real bottomrightRLon:0


    anchors.fill: parent


    PositionSource
    {
        active: true
        onPositionChanged: {}
    }

    Planner {
        id:planner
    }



    Map
    {

        id: map
        anchors.fill: parent
        zoomLevel: 3
        minimumZoomLevel: 2
        maximumZoomLevel:30
        tilt: tiltValue

        plugin: Plugin {
            id: mapboxglPlugin
            name: "mapboxgl"

            PluginParameter { name: "mapboxgl.access_token"; value: "sk.eyJ1IjoiYmF5b3UwMjAiLCJhIjoiY2poNGRqd2dkMHg1MzMzcnlmamtxc2o5cSJ9.Pn_zbpERTx-0-NeEqJEikA" }

            PluginParameter {
                name: "mapboxgl.mapping.items.insert_before"
                value: "aerialway"
            }

            PluginParameter {
                name: "mapboxgl.mapping.use_fbo"
                value: "true  "
            }


        }


        //        MapParameter {
        //            type: "filter"

        //            property var layer: "3d-buildings"
        //            property var filter: [ "==", "extrude", "true" ]
        //        }

        //                MapParameter {
        //                    type: "paint"

        //                    property var layer: "3d-buildings"
        //                    property var fillExtrusionColor: "#00617f"
        //                    property var fillExtrusionOpacity: .6
        //                    property var fillExtrusionHeight: { return { type: "identity", property: "height" } }
        //                    property var fillExtrusionBase: { return { type: "identity", property: "min_height" } }
        //                }

        copyrightsVisible: true
        center
        {
            latitude: valueLatitude
            longitude: valueLongitude
        }

        gesture.enabled: true
        activeMapType: supportedMapTypes[0]
        ListModel
        {
            id:meteoModel
        }

        ListModel
        {
            id: sampleModel
        }

        MapPolyline {
            id:polylinemap
            line.width: 2
            line.color: 'blue'




        }




        MapRectangle {
            id:rectangleMap
            color: 'green'
            border.width: 6
            border.color: 'blue'
            opacity: 0.1
            topLeft
            {
                latitude:topleftRLat
                longitude: topleftRLon

            }
            bottomRight
            {
                latitude:bottomrightRLat
                longitude:bottomrightRLon

            }
        }


       

       

        MapItemView {
            id: mapItemView
            model : sampleModel

            delegate:

                MapQuickItem
            {

                id:delegate_quad
                anchorPoint.x: delegate_quad.width * 0.5
                anchorPoint.y: delegate_quad.height * 0.5
                zoomLevel:zoomLevel.toFixed()

                sourceItem: Image
                {

                    id: delegate_quad_img
                    //objectName: uav_name
                    sourceSize.width: 40
                    sourceSize.height: 40
                    source:  "qrc:/ico/marker.gif"
                    transform: Rotation
                    {
                        id: delegate_quad_img_rot
                        origin.x: delegate_quad_img.width/2
                        origin.y: delegate_quad_img.height/2
                        //angle: heading
                    }
                }

                coordinate : QtPositioning.coordinate(latitude,longitude)



            }

        }
        MapItemView
        {

            id:mapitemcircle
            model:sampleModel

            delegate:

                MapCircle {
                id:circleradius
                color:radio
                center {
                    latitude: latitude
                    longitude: longitude

                }
                radius: range
                border.color: 'black'
                border.width: 10
                opacity: 0.1

            }




        }


        MapQuickItem
        {
            id:main_quadcopter
            coordinate: QtPositioning.coordinate(valueLatitude,valueLongitude)
            anchorPoint.x: main_quadcopter.width * 0.5
            anchorPoint.y: main_quadcopter.height * 0.5
            zoomLevel:zoomLevel.toFixed()
            sourceItem: Image
            {
                id: quadcopter_image;
                sourceSize.width: 40
                sourceSize.height: 40
                source: "qrc:/ico/drone_i.ico"
                transform: Rotation
                {
                    id: quadcopter_image_rot
                    origin.x: quadcopter_image.width/2
                    origin.y: quadcopter_image.height/2
                    angle: 0
                }
                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked:
                    {
                        console.log("Main Quad clicked")
                    }
                }
            }
        }
        MouseArea
        {
            anchors.fill: parent
            MouseArea
            {
                id: mouseArea
                anchors.fill: parent
                drag.target: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                property variant iconObj
                property int startX
                property int startY
                onPressed:  {


                }

                onPressAndHold: {

                    if(mouse.button & Qt.RightButton)
                    {

                    }


                }
                onDoubleClicked:  {

                    if(mouse.button & Qt.RightButton)
                    {

                    }
                }

                onClicked:
                {

                    if(mouse.button & Qt.LeftButton)
                    {

                        //                                startX = mouseX
                        //                                startY = mouseY
                        //                                var iconComp = Qt.createComponent("qrc:/Planner.qml");
                        //                                iconObj = iconComp.createObject(parent);
                        //                                iconObj.x = mouseX - iconObj.width/4
                        //                                iconObj.y = mouseY - iconObj.height/4

                        signalAppenList(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude,
                                        map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude)

                        //                        bottomrightRLat=(map.toCoordinate(Qt.point(mouseArea.mouseX,mouseArea.mouseY)).latitude)
                        //                        bottomrightRLon=(map.toCoordinate(Qt.point(mouseArea.mouseX,mouseArea.mouseY)).longitude)
                        console.log("bot lat "+ bottomrightRLat+" bot lon "+ bottomrightRLon)

                        // console.log('Path length = '+ (polylinemap.pathLength(pathlen)))
                        //highlightItem = highlightComponent.createObject (selectArea, { "x" : mouse.x  });
                        updatePointsMap()
                        cellindex=cellbase.getRows()

                        //delayweather(weatherParams)
                        delay(1000,weatherParams)


                        // weatherTimer.start()




                        console.log(cellindex)
                        //  console.log("weather cities: "+ weatherIndex)
                        for (var i=0;i<cellindex-1;i++)
                        {
                            sampleModel.append({"latitude":cellbase.getLatitude(i),"longitude":cellbase.getLongitude(i),"range":cellbase.getRange(i),"radio":cellbase.getRadio(i)})

                            if(sampleModel.get(i).radio==="LTE")
                            {

                                sampleModel.set(i,{"radio":'red'})

                            }
                            else if (sampleModel.get(i).radio==="UMTS")
                            {

                                sampleModel.set(i,{"radio":'green'})
                            }
                            else if (sampleModel.get(i).radio==="GSM")
                            {

                                sampleModel.set(i,{"radio":'blue'})
                            }
                            else {
                                sampleModel.set(i,{"radio":'white'})
                            }

                        }





                    }

                    if(mouse.button & Qt.RightButton)

                    {   sampleModel.clear()
                        meteoModel.clear()
                        clearAntennas()
                        weather.clearWeatherSize()
                        //weatherTimer.stop()




                        //                        topleftRLat=(map.toCoordinate(Qt.point(mouseArea.mouseX,mouseArea.mouseY)).latitude)
                        //                        topleftRLon=(map.toCoordinate(Qt.point(mouseArea.mouseX,mouseArea.mouseY)).longitude)
                        console.log("top lat "+topleftRLat+" top lon "+topleftRLon)

                        // console.log(cellindex)
                        polylinemap.removeCoordinate(polylinemap.pathLength()-1)
                        //libraryModel.remove(polylinemap.pathLength(),1)
                    }


                }






                //                ColumnLayout {
                //                    id: columnLayoutMapType
                //                    x: 0
                //                    y: 177
                //                    width: 57
                //                    height: 106

                //                    ToolButton {
                //                        id: toolButtonTypeMapUp
                //                        width: 50
                //                        height: 50
                //                        iconSource: "qrc:/ico/plus.ico"
                //                        iconName: qsTr("plus")
                //                        tooltip: ""
                //                        onClicked:
                //                        {
                //                            maptype=maptype +1;
                //                        }

                //                    }

                //                    ToolButton {
                //                        id: toolButtonTypeMapDown
                //                        width: 50
                //                        height: 50
                //                        iconSource: "qrc:/ico/minus.ico"
                //                        iconName: "IconDown"
                //                        tooltip: ""
                //                        onClicked:
                //                        {
                //                            maptype=maptype - 1;
                //                        }
                //                    }
                //                }

            }
        }
        onZoomLevelChanged:
        {
            sliderHorizontalZoom.value = zoomLevel;
        }
    }
    RowLayout
    {
        id: rowLayoutZoomBar
        x: 361
        y: 445
        width: 499
        height: 24
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8

        ToolButton
        {
            id: toolButtonZoomMapOut
            text: "-"
            // tooltip: ""
            onClicked:
            {
                sliderHorizontalZoom.value = sliderHorizontalZoom.value - 0.5;
                sliderHorizontalZoom
            }
        }

        Slider
        {
            id: sliderHorizontalZoom
            x: 0
            //tickmarksEnabled: false
            stepSize: 0.2
            from: 2
            value: 3
            to: 20
            onValueChanged:
            {
                map.zoomLevel =value;
            }
        }


        ToolButton
        {
            id: toolButtonZommMapIn
            x: 200
            text: "+"
            onClicked:
            {
                sliderHorizontalZoom.value = sliderHorizontalZoom.value + 0.5;
            }
        }
        Image
        {
            id: centerImage

            width: 27
            height: 27
            fillMode: Image.PreserveAspectFit
            sourceSize.height: 27
            sourceSize.width: 27
            source: "qrc:/ico/center.ico"
            MouseArea
            {
                id: mouseareaCenterImage
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.right: parent.right
                hoverEnabled: true
                onEntered:
                {
                    centerImage.source = "qrc:/ico/centeri.ico";
                }
                onExited:
                {
                    centerImage.source = "qrc:/ico/center.ico";
                }
                onClicked: {
                    map.center = main_quadcopter.coordinate
                }
            }
        }

        Slider {
            id: sliderHorizontalTilt
            x: 300
            y: 0

            from: 0
            to: 60
            Layout.preferredWidth: -1
            stepSize: 0.2
            value: 4
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            onValueChanged: {
                map.tilt=value
            }
        }
    }

    function updateUavGPS(xc,yc)
    {
        main_quadcopter.coordinate = QtPositioning.coordinate(xc,yc)
        if(xc === 0) valueLatitude = 39.904459; else valueLatitude = xc;
        if(yc === 0) valueLongitude = 116.406847; else valueLongitude = yc;

        //console.log("UavMap.updateUavGPS(xc,yc)")
    }

    function updatePointsMap()

    {
        distance=0
        var pathlength=polylinemap.pathLength();
        for (var i=0;i< pathlength;i++)
        {
            var lat1,long1,latn,longn;
            var coor1=0
            coor1=polylinemap.coordinateAt(i);
            var coorn=0
            coorn=polylinemap.coordinateAt(i+1);
            var distancee=coor1.distanceTo(coorn);
            //console.log(pathlength + "path number")
            //console.log(distancee+"  distance");
            //          lat1=coor1.latitude;
            //          long1=coor1.longitude;
            //        latn=coorn.latitude;
            //        longn=coorn.longitude
            //        signalCalculateDistance(lat1,latn,long1,longn)
            distance=distancee+distance
        }
        //console.log(distance + " momo d")
        distanceCalculated(distance)

    }

    function angleRefresh(xca){
        quadcopter_image_rot.angle=xca*180/Math.PI


    }

    function polylineAdd(x,y)
    {


        polylinemap.addCoordinate(QtPositioning.coordinate(x,y))


        //sampleModel.set(i,{"latitude":x,"longitude":y})}
        sampleModel.append({"latitude":x,"longitude":y})





        //        for(var i=0;i<=polylinemap.pathLength();i++)
        //        {
        //        listWP[i]= listWP.push(x)
        //        console.log("append WP "+ listWP)
        //        }


    }

    function polylineRemove(row)
    {
        polylinemap.removeCoordinate(row)
        indexR=row

    }


}























































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:5;autoSize:true;height:480;width:640}
D{i:51;anchors_height:27;anchors_width:27;anchors_x:-40}
}
 ##^##*/

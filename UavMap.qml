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
            //        PluginParameter { name: "mapbox.map_id"; value: "styles/bayou020/cj9v21si54gk52st7ivz9ywui" }
           // PluginParameter { name: "mapboxgl.mapping.additional_style_urls"; value: "mapbox://styles/bayou020/cjh8omavq0xt12rp6qlxrlu3j" }
            // PluginParameter { name: "mapboxgl.mapping.additional_style_urls"; value: "mapbox://styles/bayou020/cjh8oqiud72i62rp9me2sj3gf" }
           //PluginParameter { name: "mapboxgl.mapping.additional_style_urls"; value: "mapbox://styles/bayou020/cjh8oqaqj6xki2rqlffwawuaz" }
            // PluginParameter { name: "mapboxgl.mapping.additional_style_urls"; value: "mapbox://styles/bayou020/cjh8oq1yt72hr2rp99n8mdbfn" }


            PluginParameter {
                name: "mapboxgl.mapping.items.insert_before"
                value: "aerialway"
            }

            PluginParameter {
                name: "mapboxgl.mapping.use_fbo"
                value: "true  "
            }


        }




        //                        MapParameter {
        //                            id: source
        //                            type: "source"

        //                            property var name: "weatherSource"
        //                          //  property var tiles:  "https://tile.openweathermap.org/map/temp_new/{z}/{x}/{y}.png?appid=375bc10f6f6da05c872d85c9ef9f52fe"                //"https://tile.openweathermap.org/map/clouds_new/{z}/{x}/{y}.png?appid=80f3bdceecbd21d53f2893054a176915"
        //                            property var sourceType: "raster"
        //                              property var url:"https://tile.openweathermap.org/map/temp_new/{z}/{x}/{y}.png?bbox={bbox-epsg-3857}&format=image/png&service=WMS&version=1.1.1&appid=80f3bdceecbd21d53f2893054a176915"

        ////                            property var tileSize: 256
        ////                            property var minzoom: 4.0
        ////                            property var maxzoom: 20.0

        //                        }


        //        MapParameter {
        //            type: "layer"

        //            property var name: "wind_weather"
        //            property var layerType: "raster"
        //            property var source: "weatherSource"

        //        }


        /*{type: raster,  tiles: ["https://tile.openweathermap.org/map/temp_new/{z}/{x}/{y}.png?appid=874718354841f0e0250b4b06a05a971e"],
                                            tileSize: 256 }*/
        //                                        property var minzoom: 1.0
        //                                        property var maxzoom: 20.0






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

        copyrightsVisible: false
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


        MapItemView
        {
            id:meteoText
            model:meteoModel
            delegate: MapQuickItem
            {
                id:meteotextDelegate

                zoomLevel: zoomLevel.toFixed()

                sourceItem: Text
                {
                    text:qsTr("      temp: "+cityActTemp)
                    font.pixelSize:14

                }
                anchors.fill:bottom.parent


                coordinate : QtPositioning.coordinate(cityLat,cityLon)
            }
        }

        MapItemView
        {
            id:meteoView
            model:meteoModel
            delegate:
                MapQuickItem
            {
                id:delegateWeather
                anchorPoint.x:delegateWeather.width *0.5
                anchorPoint.y:delegateWeather.height *0.5
                zoomLevel: zoomLevel.toFixed()

                sourceItem: Image
                {
                    id:delegate_weather_img
                    sourceSize.width: 40
                    sourceSize.height: 40
                    source:{


                        switch (cityIcon)
                        {

                        case "01d":
                        case "01n":
                            "qrc:/ico/weather-sunny.png"
                            break;
                        case "02d":
                        case "02n":
                            "qrc:/ico/weather-sunny-very-few-clouds.png"
                            break;
                        case "03d":
                        case "03n":
                            "qrc:/ico/weather-few-clouds.png"
                            break;
                        case "04d":
                        case "04n":
                            "qrc:/ico/weather-overcast.png"
                            break;
                        case "09d":
                        case "09n":
                            "qrc:/ico/weather-showers.png"
                            break;
                        case "10d":
                        case "10n":
                            "qrc:/ico/weather-showers.png"
                            break;
                        case "11d":
                        case "11n":
                            "qrc:/ico/weather-thundershower.png"
                            break;
                        case "13d":
                        case "13n":
                            "qrc:/ico/weather-snow.png"
                            break;
                        case "50d":
                        case "50n":
                            "qrc:/ico/weather-fog.png"
                            break;
                        default:
                            "qrc:/ico/weather-fog.png"
                        }

                    }


                    // smooth:true



                    MouseArea
                    {
                        id:weatherMouse
                        anchors.fill: parent
                        drag.target: parent
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        onEntered:
                        {


                        }


                    }
                }



                coordinate : QtPositioning.coordinate(cityLat,cityLon)
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


        MapItemView
        {

            id:antennaInformations
            model:sampleModel

            delegate:Item
            {
                id:itemAntenna
                height:100
                width:100


            }




        }

        TableView
        {
            id:tableView
            model: ListModel
            {
                id: tableViewModel
            }
            visible: false
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

    function cellRow (row)
    {

        console.log(row)
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


    function weatherParams()

    {


        weatherIndex=weather.getWeatherSize();
        console.log(weatherIndex + "index");
        for (var j=0;j<weatherIndex;j++)

        {
            //console.log(j+ "weather index")
            meteoModel.append({"cityName":weather.getCityName(j),"cityLat":weather.getCityLat(j),"cityLon":weather.getCityLon(j),"cityIcon":weather.getWeatherIcon(j),"cityActTemp":weather.getCityActualTemp(j)})

            //console.log("appended "+j)
            console.log( meteoModel.get(j).cityName+" city " + j+ "  "+

                        + meteoModel.get(j).cityLat +" lat "+ meteoModel.get(j).cityLon+" Lon "+ meteoModel.get(j).cityIcon+" Icon")



        }



    }




    //    function cellInformation(latitude,longitude,range)
    //    {

    //

    //    }

}























































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:5;autoSize:true;height:480;width:640}
D{i:51;anchors_height:27;anchors_width:27;anchors_x:-40}
}
 ##^##*/

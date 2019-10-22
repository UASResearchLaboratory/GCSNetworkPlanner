import QtQuick 2.4
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import QtPositioning 5.3
import QtLocation 5.9
import QtGraphicalEffects 1.0


Item {
    id:planner
    width: 200
    height: 300



    property double count: 0
    property double mouseLatitude: 0
    property double mouseLongitude: 0
    property double libRow: 0
    property double distance: 0
    property double distanceT: 0
    signal polylineCoordinates(double x, double y)
    signal polylineRemove(int row)
    property var listWpLatitude :[]
    property var listWpLongitude :[]
    signal sendSignalLatitude(var latitude)
    signal sendSignalLongitude(var longitude)
    signal distanceUpdate()
    signal locatSend (var position)






    ListModel {
        id: libraryModel


    }


    TableView {/*
        width: 200
        height: 250*/
        anchors.fill: parent
        highlightOnFocus: false
        headerVisible: true
        frameVisible: true
        alternatingRowColors: true
        backgroundVisible: true


        TableViewColumn {
            role: "latitude"
            title: "Latitude"
            width: 100
        }
        TableViewColumn {
            role: "longitude"
            title: "Longitude"
            width: 100
        }
        model: libraryModel

        onClicked: {
               libRow=row
            console.log(libRow + "row")


        }
        //        TableViewStyle {
        //            backgroundColor:"blue"
        //        }
    }

    RowLayout {
        id: columnLayout
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: -82
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -40


        Button {
            id: removebutton
            text: qsTr("Remove")
            onClicked: {
                libraryModel.remove(libRow,1)
                polylineRemove(libRow)
                removeWPS()
                //removeDistance(libRow)
                distanceUpdate()

            }
        }
        Button {
            id: setbutton
            text: qsTr("Set Mission")
            onClicked: {
               sendSignalLatitude(listWpLatitude)
               sendSignalLongitude(listWpLongitude)

            }
        }

    }
    Text {
        id: distanceText
        text: Math.round(distanceT/1000).toFixed(2)  + "km"
        anchors.horizontalCenterOffset: -12
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -100
        anchors.left: parent.center

        font.pixelSize: 48
    }





    function addCoordinate(x,y) {

        if( visible === true )
        {
        libraryModel.append({"latitude":x,"longitude":y})
        polylineCoordinates(x,y)
            sendWPS()
         //polylinemap.addCoordinate(QtPositioning.coordinate(x,y))
        }

  }

    function sendWPS() {
        var listWPLatitude=new Array(0);
        var listWPLongitude=new Array(0);
        for (var i=0;i<libraryModel.count;i++)
        {
           listWPLatitude.push(libraryModel.get(i).latitude)
           listWPLongitude.push(libraryModel.get(i).longitude)
           listWpLatitude=listWPLatitude
           listWpLongitude=listWPLongitude
        }
    }

    function removeWPS()
    {
        listWpLatitude.splice(libRow,1)
        listWpLongitude.splice(libRow,1)
    }

    function receiveDistance(distancee)
    {
        distanceT=distancee
    }


//    function calculateDistance(lat1,lat2,lon1,lon2)
//    {

//        var i=0
//        var R = 6371e3; // metres
//        var φ1 = lat1*Math.PI/180;
//        var φ2 = lat2*Math.PI/180;
//        var Δφ = (lat2-lat1)*Math.PI/180;
//        var Δλ = (lon2-lon1)*Math.PI/180;

//        var a = Math.sin(Δφ/2) * Math.sin(Δφ/2) +
//                Math.cos(φ1) * Math.cos(φ2) *
//                Math.sin(Δλ/2) * Math.sin(Δλ/2);
//        var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));

//        var d=0
//            d= R * c;

//       // console.log(d + "m  final distance");
////        console.log(distance/1000.00 + "Km  final distance");
//        //distance=d+distance ||0;
//        distance=d ||0
//        //distance=Math.round(d).toFixed(2) ||0
//        console.log(distance +" distanceww")
////        distanceT=distance+distanceT

//        distanceT=distance

//    }


//    function handleAddDistance()
//    {
//        addDistance(libraryModel.count-1)
//    }

//    function addDistance(row)
//    {
//        var lat1,long1,lat2,long2
//        lat2=libraryModel.get(row).latitude
//        long2=libraryModel.get(row).longitude
//        lat1=libraryModel.get(row-1).latitude
//        long1=libraryModel.get(row-1).longitude
//        calculateDistance(lat1,lat2,long1,long2)
//        distanceT=distanceT+distance
//        console.log(row)
//    }

//function removeDistance(row)
//    {
//        var lat1,long1,lat2,long2
//        if (row===0)
//        {
//            lat2=libraryModel.get(row+1).latitude
//            long2=libraryModel.get(row+1).longitude
//            lat1=libraryModel.get(row).latitude
//            long1=libraryModel.get(row).longitude
//            calculateDistance(lat1,lat2,long1,long2)
//            distanceT=distanceT-distance
//            console.log(row)
//        }
//        else
//        {
//        lat2=libraryModel.get(row).latitude
//        long2=libraryModel.get(row).longitude
//        lat1=libraryModel.get(row-1).latitude
//        long1=libraryModel.get(row-1).longitude
//        calculateDistance(lat1,lat2,long1,long2)
//        distanceT=distanceT-distance
//        }
//     console.log(row)

//    }

}

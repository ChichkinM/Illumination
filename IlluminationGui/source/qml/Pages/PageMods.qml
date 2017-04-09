import QtQuick 2.0

Item {    
    Rectangle {
        anchors.fill: parent
        color: "darkblue"
    }

    //    ListModel {
    //        id: listModel

    //        ListElement {
    //            title: "Цвет"; clr: "green"
    //        }
    //        ListElement {
    //            title: "Переливания"; clr: "red"
    //        }
    //        ListElement {
    //            title: "Музыка"; clr: "orange"
    //        }
    //    }

    //    GridView {
    //        width: parent.width
    //        anchors.fill: parent
    //        cellWidth: 100
    //        cellHeight: 100

    //        focus: true
    //        model: listModel

    //        delegate: Item {
    //            width: 100
    //            height: 100

    //            Rectangle {
    //                width: parent.width
    //                height: parent.height
    //                color: clr
    //            }

    //            Text {
    //                text: title
    //                color: "white"
    //                font.pointSize: 12
    //                anchors.horizontalCenter: parent.horizontalCenter
    //            }

//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: {
//                        console.log(/*index*/"click");
//                        loader.setSource("qrc:/Pages/PageStart.qml");
//                    }
//                }

    //        }
    //    }
}

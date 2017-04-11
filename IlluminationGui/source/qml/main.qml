import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import "Components"

Window {
    id: w
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    RowLayout {
        id: rowLayout
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5

        Button {
            text: qsTr("Фрагмент 1")
        }
    }

    Loader {
        id: loader

        anchors.top: rowLayout.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 5

        source: "qrc:/Pages/PageStart.qml"
//        source: "qrc:/Pages/PageMods.qml"
    }


    Connections {
        target: loader.item

        onPageExit: loader.source = "qrc:/Pages/PageMods.qml";
    }
}

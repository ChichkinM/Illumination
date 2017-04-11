import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    id: tab
    color: "lightgray"
    Layout.fillWidth: true
    Layout.fillHeight: true

    signal activated()
    function disactivate()
    {
        active = false;
        color = "lightgray";
    }

    property int index: 0
    property bool active: false

    MouseArea {
        anchors.fill: parent;
        onClicked: {
            active = true;
            tab.color = "lightgreen";

            activated();
        }
    }
}

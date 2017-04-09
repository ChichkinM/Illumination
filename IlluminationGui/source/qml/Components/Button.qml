import QtQuick 2.0

Rectangle {
    id: button

    property bool checked: false
    property alias text : buttonText.text


    Accessible.name: text
    Accessible.description: "This button does " + text
    Accessible.role: Accessible.Button
    Accessible.onPressAction: button.clicked();

    signal clicked

    width: buttonText.width + 20
    height: 30
    color: "lightgray"

    radius: 5
    antialiasing: true

    Text {
        id: buttonText
        text: parent.description
        font.family: "Monotype Corsiva"
        font.pointSize: 14
        anchors.centerIn: parent
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: parent.clicked();
    }
}

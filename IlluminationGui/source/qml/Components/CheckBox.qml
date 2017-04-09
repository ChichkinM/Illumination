import QtQuick 2.0

Rectangle {
    id: checkBox

    property alias text: checkBoxText.text

    signal setColor(string color, real duration)
    signal setColorFinished()

    color: "transparent"
    width: title.width
    height: 30
    radius: 10

    onSetColor: {
        colorAnimation.to = color;
        colorAnimation.duration = duration;
        colorAnimation.start();
    }

    Text {
        id: checkBoxText
        anchors.centerIn: parent

        color: "white"
        font.pointSize: 16
    }

    PropertyAnimation {
        id: colorAnimation

        target: checkBoxText
        property: "color"
        duration: 300

        onRunningChanged: {
            if(!running)
                setColorFinished()
        }
    }
}

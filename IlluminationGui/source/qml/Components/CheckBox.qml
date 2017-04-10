import QtQuick 2.0

Rectangle {
    id: checkBox

    property alias text: checkBoxText.text

    color: "transparent"
    width: title.width
    height: 30
    radius: 10

    QtObject {
        id: internal

        property bool preReady: false
        property bool ready: false
        property bool tryInit: false
    }

    signal setColorFinished();

    function setState(state, duration) {
        internal.preReady = state;

        if (state)
            setColor("green", duration);
        else
            setColor("red", duration);
    }

    function setColor(color, duration) {
        colorAnimation.to = color;
        colorAnimation.duration = duration;
        colorAnimation.start();
    }

    function isReady() { return internal.ready; }
    function isTryInit() {return internal.tryInit; }


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

        onRunningChanged: {
            if(!running)
            {
                internal.tryInit = true;
                internal.ready = internal.preReady;
                setColorFinished();
            }
        }
    }
}

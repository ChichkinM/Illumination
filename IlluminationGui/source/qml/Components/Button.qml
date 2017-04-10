import QtQuick 2.0

Rectangle {
    id: button

    property bool checked: false
    property alias text : buttonText.text

    QtObject {
        id: internal

        property bool preShow: true
        property bool show: true
    }

    Accessible.name: text
    Accessible.description: "This button does " + text
    Accessible.role: Accessible.Button
    Accessible.onPressAction: button.clicked();

    signal clicked

    width: buttonText.width + 20
    height: 30
    color: "orange"

    radius: 5
    antialiasing: true

    function setShow(state, duration)
    {
        if(state !== internal.show)
        {
            internal.preShow = state;
            opacityAnimation.duration = duration;

            if(state)
                opacityAnimation.to = 1;
            else
                opacityAnimation.to = 0;

            opacityAnimation.start();
        }
    }

    PropertyAnimation {
        id: opacityAnimation

        target: button
        property: "opacity"

        onRunningChanged: {
            if(!running)
                internal.show = internal.preShow;
        }
    }

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
        onClicked: {
            if (internal.show && !opacityAnimation.running)
                button.clicked();
        }
    }
}

import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0
import "../Components"

Item {
    id: pageStart

//    Rectangle {
//        id: background
//        anchors.fill: parent

//        color: "#444444"
//    }

    signal pageExit()

    Component.onCompleted: mainWindow.btnNetwork_clicked();

    Connections {
        target: mainWindow
        onNetworkStateChange: {
            switch(stateNet)
            {
            case 3:
                cbDrvr.setColor("green", 300);
                cbLed.setColor("green", 300);
                break;

            case 2:
                cbDrvr.setColor("orange", 300);
                break;

            default:
                cbDrvr.setColor("red", 300);
            }
        }
    }

    Connections {
        target: cbLed
        onSetColorFinished: pageStart.pageExit()
    }

    GridLayout {
        anchors.centerIn: parent
        columns: 1
        rows: 3

        Text {
            id: title
            text: "Подключаемся..."
            font.pointSize: 20
        }

        CheckBox {
            id: cbDrvr

            text: "Драйвер"
        }

        CheckBox {
            id: cbLed

            text: "Светодиодная лента"
        }
    }
}



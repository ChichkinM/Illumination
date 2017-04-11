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

    function checkComponentsState()
    {
        if(cbDrvr.isReady() && cbLed.isReady())
        {
            pageExitAnimation.to = 0;
            pageExitAnimation.duration = 1000;
            pageExitAnimation.start();
        }
        else if(cbDrvr.isTryInit() && cbLed.isTryInit())
        {
            btnSkip.setShow(true, 1000);
            btnRefresh.setShow(true, 1000);
            console.log("show skip");
        }
    }

    Component.onCompleted: {
        btnSkip.setShow(false, 0);
        btnRefresh.setShow(false, 0);
        mainWindow.btnNetwork_clicked();
    }

    Connections {
        target: mainWindow

        onNetworkStateConnecting: cbDrvr.setColor("orange", 300);
        onNetworkStateConnected:  cbDrvr.setState(true, 300);
        onNetworkStateDisconnected: cbDrvr.setState(false, 300);

        onLedStateConnected: cbLed.setState(true, 300);
        onLedStateDisconnected: cbLed.setState(false, 300);
    }

    PropertyAnimation {
        id: pageExitAnimation

        target: pageStart
        property: "opacity"
        to: 0
        duration: 300

        onRunningChanged: {
            if(!running)
                pageStart.pageExit();
        }
    }

    ColumnLayout {
        id: grid
        anchors.centerIn: parent

        Text {
            id: title
            text: "Подключаемся..."
            font.pointSize: 20
        }

        //TODO может есть способ сделать список объектов
        CheckBox {
            id: cbDrvr
            text: "Драйвер"

            onSetColorFinished: pageStart.checkComponentsState();
        }

        CheckBox {
            id: cbLed
            text: "Светодиодная лента"

            onSetColorFinished: pageStart.checkComponentsState();
        }
    }

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30

        Button {
            id: btnRefresh

            text: "Обновить";

            onClicked: {
                cbDrvr.setColor("orange", 300);
                cbLed.setColor("orange", 300);

                mainWindow.btnRefresh_clicked();
            }
        }

        Button {
            id: btnSkip

            text: "Все равно начать >>";

            onClicked: pageExitAnimation.start();
        }
    }
}

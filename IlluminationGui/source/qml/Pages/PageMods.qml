import QtQuick 2.0
import QtQuick.Layouts 1.1
import "../Components"

Item {    
    //    Rectangle {
    //        anchors.fill: parent
    //        color: "darkblue"
    //    }

    RowLayout {
        id: rowLayout
        anchors.fill: parent

        function changeMode(sender)
        {
            for(var i = 0; i < rowLayout.children.length; i++)
                if(sender !== rowLayout.children[i])
                    rowLayout.children[i].disactivate();
        }

        Tab {
            id: tab1

            Layout.fillWidth: true
            Layout.fillHeight: true

            onActivated: {
                rowLayout.changeMode(tab1);
            }
        }

        Tab {
            id: tab2

            Layout.fillWidth: true
            Layout.fillHeight: true

            onActivated: {
                rowLayout.changeMode(tab2);
            }
        }

        Tab {
            id: tab3

            Layout.fillWidth: true
            Layout.fillHeight: true

            onActivated: {
                rowLayout.changeMode(tab3);
            }
        }

        function setMode(sender)
        {
            sender.active = true;
        }
    }
}

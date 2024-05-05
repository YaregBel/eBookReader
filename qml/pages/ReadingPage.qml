import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    SilicaFlickable {
        objectName: "flickable"
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: page.width
            spacing: Theme.paddingLarge

            PageHeader {
                objectName: "pageHeader"
                title: qsTr("ZV___Приятного чтения___ZV")
            }
            Text{
                text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua"
                wrapMode: Text.WordWrap
                width: parent.width
                color: "#FFFFFF";


            }

        }
    }
}

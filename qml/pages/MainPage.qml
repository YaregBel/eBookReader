import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.omp.SimpleBLE 1.0

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
                title: qsTr("freakyReader")

                extraContent.children: [
                    IconButton {
                        objectName: "aboutButton"
                        icon.source: "image://theme/icon-m-about"
                        anchors.verticalCenter: parent.verticalCenter

                        onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
                    }
                ]
            }

            Label {
                id: labelM
                x: Theme.horizontalPageMargin
                text: qsTr("Ниже будет кнопка")
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }

            Button {
                objectName: "findButton"
                text: "Изменить"
                onClicked: Class1.printPath;

            }

            Label
            {
                    text: Class1.getTextSize();
                    font.pixelSize: 15;
                    font.family: "Verdana"
            }


        }
    }
}

import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.omp.SimpleBLE 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    Class1{id: class1}

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
                objectName: "button1"
                text: "Кнопка 1"
                onClicked: class1.changeValue(1);
            }
            Button {
                objectName: "button2"
                text: "Кнопка 2"
                onClicked: class1.changeValue(2);
            }
            Button {
                objectName: "button3"
                text: "Кнопка 3"
                onClicked: class1.changeValue(3);
            }

            Label {
                id: lButOper
                x: Theme.horizontalPageMargin
                text: qsTr("После нажатия на кнопку, здесь будет отображаться переданное значение")
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeMedium

                Connections {
                    target: class1
                    // Form like this "on + ValueChange"
                    // (first letter of method must be capitalized)
                    onValueChanged: lButOper.text = s;
                }
            }


        }
    }
}

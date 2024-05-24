import QtQuick 2.2
import Sailfish.Silica 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All
    backgroundColor: "dark green"

    SilicaListView {
        id: mainPageList
        anchors.fill: parent
        header: PageHeader { title: qsTr("Список книг") }

        PullDownMenu {
            MenuLabel { text: qsTr("Меню приложения") }
            MenuItem { text: qsTr("Пункт меню 1") }
            MenuItem { text: qsTr("Пункт меню 2") }
            MenuLabel { text: qsTr("Подраздел") }
            MenuItem { text: qsTr("Пункт меню 3") }
        }

        delegate: ListItem {
            width: parent.width
            objectName: "listItemBook"
            contentHeight: 200

            Row {
                height: 120
                anchors.fill: parent
                anchors.margins: Theme.horizontalPageMargin
                spacing: 5

                Rectangle {
                    color: 'red'
                    width: 60
                    height: 60
                }

                Column {
                    spacing: 2
                    width: parent.width - Theme.horizontalPageMargin * 2
                    height: contentHeight + (contextMenu.visible ? contextMenu.height : 0)
                    Label {
                        text: qsTr("Книга %1").arg(model.index + 1)
                        color: Theme.primaryColor
                        font.bold: true
                    }
                    Label {
                        text: qsTr("Автор %1").arg(model.index + 1)
                        color: Theme.secondaryColor
                    }
                    ProgressBar {
                        minimumValue: 0
                        maximumValue: 100
                        value: 50
                        width: parent.width - 60 - Theme.horizontalPageMargin * 2
                    }
                }
            }
            menu: ContextMenu {
                id: contextMenu
                MenuLabel { text: qsTr("Контекстное меню") }
                MenuItem {
                    text: qsTr("Открыть книгу")
                    onClicked: pageStack.push(Qt.resolvedUrl("TextPage.qml"))
                }
                MenuItem {
                    text: qsTr("Удалить")
                    onClicked: {
                       delete parent
                    }
                }
            }
        }

        model: 100

        VerticalScrollDecorator { }
    }
}

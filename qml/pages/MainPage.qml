import QtQuick 2.2
import Sailfish.Silica 1.0
import ru.omp.FileReader 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All
    backgroundColor: "#704214"

    property int chenchik: 5  // Задаем количество итераций

    property int booksCount;

    Component.onCompleted: fileReader.listFiles("Documents");

    Connections {
        target: fileReader

        onListGenerated: {
            var list = listOfFiles;
            booksCount = list.length
            console.log("Первый элемент списка -", list[0])
            console.log("Количество элементов в списке -", booksCount)
        }
    }



    SilicaListView {
        id: mainPageList
        anchors.fill: parent
        header: PageHeader { title: qsTr("Список книг")
        titleColor: Theme.primaryColor
        }

        FileReader{id:fileReader}


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
                        delete this
                    }
                }
            }
            Connections {
                target: fileCounter // Указываем целевое соединение
                /* Объявляем и реализуем функцию, как параметр
                                   * объекта и с имененем похожим на название сигнала
                                   * Разница в том, что добавляем в начале on и далее пишем
                                   * с заглавной буквы
                                   * */
                onListFormed: {
                    // Устанавливаем счётчик в текстовый лейбл
                }
            }
        }

        model: booksCount

        VerticalScrollDecorator { }
    }
}

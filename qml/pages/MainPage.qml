import QtQuick 2.2
import Sailfish.Silica 1.0
import ru.omp.FileReader 1.0


Page {
    objectName: "mainPage"
    id: mainPage
    allowedOrientations: Orientation.All
    backgroundColor: "dark green"

    property int booksCount;

    signal sendId(int bID);

    SilicaListView {
        id: mainPageList
        anchors.fill: parent
        header: PageHeader { title: qsTr("Список книг") }

        FileReader{id:fileReader}

        // Вызовем метод из плюсов, для считывания списка книг
        Component.onCompleted: fileReader.listFiles("Documents");

        //fileReader.listFiles("Documents");

        Text {
            id: name1
            text: qsTr("text")

            Connections {
                    target: fileReader // Указываем целевое соединение
                    /* Объявляем и реализуем функцию, как параметр
                     * объекта и с имененем похожим на название сигнала
                     * Разница в том, что добавляем в начале on и далее пишем
                     * с заглавной буквы
                     * */

                    onListGenerated: {
                         var list = listOfFiles;
                         booksCount = list.length
                         console.log("Первый элемент списка -", list[0])
                         console.log("Количество элементов в списке -", booksCount)
                    }
                }
        }


        PullDownMenu {
            MenuLabel { text: qsTr("Меню приложения") }
            MenuItem { text: qsTr("Пункт меню 1") }
            MenuItem { text: qsTr("Пункт меню 2") }
            MenuLabel { text: qsTr("Подраздел") }
            MenuItem { text: qsTr("Добавить книгу")}
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
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ReadingPage.qml"));
                        mainPage.sendId(model.index);
                    }
                }
                MenuItem {
                    text: qsTr("Удалить")
                    onClicked: {
                       delete parent
                    }
                }
            }
        }

        model: booksCount


        VerticalScrollDecorator { }

    }
}

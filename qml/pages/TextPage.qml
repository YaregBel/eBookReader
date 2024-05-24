import QtQuick 2.2
import Sailfish.Silica 1.0
import ru.omp.FileReader 1.0

Page {
    objectName: "textPage"
    allowedOrientations: Orientation.All

    FileReader {id:fileReader}


    Button {
        text: 'Читать'
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: { pageStack.push(textPageComponent)
            fileReader.open() }
    }





    Component {
        id: textPageComponent
        Page {
            function textFunc(book, number) {
                var array = textArray(book)
                console.log(array[number])
                return array[number]

            }

            property int currentPage: 0
            property var pages: []

            function paginateText(book) {
                    var tags = textArray(book)
                    var pageSize = 5 // количество тегов на одной странице
                    var paginated = []

                    for (var i = 0; i < tags.length; i += pageSize) {
                        paginated.push(tags.slice(i, i + pageSize).join(""))
                    }

                    return paginated
                }

                function updatePage() {
                    if (currentPage >= 0 && currentPage < pages.length) {
                        printText.text = pages[currentPage]
                    }
                }

            function onFileOpened(string){
                        printText.text = string;
                }

            function textArray(text) {
                // Регулярное выражение для поиска тегов
                  const regex = /<[^>]+>[^<]*<\/[^>]+>/g;
                  // Используем метод match для получения всех совпадений
                  const tagsArray = text.match(regex);
                  return tagsArray || []; // Возвращаем пустой массив, если нет совпадений
            }

            SilicaFlickable {
                objectName: "flickable"
                anchors.fill: parent
                contentHeight: layout.height + Theme.paddingLarge

                Column {
                    id: layout
                    objectName: "layout"
                    width: parent.width

                    Text {
                        id: printText
                                        wrapMode: Text.WordWrap

                                        anchors.horizontalCenter: parent.horizontalCenter
                                        width: parent.width * 0.9 // Устанавливаем ширину в 90% от ширины родителя
                                        font.pixelSize: Math.min(parent.width / 20, 24) // Динамически изменяем размер шрифта
                                          font.pointSize: parent.width / 40 // Можно использовать pointSize для адаптивности



                                        Connections {
                                                target: fileReader // Указываем целевое соединение
                                                /* Объявляем и реализуем функцию, как параметр
                                                 * объекта и с имененем похожим на название сигнала
                                                 * Разница в том, что добавляем в начале on и далее пишем
                                                 * с заглавной буквы
                                                 * */
                                                onOpened: {
                                                    pages = paginateText(book)
                                                    currentPage = 0
                                                    updatePage()



                                                }
                                            }
                    }
                }
            }

            // Закрепленное меню внизу
            Rectangle {
                id: bottomMenu
                width: parent.width
                height: Theme.itemSizeMedium
                color: "green"
                anchors.bottom: parent.bottom


                Row {
                    anchors.margins: Theme.horizontalPageMargin
                    anchors.centerIn: parent
                    spacing: 10

                    Button {
                        width: bottomMenu.width * 0.25
                        text: "Меню"
                        onClicked: pageStack.push(Qt.resolvedUrl("MainPage.qml"))
                    }
                    Button {
                        width: bottomMenu.width * 0.25
                        text: 'Push'
                        onClicked: if (currentPage < pages.length - 1) {
                                       currentPage++
                                       updatePage()
                                   }

                    }
                    Button {
                        width: bottomMenu.width * 0.25
                        text: 'Pop'
                        onClicked: if (currentPage > 0) {
                                       currentPage--
                                       updatePage()
                                   }
                    }
                }
            }

        }


    }


}

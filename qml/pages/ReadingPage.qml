import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.omp.FileReader 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    FileReader {id:fileReader}

    function onFileOpened(string){
            printText.text = string;
    }


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

            TextArea{
                text:  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua"
                readOnly: true;
            }

            Button{
                onClicked: fileReader.open();
                text: "click me!"
            }


            TextArea{
                id: printText
                text:  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua"
                readOnly: true;

                Connections {
                        target: fileReader // Указываем целевое соединение
                        /* Объявляем и реализуем функцию, как параметр
                         * объекта и с имененем похожим на название сигнала
                         * Разница в том, что добавляем в начале on и далее пишем
                         * с заглавной буквы
                         * */
                        onOpened: {
                            printText.text = book// Устанавливаем счётчик в текстовый лейбл
                        }
                    }
            }

        }
    }
}

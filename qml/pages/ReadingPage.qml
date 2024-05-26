import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.omp.FileReader 1.0


Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    FileReader {id:fileReader}

    property int receivedID: 1;


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

            Button{
                onClicked: fileReader.open();
                text: "click me!"
            }


            Text{
                id: printText
                text:  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua"
                //readOnly: true;
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
                            printText.text = book// Устанавливаем счётчик в текстовый лейбл
                            console.log("Полученный ID:", receivedID)
                        }
                    }
            }

//            Text{
//                id: text123
//                text: receivedID
//            }

        }

        function handlerSendID(message) {
                receivedID = message;
                console.log("ПОЛУЧИЛИ ID", message)
            }

    }
}

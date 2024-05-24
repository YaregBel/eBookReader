import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    SilicaListView {
          id: mainPageList
          anchors.fill: parent
          header: PageHeader { title: qsTr("Список книг") }
          PullDownMenu {
                     MenuItem {
                         text: qsTr("Пункт меню 3")
                         onClicked: console.log("Нажат третий пункт меню")
                     }
                     MenuLabel {
                         text: qsTr("Подраздел")
                     }
                     MenuItem {
                         text: qsTr("Пункт меню 2")
                         onClicked: console.log("Нажат второй пункт меню")
                     }
                     MenuItem {
                         text: qsTr("Пункт меню 1")
                         onClicked: console.log("Нажат первый пункт меню")
                     }
                     MenuLabel {
                         text: qsTr("Меню приложения")
                     }
                 }

          delegate: ListItem {
              onClicked: pageStack.push(Qt.resolvedUrl("ReadingPage.qml"))
              Flow {
                  Rectangle {
                      color: 'red'
                      height: 60
                      width: 60
                  }
                  Column {
                      Label {
                          text: qsTr("Книга %1").arg(model.index + 1)

                          x: Theme.horizontalPageMargin
                          color: 'gray'

                      }
                      Label {
                          text: qsTr("Автор %1").arg(model.index + 1)
                          x: Theme.horizontalPageMargin
                          color: 'yellow'
                      }

                  }


              }
              menu: ContextMenu {
                      MenuLabel {
                          text: "Контекстное меню"
                      }
                      MenuItem {
                          text: "Выделить жирным"
                          onClicked: label.font.bold = !label.font.bold
                      }
                      MenuItem {
                          text: "Выделить курсивом"
                          onClicked: label.font.italic = !label.font.italic
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
          model: 3

          VerticalScrollDecorator { }
      }


}

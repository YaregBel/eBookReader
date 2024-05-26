import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.omp.FileReader 1.0


Page {

    MainPage {
        id: sourcePage
        anchors.fill: parent
        visible: true

        // Подключаем сигнал к слоту на целевой странице
        onSendId: {
            targetPage.handlerSendID
            targetPage.visible = true
            sourcePage.visible = false
        }

    }

    ReadingPage {
        id: targetPage
        anchors.fill: parent
        visible: false
    }
}

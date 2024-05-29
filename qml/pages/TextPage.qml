import QtQuick 2.2
import Sailfish.Silica 1.0
import ru.omp.FileReader 1.0

Page {
    id: lowerTextPage
    FileReader { id: fileReader }

    allowedOrientations: Orientation.All
    property int currentPage: 0
    property var pages: []
    property int fontSize: 10

    Component.onCompleted: {
        fileReader.open()
    }


    function textArray(text) {
        const regex = /<[^>]+>(.*?)<\/[^>]+>/g;
        var match;
        var matches = [];
        while ((match = regex.exec(text)) != null) {
            if (match[0].indexOf('<h1>') === 0) {
                var cleanMatch = match[1].replace(/<\/?[^>]+(>|$)/g, ""); // Удаление вложенных тегов
                matches.push('<h1>' + cleanMatch + '</h1>');
            } else {
                matches.push(match[0]);
            }
        }
        return matches;
    }

    function paginateText(book) {
        const tags = textArray(book);
        const paginated = [];
        var currentPageContent = "";

        var tempText = Qt.createQmlObject('import QtQuick 2.2; Text { width: ' + (lowerTextPage.width * 0.9) + '; wrapMode: Text.WordWrap; font.pixelSize: ' + fontSize + ' }', lowerTextPage);

        for (var i = 0; i < tags.length; i++) {
            const tagContent = tags[i].toString(); // Преобразование в строку
            const newContent = currentPageContent + tagContent;
            tempText.text = newContent;

            // Проверка тега <h1>
            if (tagContent.indexOf('<h1>') !== -1 && currentPageContent.length > 0) {
                paginated.push(currentPageContent);
                currentPageContent = tagContent;
            } else if (tempText.contentHeight > lowerTextPage.height - 20) {
                const splitIndex = findSplitIndex(tagContent, currentPageContent, tempText);
                const firstPart = tagContent.substring(0, splitIndex);
                const secondPart = tagContent.substring(splitIndex);

                paginated.push(currentPageContent + "<p>" + firstPart + "</p>");
                currentPageContent = "<p>" + secondPart + "</p>";
            } else {
                currentPageContent = newContent;
            }
        }

        if (currentPageContent.length > 0) {
            paginated.push(currentPageContent);
        }

        tempText.destroy();
        return paginated;
    }

    function findSplitIndex(tag, currentPageContent, tempText) {
        var low = 0, high = tag.length, splitIndex = high;

        while (low < high) {
            const mid = Math.floor((low + high) / 2);
            tempText.text = currentPageContent + tag.substring(0, mid);

            if (tempText.contentHeight > lowerTextPage.height) {
                high = mid;
            } else {
                low = mid + 1;
                splitIndex = mid;
            }
        }

        return splitIndex;
    }

    function updatePage() {
        if (currentPage >= 0 && currentPage < pages.length) {
            printText.text = pages[currentPage];
        }
    }

    SilicaFlickable {
        objectName: "flickable"
        id: silicaPage
        anchors.fill: parent
        contentHeight: layout.height + Theme.paddingLarge

        PullDownMenu {
            MenuLabel { text: qsTr("Меню") }
            MenuItem {
                text: qsTr("Вернуться к списку книг")
                onClicked: pageStack.pop()
            }
            MenuLabel { text: qsTr("Изменить размер текста") }
            MenuItem {
                text: dwa
                id: fontSizeMenu
                Row {
                    anchors.margins: Theme.horizontalPageMargin
                    anchors.centerIn: parent
                    spacing: 10
                    Button {
                        text: '-'
                        width: fontSizeMenu.width * 0.25
                        onClicked: {

                            fontSize--
                            fontSizeLabel.text = fontSize

                        }
                    }
                    Label {
                        id: fontSizeLabel
                        text: fontSize
                    }

                    Button {
                        text: '+'
                        width: fontSizeMenu.width * 0.25
                        onClicked: {
                            fontSize++
                            fontSizeLabel.text = fontSize
                        }
                    }
                }

            }
        }

        Column {
            id: layout
            objectName: "layout"
            width: parent.width

            Text {
                id: printText
                wrapMode: Text.WordWrap
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width * 0.9
                font.pixelSize: fontSize
                font.pointSize: parent.width / 40

                Connections {
                    target: fileReader
                    onOpened: {
                        pages = paginateText(book);
                        currentPage = 0;
                        updatePage();
                        console.log(pages)
                    }
                }
            }
        }
    }

    Rectangle {
        id: leftClickArea
        width: parent.width * 0.1
        height: parent.height
        color: "transparent"
        anchors.left: parent.left
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (currentPage > 0) {
                    currentPage--;
                    updatePage();
                }
            }
        }
    }

    Rectangle {
        id: rightClickArea
        width: parent.width * 0.1
        height: parent.height
        color: "transparent"
        anchors.right: parent.right
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (currentPage < pages.length - 1) {
                    currentPage++;
                    updatePage();
                }
            }
        }
    }



}



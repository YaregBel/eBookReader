import QtQuick 2.2
import Sailfish.Silica 1.0
import ru.omp.FileReader 1.0

Page {
    objectName: "textPage"
    allowedOrientations: Orientation.All

    FileReader { id: fileReader }

    Button {
        text: 'Читать'
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            pageStack.push(textPageComponent)
            fileReader.open()
        }
    }

    Component {
        id: textPageComponent
        Page {
            id: lowerTextPage
            property int currentPage: 0
            property var pages: []

            function textArray(text) {
                const regex = /<[^>]+>[^<]*<\/[^>]+>/g;
                return text.match(regex) || [];
            }

            function paginateText(book) {
                const tags = textArray(book);
                const paginated = [];
                var currentPageContent = "";

                var tempText = Qt.createQmlObject('import QtQuick 2.2; Text { width: ' + (lowerTextPage.width * 0.9) + '; wrapMode: Text.WordWrap; font.pixelSize: ' + Math.min(lowerTextPage.width / 20, 24) + ' }', lowerTextPage);

                for (var i = 0; i < tags.length; i++) {
                    const newContent = currentPageContent + tags[i];
                    tempText.text = newContent;

                    if (tempText.contentHeight > lowerTextPage.height) {
                        const splitIndex = findSplitIndex(tags[i], currentPageContent, tempText);
                        const firstPart = tags[i].substring(0, splitIndex);
                        const secondPart = tags[i].substring(splitIndex);

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
                        font.pixelSize: Math.min(parent.width / 20, 24)
                        font.pointSize: parent.width / 40

                        Connections {
                            target: fileReader
                            onOpened: {
                                pages = paginateText(book);
                                currentPage = 0;
                                updatePage();
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
        }
    }


import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

import com.pipacs.ionic.Bookmark 1.0
import com.pipacs.ionic.Book 1.0

Page {
    tools: libraryTools
    orientationLock: prefs.orientation

    BookPage {id: bookPage}
    ImportPage {id: importPage}

    PageHeader {
        id: header
        text: sortByModel.get(library.sortBy).header
        clickable: true
        onClicked: {
            sortByDialog.open()
        }
    }

    SelectionDialog {
        id: sortByDialog
        titleText: "Sort books by"
        selectedIndex: library.sortBy

        model: ListModel {
            id: sortByModel
            ListElement {name: "Title"; header: "Library: By title"}
            ListElement {name: "Author"; header: "Library: By author"}
            ListElement {name: "Date added"; header: "Library: By date added"}
            ListElement {name: "Date last read"; header: "Library: By date last read"}
        }
        onAccepted: {
            library.sortBy = sortByDialog.selectedIndex
        }
    }

    Component {
        id: delegate
        Item {
            height: Math.max(65, textName.height + textOpened.height + 15)
            width: parent.width

            BorderImage {
                id: background
                anchors.fill: parent
                // Fill page borders
                anchors.leftMargin: -listView.anchors.leftMargin
                anchors.rightMargin: -listView.anchors.rightMargin
                visible: mouseArea.pressed
                source: "image://theme/meegotouch-list-background-pressed-center"
            }

            Row {
                Image {
                    width: 53
                    height: 59
                    source: coverUrl
                }
                Column {
                    Label {
                        id: textName
                        text: name
                    }
                    Label {
                        id: textOpened
                        text: "Last read: " + dateOpened
                        font.pixelSize: platformStyle.fontPixelSize - 4
                    }
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    bookPage.book = library.books[index]
                    pageStack.push(bookPage)
                }
            }
        }
    }

    ListView {
        id: listView
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 11
        clip: true
        focus: true
        model: library.books
        delegate: delegate
    }

    ScrollDecorator {
        flickableItem: listView
    }

    ToolBarLayout {
        id: libraryTools
        visible: true
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {pageStack.pop()}
        }
        ToolIcon {
            iconId: "toolbar-add"
            onClicked: {pageStack.push(importPage)}
        }
    }
}

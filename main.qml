import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
//import com.apm.bridge 1.0
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Package Manager")
//    Bridge {
//        id:bridge
//    }

    background: Rectangle{
        color: '#80dadada'
    }

    function getsys(f) {
        print(f)
    }
    Item {
        property string savedir: ''
        id: datas
    }
    FileDialog {
        id: exportDlg
        title: qsTr("select save directory!")
        folder: shortcuts.documents
        selectExisting: true
        selectFolder: true
        selectMultiple: false
        onAccepted: {
            datas.savedir = exportDlg.fileUrl
        }
    }

    function save() {
        exportDlg.open()
        bridge.export_package(listView.currentItem.text,datas.savedir)
    }

    ColumnLayout {
        anchors.rightMargin: 3
        anchors.leftMargin: 3
        anchors.bottomMargin: 3
        anchors.topMargin: 3
        anchors.fill: parent
        RowLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            anchors.bottomMargin: 3
            anchors.topMargin: 3
            spacing: 2
            TextField {
                id: inputs
                placeholderText: qsTr('please input filters')
                Layout.minimumWidth: 400
                Layout.minimumHeight: 42
                color: 'black'
                background: Rectangle {
                    color: '#f3f3f3'
                    radius: 6
                }
                Layout.alignment: Qt.AlignCenter
                onTextChanged: {
                    getsys(inputs.text)
                    bridge.filter(inputs.text)
                    listView.model = bridge.size()
                }
            }
        }

        ScrollView {
            Layout.fillWidth: true
            anchors.topMargin: 40
            Layout.fillHeight: true
            ListView {
                id: listView
                width: parent.width
                model: bridge.size()
                delegate: ItemDelegate {
                    text: bridge.name(index)
                    highlighted: ListView.isCurrentItem
                    width: parent.width
                    onClicked: {
                        listView.currentIndex = index
                        print('clicked' + listView.currentIndex + ListView.isCurrentItem)
                    }
                }

//                onMovementEnded: {
//                    print("end")
//                }
//                onMoveChanged: {
//                    print("move changed")
//                }
//                onMovementStarted: {
//                    print("move started")
//                }

            }
        }

        RowLayout {
            id: rowLayout
            width: 100
            height: 100
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            Button {
                id: exp
                text: qsTr("Export")
                onClicked:save()
            }

            Button {
                id: del
                text: qsTr("Delete")
                onClicked: bridge.remove_package(listView.currentItem.text)
            }

            Button {
                id: refresh
                text: qsTr("Refresh")
                onClicked: bridge.refresh()
            }
        }
    }
    onClosing: bridge.quit()
    Connections {
        target: bridge
        onNamesChanged: {
            print('changed')
            listView.model = 0
            listView.model = bridge.size()
        }
        onPackageRemoved:listView.remove(listView.currentIndex)
    }

}

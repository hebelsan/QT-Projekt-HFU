import QtQuick 2.7

Item {
    id: usbView
    width: 800
    height: 600
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    property var musicFilesList: []

    Connections {
        target: connector
        onAudioWheelTurnedLeft: {
            if (usbView.visible) {
                if (musicList.currentIndex > 0) {
                    musicList.currentIndex--;
                }
                musicState.titleCache = usbView.musicFilesList[0][musicList.currentIndex];
            }
        }
        onAudioWheelTurnedRight: {
            if (usbView.visible) {
                if (musicList.currentIndex < musicList.count-1) {
                    musicList.currentIndex++;
                }
                musicState.titleCache = usbView.musicFilesList[0][musicList.currentIndex];
            }
        }
        onMusicPlayButtonPressed: {
            playButton.source = playButton.pausePath
        }
        onMusicPauseButtonPressed: {
            playButton.source = playButton.playPath
        }
        onMusicBackwardButtonPressed: {
            backwardButton.source = backwardButton.backwardButtonPressedPath
        }
        onMusicForwardButtonPressed: {
            forwardButton.source = forwardButton.forwardButtonPressedPath
        }
        onMusicWheelDirectionNormal: {
            backwardButton.source = backwardButton.backwardButtonPath
            forwardButton.source = forwardButton.forwardButtonPath
        }
        onSendNewMusicList: {
            setNewFileList(filesStructure)
        }
    }

    UsbViewVolumeBar {
        id: usbViewVolumeBar
        width: 15
        height: 250
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 220
        anchors.leftMargin: -300
    }

    Image {
        id: cover
        width: 100
        height: 100
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 190
        anchors.leftMargin: -200
        source: musicState.coverPath
    }

    Item {
        id: usbViewButtons
        width: 500
        height: 100
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 190
        anchors.leftMargin: -100

        Text {
            id: title
            width: parent.width - 100
            height: 20
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 50
            horizontalAlignment:  Text.AlignHCenter
            text: musicState.title
            font.pointSize: 16
            color: "white"
            clip: true
        }

        MusicTitleProgressBar {
            id: progressBar
            width: parent.width - 100
            anchors.top: parent.top
            anchors.topMargin: 25
            anchors.left: parent.left
            anchors.leftMargin: 50
            Connections {
                target: musicState
                onMusicProgressTimerStarted: {
                    progressBar.fullProgressBar.width +=
                            progressBar.fullProgressBar.parent.width / musicState.titleDuration
                    progressBar.progressButton.anchors.leftMargin +=
                            progressBar.progressButton.parent.width / musicState.titleDuration
                }
            }
        }

        Image {
            id: backwardButton
            property string backwardButtonPath: "bilder/UsbView/BackwardButton.png"
            property string backwardButtonPressedPath: "bilder/UsbView/BackwardButtonPressed.png"
            width: 40
            height: 40
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 50
            source: backwardButtonPath
        }

        Image {
            id: playButton
            property string playPath: "bilder/UsbView/PlayButton.png"
            property string pausePath: "bilder/UsbView/PauseButton.png"
            width: 40
            height: 40
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            source: playPath
        }

        Image {
            id: forwardButton
            property string forwardButtonPath: "bilder/UsbView/ForwardButton.png"
            property string forwardButtonPressedPath: "bilder/UsbView/ForwardButtonPressed.png"
            width: 40
            height: 40
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: 50
            source: forwardButtonPath
        }
    }

    Image {
        id: rahmen
        visible: true
        width: 625
        height: 340
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 170
        anchors.leftMargin: -253
        source: "bilder/UsbView/UsbRahmen.png"
    }

    Rectangle {
        id: titlListRec
        width: 580
        height: 280
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 200
        anchors.leftMargin: -230
        border.color: "red"
        border.width: 1

        Component {
            id: musicDelegate
            Item {
                width: parent.width; height: 30;
                Column {
                    Text { text: '<b>Titel:</b> ' + titel }
                    Text { text: '<b>Interpreter:</b> ' + interpreter }
                }
            }
        }

        Component {
            id: highlight
            Rectangle {
                color: "red"
                radius: 5
            }
        }

        ListView {
            anchors.fill: parent
            id: musicList
            model: MusicListModel {}
            delegate: musicDelegate
            highlight: highlight
            focus: true
            highlightFollowsCurrentItem: true
            clip: true
        }
    }

    function setNewFileList(filesStructure) {
        musicState.titleCache = filesStructure[0][0];
        usbView.musicFilesList = filesStructure;
        musicList.model.clear();
        for (var i=0; i < filesStructure[0].length; i++) {
            if (checkIfDir(filesStructure[0][i])) {
                appendDir(filesStructure[0][i])
            } else
                appendTitle(filesStructure[0][i])
        }
    }

    function checkIfDir(fileName) {
        if (fileName.substring(0, 3) === "DIR")
            return true;
    }

    function appendDir(fileName) {
        musicList.model.append({ "titel": fileName,
                               "interpreter" : fileName })
    }

    function appendTitle(fileName) {
        musicList.model.append({ "titel": fileName,
                               "interpreter" : fileName })
    }
}


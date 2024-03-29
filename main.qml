import QtQuick 2.15
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.15

ApplicationWindow  {
    width: 1920
    height: 1080
    visible: uiControler.isMediaAppVisible;

    onVisibleChanged: {
        console.log("ApplicationWindow" + uiControler.isMediaAppVisible)
    }

    Image {
        source: "qrc:/Image/background.png" // Adjust the path to your background image
        anchors.fill: parent
    }

    Item {
        id: mediaplayerheader
        width: parent.width
        height: parent.height / 5

        Rectangle {
            id: statusBar
            width: parent.width
            height: parent.height / 4

            color: "#35374B"

            Item {
                id: backButtonIconShape

                width: parent.height-15
                height: parent.height-15

                anchors.left: parent.left
                anchors.leftMargin: 5

                anchors.verticalCenter: parent.verticalCenter

                Image {
                    id: backButtonIcon
                    source: "qrc:/Image/back_button.png" // Adjust the path to your background image
                    anchors.fill: parent
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true

                    onClicked: {
                        uiControler.uiEventBackToHomeOnClicked();
                    }

                    onPressed: {
                        backButtonIcon.source = "qrc:/Image/back_button_hover.png"
                    }

                    onReleased: {
                        backButtonIcon.source = "qrc:/Image/back_button.png"
                    }

                    onEntered: {
                        cursorShape = Qt.PointingHandCursor;
                    }

                    onExited: {
                        cursorShape = Qt.ArrowCursor;
                    }
                }
            }
        }

        Rectangle {

            width: parent.width
            height: parent.height-statusBar.height

            anchors.top: statusBar.bottom

            Image {
                source: "qrc:/Image/title.png" // Adjust the path to your background image
                anchors.fill: parent
            }

            Text {
                text: "MediaPlayer"

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                font.pixelSize: 24
                font.family: "Arial"

                color: "white"
            }
        }
    }

    Item {
        id: mediaplayerbody
        width: parent.width
        height: parent.height - mediaplayerheader.height

        anchors.top: mediaplayerheader.bottom

        Item {
            id: mediaplayermenu
            width: parent.width *2 / 7
            height: parent.height

            anchors.left: parent.left

            ListView {
                id: mediaplayerlist

                width: parent.width
                height: parent.height
                spacing : 1
                displayMarginBeginning: 0

                property int hoveredIndex: -1
                property int exitedIndex: -1

                property bool isPlaying: uiControler.isMediaPlaying

                Image {
                    source: "qrc:/Image/playlist.png"
                    anchors.fill: parent
                }

                Component.onCompleted: {
                    mediaplayerlist.currentIndex = -1;
                }

                onCurrentIndexChanged: {
                    uiControler.uiMusicSelectedChanged(mediaplayerlist.currentIndex);
                }


                model: songListModel

                function getImageSource(id) {

                    let imageSource= "";

                    if(id === mediaplayerlist.currentIndex) {
                        imageSource= "qrc:/Image/playlist_item.png";
                    }

                    if( id === mediaplayerlist.hoveredIndex) {
                        if(id === mediaplayerlist.currentIndex) {
                            imageSource= "qrc:/Image/playlist_item.png";
                        } else {
                            imageSource= "qrc:/Image/hold.png";
                        }
                    }

                    if(id === mediaplayerlist.exitedIndex){
                        if(id === mediaplayerlist.currentIndex) {
                            imageSource= "qrc:/Image/playlist_item.png";
                        } else {
                            imageSource= "";
                        }
                    }

                    return imageSource;
                }

                delegate: Item {
                    width: mediaplayerlist.width
                    height: 60

                    Image {
                        id: playingIcon
                        source: "qrc:/Image/playing.png";

                        width: 20
                        height: 20

                        anchors.left: parent.left
                        anchors.leftMargin: 10

                        anchors.verticalCenter: parent.verticalCenter
                        visible: mediaplayerlist.isPlaying && mediaplayerlist.currentIndex === index

                    }

                    Image {
                        id: playlistImageHold
                        source: mediaplayerlist.getImageSource(index);
                        anchors.fill: parent
                    }

                    Text {
                        anchors.centerIn: parent
                        text: model.title
                        color: "white"
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: {
                            mediaplayerlist.currentIndex = index
                            mediaplayerpresentviewlist.currentIndex = index
                        }

                        onEntered: {
                            mediaplayerlist.hoveredIndex = index
                            if(mediaplayerlist.hoveredIndex === mediaplayerlist.exitedIndex) {
                                mediaplayerlist.exitedIndex = -1;
                            }
                        }

                        onExited: {

                            mediaplayerlist.exitedIndex = index
                            if(mediaplayerlist.hoveredIndex === mediaplayerlist.exitedIndex) {
                                mediaplayerlist.hoveredIndex = -1;
                            } 
                        }
                    }

                }
            }
        }

        Item {
            id: mediaplayerpresent
            width: parent.width - mediaplayermenu.width
            height: parent.height
            anchors.left : mediaplayermenu.right

            Item {
                id: mediaplayerpresentview
                width: parent.width
                height: parent.height * 7/10

                PathView {
                    id: mediaplayerpresentviewlist

                    preferredHighlightBegin: 0.5
                    preferredHighlightEnd: 0.5

                    width: parent.width
                    height: parent.height

                    pathItemCount: 3

                    flickDeceleration: 1000

                    model: songListModel

                    delegate: Rectangle {
                        width: PathView.isCurrentItem ? mediaplayerpresentviewlist.width*1/5 : mediaplayerpresentviewlist.width*1/6
                        height: PathView.isCurrentItem ? mediaplayerpresentviewlist.height*3/5 : mediaplayerpresentviewlist.height*3/6
                        border.color: "black"
                        border.width: 1

                        Image {
                            id: pathviewImage
                            source: model.image
                            anchors.fill: parent
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                mediaplayerpresentviewlist.currentIndex = index;
                                mediaplayerlist.currentIndex = index;
                            }
                        }
                    }

                    path: Path {
                        startX: (mediaplayerpresentview.width - (mediaplayerpresentviewlist.width*1/6 * 3 + 40 * 2)) / 2
                        startY: mediaplayerpresentview.height / 2

                        PathLine {
                            x: (mediaplayerpresentview.width - (mediaplayerpresentviewlist.width*1/6 * 3 + 40 * 2)) / 2 + mediaplayerpresentviewlist.width*1/6
                            y: mediaplayerpresentview.height / 2
                        }

                        PathLine {
                            x: (mediaplayerpresentview.width - (mediaplayerpresentviewlist.width*1/6 * 3 + 40 * 2)) / 2 + mediaplayerpresentviewlist.width*1/6 * 2 + 40
                            y: mediaplayerpresentview.height / 2
                        }

                        PathLine {
                            x: (mediaplayerpresentview.width - (mediaplayerpresentviewlist.width*1/6 * 3 + 40 * 2)) / 2 + mediaplayerpresentviewlist.width*1/6 * 3 + 40 * 2
                            y: mediaplayerpresentview.height / 2
                        }
                    }
                }
            }

            Item {
                id: mediaplayerpresentcontrol
                width: parent.width
                height: parent.height - mediaplayerpresentview.height
                anchors.top: mediaplayerpresentview.bottom

                Connections {
                    target: uiControler
                    
                    function onPlayerSongPlayingChanged(songId, songName, singer, imagePath, totalTime) {
                        console.log("Song details:", songId, songName, singer, imagePath, totalTime)
                        mediaplayerlist.currentIndex = songId
                        mediaplayerpresentviewlist.currentIndex = songId
                    }       
                }

                ProgressBar {
                    id: mediaplayerprogressbar
                    width: parent.width*0.8
                    height: 5

                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Item {
                    width: parent.width
                    height: parent.height - mediaplayerprogressbar.height

                    Rectangle {
                        id: mediaplayercontrolshuffle
                        width: 55
                        height: 35

                        color: "transparent"

                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 50

                        property string state: "unchecked"

                        Image {
                            id: mediaplayercontrolshuffleicon
                            source: "qrc:/Image/shuffle.png" // Adjust the path to your background image
                            anchors.fill: parent
                        }

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true

                            onClicked: {
                                if(mediaplayercontrolshuffle.state === "checked") {
                                    mediaplayercontrolshuffle.state = "unchecked"
                                    mediaplayercontrolshuffleicon.source = "qrc:/Image/shuffle.png"
                                } else {
                                    mediaplayercontrolshuffle.state = "checked"
                                    mediaplayercontrolshuffleicon.source = "qrc:/Image/shuffle-1.png"
                                }
                            }

                            onEntered: {
                                cursorShape = Qt.PointingHandCursor;
                            }

                            onExited: {
                                cursorShape = Qt.ArrowCursor;
                            }
                        }


                    }

                    Rectangle {
                        id: mediaplayercontrolprevious

                        width: 60
                        height: 35

                        color: "transparent"

                        radius: 20

                        anchors.right : mediacontrolplaying.left
                        anchors.rightMargin: 10

                        anchors.verticalCenter: parent.verticalCenter

                        Image {
                            id: mediaplayercontrolpreviousicon
                            source: "qrc:/Image/prev.png"
                            anchors.fill: parent
                        }

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true

                            onClicked: {
                                mediaplayerpresentviewlist.decrementCurrentIndex();
                                mediaplayerlist.currentIndex = mediaplayerpresentviewlist.currentIndex;      
                            }

                            onPressed: {
                                mediaplayercontrolpreviousicon.source = "qrc:/Image/hold-prev.png"
                            }

                            onReleased: {
                                mediaplayercontrolpreviousicon.source = "qrc:/Image/prev.png"
                            }

                            onEntered: {
                                cursorShape = Qt.PointingHandCursor;
                            }

                            onExited: {
                                cursorShape = Qt.ArrowCursor;
                            }
                        }
                    }

                    Rectangle {
                        id: mediacontrolplaying
                        width: 90
                        height: 90

                        radius: 50
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter

                        property bool isPlaying: uiControler.isMediaPlaying

                        color: "transparent"

                        onIsPlayingChanged: {

                            if(mediacontrolplaying.isPlaying) {
                                mediacontrolplayingicon.source = "qrc:/Image/pause.png"
                            } else {
                                mediacontrolplayingicon.source = "qrc:/Image/play.png"
                            }
                        }

                        Image {
                            id: mediacontrolplayingicon
                            source: "qrc:/Image/play.png"
                            anchors.fill: parent
                        }

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true

                            onClicked: {
                                uiControler.uiEventMediaPlayStateChanged();
                            }

                            onPressed: {
                                if(mediacontrolplaying.isPlaying === false) {
                                    mediacontrolplayingicon.source = "qrc:/Image/hold-play.png"
                                } else{
                                    mediacontrolplayingicon.source = "qrc:/Image/hold-pause.png"
                                }
                            }

                            onReleased: {
                                if(mediacontrolplaying.isPlaying === false) {
                                    mediacontrolplayingicon.source = "qrc:/Image/play.png"
                                } else{
                                    mediacontrolplayingicon.source = "qrc:/Image/pause.png"
                                }
                            }

                            onEntered: {
                                cursorShape = Qt.PointingHandCursor;
                            }

                            onExited: {
                                cursorShape = Qt.ArrowCursor;
                            }
                        }

                    }

                    Rectangle {
                        id: mediaplayercontrolnext

                        width: 60
                        height: 35

                        color: "transparent"

                        radius: 20

                        anchors.left : mediacontrolplaying.right
                        anchors.leftMargin: 10
                        anchors.verticalCenter: parent.verticalCenter

                        Image {
                            id: mediaplayercontrolnexticon
                            source: "qrc:/Image/next.png" // Adjust the path to your background image
                            anchors.fill: parent
                        }

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true

                            onClicked: {
                                mediaplayerpresentviewlist.incrementCurrentIndex();
                                mediaplayerlist.currentIndex = mediaplayerpresentviewlist.currentIndex;  
                            }

                            onPressed: {
                                mediaplayercontrolnexticon.source = "qrc:/Image/hold-next.png"
                            }

                            onReleased: {
                                mediaplayercontrolnexticon.source = "qrc:/Image/next.png"
                            }

                            onEntered: {
                                cursorShape = Qt.PointingHandCursor;
                            }

                            onExited: {
                                cursorShape = Qt.ArrowCursor;
                            }
                        }
                    }

                    Rectangle {
                        id: mediaplayercontrolrepeat
                        width: 55
                        height: 35

                        color: "transparent"

                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 50

                        Image {
                            id: mediaplayercontrolrepeaticon
                            source: "qrc:/Image/repeat.png" // Adjust the path to your background image
                            anchors.fill: parent
                        }

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true

                            onClicked: {
                                if(mediaplayercontrolrepeat.state === "checked") {
                                    mediaplayercontrolrepeat.state = "unchecked"
                                    mediaplayercontrolrepeaticon.source = "qrc:/Image/repeat.png"
                                } else {
                                    mediaplayercontrolrepeat.state = "checked"
                                    mediaplayercontrolrepeaticon.source = "qrc:/Image/repeat1_hold.png"
                                }
                            }

                            onEntered: {
                                cursorShape = Qt.PointingHandCursor;
                            }

                            onExited: {
                                cursorShape = Qt.ArrowCursor;
                            }
                        }
                    }
                }
            }
        }
    }
}

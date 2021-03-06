import QtQuick 2.0


/**
  * Implements the changing color for the Menu Items
  *
  */
    Text{
        id: text
        width: 60
        property int pos: 0
        property string caption: "text"
        color: "#ffffff"
        font.pointSize: 24

        text: caption
        font.bold: false
        font.italic: false
        font.underline: true
        verticalAlignment: Text.AlignRight
        horizontalAlignment: Text.AlignHCenter

        Behavior on parent{
            SmoothedAnimation{
                property: y
                easing.type: Easing.InOutQuad
                duration: 100
                from:10
                to: parent.y
            }
        }

        property color oldColor: "black"
        property color newColor: "black"

        Behavior on color{

            ColorAnimation {
                from: oldColor
                to: newColor
                duration: 800
            }
        }

        onPosChanged: {
            oldColor = color
            if(pos==0){
                newColor = canEventSink.selectedRightColor
            }
            else{
                newColor = canEventSink.unSelectedRightColor
            }
        }

    }

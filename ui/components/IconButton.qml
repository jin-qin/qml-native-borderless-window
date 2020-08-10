import QtQuick 2.0
import QtQuick.Controls 2.5

Button {
    property string bk_img_normal: ""
    property string bk_img_hover: ""
    property string bk_img_click: ""
    property string bk_img_disable: ""

    enabled: true
    display: AbstractButton.IconOnly
    antialiasing: true
    rightPadding: 0
    bottomPadding: 0
    leftPadding: 0
    topPadding: 0
    autoRepeat: false
    highlighted: false
    flat: true

    Binding {
        target: bk_img
        property: "source"
        value: bk_img_normal
    }

    background: Image {
        id: bk_img
        anchors.fill: parent
        source: parent.bk_img_normal
        fillMode: Image.Stretch

        onSourceSizeChanged: {
            parent.width = bk_img.width;
            parent.height = bk_img.height;
        }
    }

    onHoveredChanged: {
        hovered ? bk_img.source = bk_img_hover :
                  bk_img.source = bk_img_normal
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onPressed: {
            bk_img.source = bk_img_click
        }
    }
}

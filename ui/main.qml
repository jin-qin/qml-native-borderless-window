import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0

import io.jin.qmlbe 1.0

import "components"

Window {
    id: main_window

    visible: true
    width: 1000
    height: 600
    minimumWidth: 1000
    minimumHeight: 600
    title: qsTr("Native Borderless Window")
    color: "transparent" // transparent window

    onVisibilityChanged: {
        if (Qt.platform.os == "windows") {
            // tricks for maximized window on Microsoft Windows, if not do so, the window will exceed the monitor with about 8 pixels.
            var is_maximized = main_window.visibility === Window.Maximized
            var exceed_pixels = Math.round(8 / Screen.devicePixelRatio)
            window_content.anchors.margins = is_maximized ? exceed_pixels : 0
        }

        if (Qt.platform.os == "osx") {
            // workaround for a weird bug: after restoring from fullscreen, the title bar of the window appears again.
            if (main_window.visibility == Window.Windowed) {
                backend.notifyQmlEvent(this, "EnableWindowBorderless")
            }
        }
    }

    Component.onCompleted: {
        if (Qt.platform.os == "osx") {
            flags = Qt.WindowFullscreenButtonHint
        }

        backend.notifyQmlEvent(this, "EnableWindowBorderless")
    }

    QmlBackendEngine {
        id: backend
    }

    Rectangle {
        id: window_content
        anchors.fill: parent
        color: "white"

        Rectangle {
            id: left_panel
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            width: 60
            color: "slategray"
        }

        Rectangle {
            id: right_panel
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: left_panel.right
            anchors.right: parent.right

            TitleBar {
                id: title_bar
                wnd: main_window
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
            }
        }
    }
}

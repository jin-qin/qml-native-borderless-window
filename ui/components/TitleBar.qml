import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5

Rectangle {
    id: title_bar
    width: 500
    height: 40
    color: "#F2F6FC"
    border.width: 0

    property Window wnd: null
    property bool is_os_windows: false

    Component.onCompleted: {
        backend.notifyQmlEvent(wnd, "SetWindowTitleHeight", title_bar.height)
        backend.notifyQmlEvent(wnd, "SetTitleBarButtonsArea", Qt.size(row_title_bar_buttons.width, row_title_bar_buttons.height))

        if (Qt.platform.os == "windows") {
            is_os_windows = true
        }
    }

    Row {
        id: row_title_bar_buttons
        layoutDirection: Qt.RightToLeft
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        visible: is_os_windows

        IconButton {
            id: btn_close
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 4
            bk_img_normal: "qrc:/res/title_button_win/close_normal.png";
            bk_img_hover: "qrc:/res/title_button_win/close_hover.png";
            bk_img_click: "qrc:/res/title_button_win/close_click.png";
            bk_img_disable: "qrc:/res/title_button_win/close_disable.png";

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    wnd.close()
                }
            }
        }

        IconButton {
            id: btn_max_restore
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 4
            bk_img_normal: "qrc:/res/title_button_win/maximize_normal.png";
            bk_img_hover: "qrc:/res/title_button_win/maximize_hover.png";
            bk_img_click: "qrc:/res/title_button_win/maximize_click.png";
            bk_img_disable: "qrc:/res/title_button_win/maximize_disable.png";

            Connections {
                target: wnd
                onVisibilityChanged: {
                    var is_maximize = wnd.visibility === wnd.Maximized

                    btn_max_restore.bk_img_normal = is_maximize ? "qrc:/res/title_button_win/restore_normal.png" :
                                                                  "qrc:/res/title_button_win/maximize_normal.png"
                    btn_max_restore.bk_img_hover = is_maximize ? "qrc:/res/title_button_win/restore_hover.png" :
                                                                 "qrc:/res/title_button_win/maximize_hover.png"
                    btn_max_restore.bk_img_click = is_maximize ? "qrc:/res/title_button_win/restore_click.png" :
                                                                 "qrc:/res/title_button_win/maximize_click.png"
                    btn_max_restore.bk_img_disable = is_maximize ? "qrc:/res/title_button_win/restore_disable.png" :
                                                                   "qrc:/res/title_button_win/maximize_disable.png"
                }
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    var is_maximize = wnd.visibility === Window.Maximized
                    wnd.visibility = is_maximize ? Window.AutomaticVisibility : Window.Maximized
                }
            }
        }

        IconButton {
            id: btn_min
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 4
            bk_img_normal: "qrc:/res/title_button_win/minimize_normal.png";
            bk_img_hover: "qrc:/res/title_button_win/minimize_hover.png";
            bk_img_click: "qrc:/res/title_button_win/minimize_click.png";
            bk_img_disable: "qrc:/res/title_button_win/minimize_disable.png";

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    // *********************************************************************************************************** //
                    // workground for QT's bug.
                    // on WINDOWS: if call showMinimized() of QWindow while this window is maximized,
                    // then this window will restore to normal size (not maximized) after calling showNormal()
                    // so try to send a event to c++ backend engine, then call native method to show this window
                    // minimized.
                    //
                    // on MACOS: showMinimized() of QWindow cannot work at all if the window's flag contains Qt.FramelessWindowHint
                    // *********************************************************************************************************** //
                    if (Qt.platform.os == "windows") {
                        backend.notifyQmlEvent(wnd, "ShowWindowMinimize")
                    } else {
                        wnd.visibility = Window.Minimized
                    }
                }
            }
        }
    }
}

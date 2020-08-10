#include "util_misc_win.h"

#ifdef Q_OS_WIN
#include <dwmapi.h>
#include <Windows.h>
#include <windowsx.h>
#include "multiscreen_helper/multiscreen_helper.h"

#include <QByteArray>
#include <QGuiApplication>
#include <QDebug>

namespace Util {
namespace Misc {

void enableWindowBorderlessWin(qulonglong wId)
{
    HWND wnd = (HWND)wId;
    // enable borderless and keep aero effects.
    SetWindowLongPtr(wnd, GWL_STYLE, static_cast<LONG>(Style::aero_borderless));

    // enable shadow
    const MARGINS shadow_on = { 1, 1, 1, 1 };
    /*const MARGINS shadow_off = { 0, 0, 0, 0 };*/
    DwmExtendFrameIntoClientArea(wnd, &shadow_on);

    //redraw frame
    SetWindowPos(wnd, Q_NULLPTR, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
    ShowWindow(wnd, SW_SHOW);
}

void enableHighDpiSupportWin()
{
    auto scinfo = Util::Misc::getPrimaryScreenInfo();
    qputenv("QT_SCALE_FACTOR", QString("%1").arg(scinfo.scalingFactor).toLatin1());
}

QVector<MultiScreenHelper::ScreenInfo> getAllScreenInfo()
{
    return MultiScreenHelper::getAllScreensInfo();
}

MultiScreenHelper::ScreenInfo getPrimaryScreenInfo()
{
    return MultiScreenHelper::getPrimaryScreenInfo();
}

}
}

#endif

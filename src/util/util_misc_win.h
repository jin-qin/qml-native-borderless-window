#ifndef UTIL_MISC_WIN_H
#define UTIL_MISC_WIN_H

#include <QtGlobal>
#include <QObject>

#ifdef Q_OS_WIN
#include "multiscreen_helper/multiscreen_helper.h"

namespace Util {

enum class Style : DWORD
{
  windowed = (WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN),
  aero_borderless = (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN)
};

namespace Misc {
    void enableWindowBorderlessWin(qulonglong wId);

    void enableHighDpiSupportWin();

    QVector<MultiScreenHelper::ScreenInfo> getAllScreenInfo();

    MultiScreenHelper::ScreenInfo getPrimaryScreenInfo();
}

}

#endif

#endif // UTIL_MISC_WIN_H

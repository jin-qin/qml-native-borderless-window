#ifndef MULTISCREEN_HELPER_H
#define MULTISCREEN_HELPER_H

#include <QtGlobal>
#include <QVector>
#include <Windows.h>

/**
 * @brief The MultiScreenHelper class
 *
 * Only for Windows platform
 */

class MultiScreenHelper
{
public:
    typedef struct ScreenInfo_{
        ScreenInfo_() {
    #if defined(Q_OS_WIN)
            ZeroMemory(&originInfo, sizeof(originInfo));
            originInfo.dmSize = sizeof(DEVMODE);
    #endif
        }

        int			sysPosX = 0;
        int			sysPosY = 0;
        int         sysWidth = 0;
        int         sysHeight = 0;
        int			physicalPosX = 0;
        int			physicalPosY = 0;
        int         physicalWidth = 0;
        int         physicalHeight = 0;
        int         logicalPixels = 0;
        int         bitsPerPel = 32;
        qreal		scalingFactor = 0;
        bool        isPrimaryScreen = false;
        QString     deviceName = QString();
        QString     firendlyName = QString();
    #if defined(Q_OS_WIN)
        DEVMODE     originInfo;
    #endif
    } ScreenInfo;
public:
    MultiScreenHelper();
    ~MultiScreenHelper();

public:
    static QVector<ScreenInfo> getAllScreensInfo();
    static ScreenInfo getPrimaryScreenInfo();
    static void printAllScreenInfo();

private:
    static BOOL updateAllScreenInfo();

    static BOOL CALLBACK callbackGetScreenInfo(HMONITOR hMonitor,HDC, LPRECT,LPARAM lParam);
};

#endif // MULTISCREEN_HELPTER_H

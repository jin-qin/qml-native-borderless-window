#include "native_event_filter.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#include <windowsx.h>
#endif

#include <QByteArray>
#include <QWindow>
#include <QVariant>

#include <QDebug>

bool NativeEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result)
{
#ifdef Q_OS_WIN
    if (eventType == "windows_generic_MSG") {
        MSG* msg = static_cast<MSG *>(message);
        if (msg == Q_NULLPTR)
            return false;

        switch(msg->message) {
        case WM_COMMAND: {
          SendMessage(msg->hwnd, WM_SYSCOMMAND, msg->wParam, msg->lParam);
          *result = DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
          return true;
        }
        case WM_NCCALCSIZE:{
            NCCALCSIZE_PARAMS& params = *reinterpret_cast<NCCALCSIZE_PARAMS*>(msg->lParam);
            if (params.rgrc[0].top != 0)
                params.rgrc[0].top -= 1;

            //this kills the window frame and title bar we added with WS_THICKFRAME and WS_CAPTION
            *result = WVR_REDRAW;
            return true;
        }
        case WM_NCHITTEST: {
            const LONG borderWidth = 8; //in pixels
            RECT winrect;
            GetWindowRect(msg->hwnd, &winrect);
            long x = GET_X_LPARAM(msg->lParam);
            long y = GET_Y_LPARAM(msg->lParam);

            // caption, a.k.a. title bar
            auto wndScaleFactor = qgetenv("QT_SCALE_FACTOR").toDouble();
            int titleBarHeight = m_wndsParams[(WId)msg->hwnd]["TitleHeight"].toInt();
            titleBarHeight = static_cast<int>(titleBarHeight * wndScaleFactor);
            int titleBarBtnsWidth = m_wndsParams[(WId)msg->hwnd]["TitleBarButtonsArea"].toSize().width();
            titleBarBtnsWidth = static_cast<int>(titleBarBtnsWidth * wndScaleFactor);
            if (x >= winrect.left && x < winrect.right - titleBarBtnsWidth &&
                    y > winrect.top + borderWidth && y < winrect.top + titleBarHeight) {
                *result = HTCAPTION;
                return true;
            }
            //bottom left corner
            if (x >= winrect.left && x < winrect.left + borderWidth &&
                y < winrect.bottom && y >= winrect.bottom - borderWidth) {
                *result = HTBOTTOMLEFT;
                return true;
            }
            //bottom right corner
            if (x < winrect.right && x >= winrect.right - borderWidth &&
                y < winrect.bottom && y >= winrect.bottom - borderWidth) {
                *result = HTBOTTOMRIGHT;
                return true;
            }
            //top left corner
            if (x >= winrect.left && x < winrect.left + borderWidth &&
                y >= winrect.top && y < winrect.top + borderWidth) {
                *result = HTTOPLEFT;
                return true;
            }
            //top right corner
            if (x < winrect.right && x >= winrect.right - borderWidth &&
                y >= winrect.top && y < winrect.top + borderWidth) {
                *result = HTTOPRIGHT;
                return true;
            }
            //left border
            if (x >= winrect.left && x < winrect.left + borderWidth) {
                *result = HTLEFT;
                return true;
            }
            //right border
            if (x < winrect.right && x >= winrect.right - borderWidth) {
                *result = HTRIGHT;
                return true;
            }
            //bottom border
            if (y < winrect.bottom && y >= winrect.bottom - borderWidth) {
                *result = HTBOTTOM;
                return true;
            }
            //top border
            if (y >= winrect.top && y < winrect.top + borderWidth) {
                *result = HTTOP;
                return true;
            }
            return false;
        }
        default:
            break;
        }
    }
#endif

    return false;
}

void NativeEventFilter::setWndTitleHeight(QWindow *wnd, int wndTitleHeight)
{
#ifdef Q_OS_WIN
    m_wndsParams[wnd->winId()]["TitleHeight"] = wndTitleHeight;
#endif
}

void NativeEventFilter::setWndTitleBarButtonsArea(QWindow *wnd, const QSize &wndTitleBarButtonsArea)
{
#ifdef Q_OS_WIN
    m_wndsParams[wnd->winId()]["TitleBarButtonsArea"] = wndTitleBarButtonsArea;
#endif
}

#include "qml_backend_engine.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QTimer>
#include <QDebug>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

#include <util_misc.h>
#include <native_event_filter.h>

QmlBackendEngine::QmlBackendEngine(QObject *parent) : QObject(parent)
{
    startQmlEngine();
}

QmlBackendEngine::~QmlBackendEngine()
{
    if (m_nef != Q_NULLPTR) {
        delete m_nef;
        m_nef = Q_NULLPTR;
    }
}

void QmlBackendEngine::notifyQmlEvent(QWindow *wnd, const QString &event, const QVariant &params)
{
    if ("ShowWindowMinimize" == event) {
        onShowWindowMinimize(wnd);
        return;
    }

    if ("EnableWindowBorderless" == event) {
        onEnableWindowBorderless(wnd);
        return;
    }

    if ("SetWindowTitleHeight" == event) {
        onSetWindowTitleHeight(wnd, params);
        return;
    }

    if ("SetTitleBarButtonsArea" == event) {
        onSetTitleBarButtonsArea(wnd, params);
        return;
    }
}

void QmlBackendEngine::startQmlEngine()
{
    // handle native events
    m_nef = new NativeEventFilter();
    qApp->installNativeEventFilter(m_nef);
}

void QmlBackendEngine::onShowWindowMinimize(QWindow *wnd)
{
    if (wnd == Q_NULLPTR)
        return;

#ifdef Q_OS_WIN
    ShowWindow((HWND)wnd->winId(), SW_SHOWMINIMIZED);
#endif
}

void QmlBackendEngine::onEnableWindowBorderless(QWindow *wnd)
{
    if (wnd == Q_NULLPTR)
        return;

    Util::Misc::enableWindowBorderless(wnd->winId());
}

void QmlBackendEngine::onSetWindowTitleHeight(QWindow *wnd, const QVariant &param)
{
    if (!param.canConvert<int>() ||
        m_nef == Q_NULLPTR ||
        wnd == Q_NULLPTR)
        return;

    m_nef->setWndTitleHeight(wnd, param.toInt());
}

void QmlBackendEngine::onSetTitleBarButtonsArea(QWindow *wnd, const QVariant &param)
{
    if (!param.canConvert<QSize>() ||
        m_nef == Q_NULLPTR ||
        wnd == Q_NULLPTR)
        return;

    m_nef->setWndTitleBarButtonsArea(wnd, param.toSize());
}

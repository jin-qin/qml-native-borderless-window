#ifndef NATIVE_EVENT_FILTER_H
#define NATIVE_EVENT_FILTER_H

#include <QAbstractNativeEventFilter>
#include <QObject>
#include <QMap>
#include <QSize>

class QWindow;

class NativeEventFilter
        : public QAbstractNativeEventFilter
{
public:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *) override;

    void setWndTitleHeight(QWindow *wnd, int wndTitleHeight);

    void setWndTitleBarButtonsArea(QWindow *wnd, const QSize &wndTitleBarButtonsArea);

private:
    QMap<quint64, QMap<QString, QVariant>> m_wndsParams;
};

#endif // NATIVE_EVENT_FILTER_H

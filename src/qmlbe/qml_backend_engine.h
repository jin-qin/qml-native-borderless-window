#ifndef QML_BACKEND_ENGINE_H
#define QML_BACKEND_ENGINE_H

#include <QObject>
#include <QVariant>
#include <QSize>

class QWindow;
class NativeEventFilter;

class QmlBackendEngine : public QObject
{
    Q_OBJECT

public:
    explicit QmlBackendEngine(QObject *parent = nullptr);
    ~QmlBackendEngine();

    Q_INVOKABLE void notifyQmlEvent(QWindow *, const QString &, const QVariant &params = QVariant());

signals:

public slots:

private:
    void startQmlEngine();

    void onShowWindowMinimize(QWindow *);

    void onEnableWindowBorderless(QWindow *);

    void onSetWindowTitleHeight(QWindow *, const QVariant &param);

    void onSetTitleBarButtonsArea(QWindow *, const QVariant &param);

private:
    NativeEventFilter *m_nef = Q_NULLPTR;
};

#endif // QML_BACKEND_ENGINE_H

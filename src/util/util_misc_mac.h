#ifndef UTIL_MISC_MAC_H
#define UTIL_MISC_MAC_H

#include <QtGlobal>

#ifdef Q_OS_MAC
namespace Util {
namespace Misc{

void enableWindowBorderlessMac(qulonglong wId);

}
}
#endif

#endif // UTIL_MISC_MAC_H

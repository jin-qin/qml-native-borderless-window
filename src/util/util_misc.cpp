#include "util_misc.h"

#ifdef Q_OS_WIN
#include "util_misc_win.h"
#elif defined (Q_OS_MAC)
#include "util_misc_mac.h"
#endif

namespace Util {
namespace Misc {

void enableWindowBorderless(qulonglong wId)
{
#ifdef Q_OS_WIN
    Util::Misc::enableWindowBorderlessWin(wId);
#elif defined (Q_OS_MAC)
    Util::Misc::enableWindowBorderlessMac(wId);
#endif
}

void enableHighDpiSupport()
{
#ifdef Q_OS_WIN
    Util::Misc::enableHighDpiSupportWin();
#elif defined (Q_OS_MAC)
#endif
}

}
}

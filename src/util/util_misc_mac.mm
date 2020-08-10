#include "util_misc_mac.h"

#ifdef Q_OS_MAC

#include <Cocoa/Cocoa.h>

namespace Util {
namespace Misc {

void enableWindowBorderlessMac(qulonglong wId)
{
    NSView* view = (NSView*)wId;
    if (Q_NULLPTR == view) { return; }
    NSWindow *window = view.window;
    if (Q_NULLPTR == window) { return; }

    // set title text and icon to invisible
    window.titleVisibility = NSWindowTitleHidden;   // [OS Version] >= MAC_10_10

    // set title bar to fully transparent
    window.titlebarAppearsTransparent = YES;        // [OS Version] >= MAC_10_10

    // set title bar to cannot move, avoid
    // conflicting with custom dragging action
    window.movable = NO;                            // [OS Version] >= MAC_10_6

    // set view extend to title bar
    window.styleMask |=  NSWindowStyleMaskFullSizeContentView; // [OS Version] >= MAC_10_10
}

}
}
#endif

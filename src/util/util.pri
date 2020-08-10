win32 {
include($$PWD/multiscreen_helper/multiscreen_helper.pri)
}

HEADERS += \
    $$PWD/native_event_filter.h \
    $$PWD/util_misc.h

SOURCES += \
    $$PWD/native_event_filter.cpp \
    $$PWD/util_misc.cpp

win32 {
HEADERS += $$PWD/util_misc_win.h
SOURCES += $$PWD/util_misc_win.cpp
}

macx {
HEADERS += $$PWD/util_misc_mac.h
SOURCES += $$PWD/util_misc_mac.mm
}

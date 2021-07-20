TEMPLATE = app

QT += qml quick gui widgets

#CONFIG += c++11
CONFIG += qt warn_on c++11 rtti stl thread exceptions

# Name of the target file
TARGET = MarsPlayer

# Codec configuration
CODECFORTR = UTF-8
CODECFORSRC = UTF-8

RESOURCES += qml.qrc

TRANSLATIONS += MarsPlayer_zh_CN.ts

HEADERS += \
    MainApp.h

SOURCES += \
        main.cpp \
    MainApp.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

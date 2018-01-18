#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T06:43:22
#
#-------------------------------------------------

QT       += widgets

TARGET = PaciWidget
TEMPLATE = lib

DEFINES += PACIWIDGET_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    timecodeclock.cpp \
    timebasecombobox.cpp \
    usetimecodeselector.cpp

HEADERS += \
        paciwidget_global.h \ 
    timecodeclock.h \
    timebasecombobox.h \
    usetimecodeselector.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS +=

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CandyQt/release/ -lCandyQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CandyQt/debug/ -lCandyQt
else:unix: LIBS += -L$$OUT_PWD/../CandyQt/ -lCandyQt

INCLUDEPATH += $$PWD/../CandyQt
DEPENDPATH += $$PWD/../CandyQt

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PaciCore/release/ -lPaciCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PaciCore/debug/ -lPaciCore
else:unix: LIBS += -L$$OUT_PWD/../PaciCore/ -lPaciCore

INCLUDEPATH += $$PWD/../PaciCore
DEPENDPATH += $$PWD/../PaciCore

RESOURCES += \
    widget_resource.qrc

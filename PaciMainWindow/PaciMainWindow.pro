#-------------------------------------------------
#
# Project created by QtCreator 2017-12-13T21:09:36
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaciMainWindow
TEMPLATE = app

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
        main.cpp \
        pacimainwindow.cpp \
    widgets/tracksidebar.cpp \
    widgets/trackbutton.cpp \
    format_handler/formatprofile.cpp \
    format_handler/multiloader.cpp \
#    sequencedoc.cpp
    format_handler/multisaver.cpp \
    sequencedoc.cpp \
    widgets/clipstable.cpp \
    widgets/clipstablemodel.cpp

HEADERS += \
        pacimainwindow.h \
    widgets/tracksidebar.h \
    widgets/trackbutton.h \
    format_handler/formatprofile.h \
    format_handler/multiloader.h \
#    sequencedoc.h
    format_handler/multisaver.h \
    sequencedoc.h \
    widgets/clipstable.h \
    widgets/clipstablemodel.h

FORMS += \
        pacimainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PaciWidget/release/ -lPaciWidget
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PaciWidget/debug/ -lPaciWidget
else:unix: LIBS += -L$$OUT_PWD/../PaciWidget/ -lPaciWidget

INCLUDEPATH += $$PWD/../PaciWidget
DEPENDPATH += $$PWD/../PaciWidget

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PaciCore/release/ -lPaciCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PaciCore/debug/ -lPaciCore
else:unix: LIBS += -L$$OUT_PWD/../PaciCore/ -lPaciCore

INCLUDEPATH += $$PWD/../PaciCore
DEPENDPATH += $$PWD/../PaciCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CandyQt/release/ -lCandyQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CandyQt/debug/ -lCandyQt
else:unix: LIBS += -L$$OUT_PWD/../CandyQt/ -lCandyQt

INCLUDEPATH += $$PWD/../CandyQt
DEPENDPATH += $$PWD/../CandyQt

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PaciFormat/release/ -lPaciFormat
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PaciFormat/debug/ -lPaciFormat
else:unix: LIBS += -L$$OUT_PWD/../PaciFormat/ -lPaciFormat

INCLUDEPATH += $$PWD/../PaciFormat
DEPENDPATH += $$PWD/../PaciFormat

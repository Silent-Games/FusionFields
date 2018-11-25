#-------------------------------------------------
#
# Project created by QtCreator 2017-05-13T11:56:13
#
#-------------------------------------------------

QT                    += core gui widgets sql multimedia

TARGET                 = FusionFields
TEMPLATE               = app

SOURCES               += main.cpp \
                         controller.cpp \
                         menu.cpp \
                         button.cpp \
                         config.cpp \
                         fusionfields.cpp \
                         game.cpp \
                         gamefield.cpp \
                         board.cpp \
                         database.cpp \
                         notification.cpp \
                         item.cpp \
                         items.cpp \
                         itemselection.cpp \
                         itemdescription.cpp \
                         menubutton.cpp \
                         xplevelprogress.cpp \
                         itemboard.cpp \
                         challenges.cpp \
                         challenge.cpp \
                         homewidget.cpp \
                         header.cpp \
                         challengetask.cpp \
                         gameendwidget.cpp \
                         data.cpp \
                         animation.cpp \
                         itemgame.cpp \
                         savedatathread.cpp \
                         appinfo.cpp \
                         tutorial1.cpp \
                         label.cpp \
                         tutorial2.cpp

HEADERS               += controller.h \
                         menu.h \
                         button.h \
                         config.h \
                         fusionfields.h \
                         game.h \
                         gamefield.h \
                         board.h \
                         database.h \
                         notification.h \
                         item.h \
                         items.h \
                         itemselection.h \
                         itemdescription.h \
                         menubutton.h \
                         xplevelprogress.h \
                         itemboard.h \
                         challenges.h \
                         challenge.h \
                         homewidget.h \
                         header.h \
                         challengetask.h \
                         gameendwidget.h \
                         data.h \
                         animation.h \
                         itemgame.h \
                         savedatathread.h \
                         appinfo.h \
                         tutorial1.h \
                         label.h \
                         tutorial2.h

FORMS                 += controller.ui \
                         menu.ui \
                         fusionfields.ui

CONFIG                += mobility
MOBILITY               =

OTHER_FILES           += android-sources/AndroidManifest.xml

RESOURCES             += ressourcen.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources


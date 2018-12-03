TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lwt
LIBS += -lwthttp
LIBS += -lwtdbo
LIBS += -lwtdbosqlite3

SOURCES += \
        main.cpp \
    user.cpp \
    user.cpp \
    userslist.cpp \
    mysesion.cpp

HEADERS += \
    user.h \
    userslist.h

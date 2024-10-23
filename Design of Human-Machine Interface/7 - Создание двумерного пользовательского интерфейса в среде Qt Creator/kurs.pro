QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractcalc.cpp \
    calcfactory.cpp \
    calculationfacade.cpp \
    car.cpp \
    cars.cpp \
    carsuse.cpp \
    caruse.cpp \
    client.cpp \
    clients.cpp \
    main.cpp \
    rent.cpp \
    view_controller.cpp \
    widget.cpp

HEADERS += \
    abstractcalc.h \
    calcfactory.h \
    calculationfacade.h \
    car.h \
    cars.h \
    carsuse.h \
    caruse.h \
    client.h \
    clients.h \
    rent.h \
    view_controller.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    lr8.pro

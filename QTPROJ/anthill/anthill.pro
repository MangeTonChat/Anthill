QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ant.cpp \
    anthill.cpp \
    egg.cpp \
    larva.cpp \
    main.cpp \
    map.cpp \
    movingant.cpp \
    pheromone.cpp \
    queen.cpp \
    staticant.cpp \
    view.cpp \
    warrior.cpp \
    worker.cpp

HEADERS += \
    Beef.h \
    ant.h \
    anthill.h \
    egg.h \
    larva.h \
    map.h \
    movingant.h \
    obstacle.h \
    pheromone.h \
    queen.h \
    staticant.h \
    view.h \
    warrior.h \
    worker.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    ../../../../../../AppData/Local/Temp/cobblestone_GukVlR

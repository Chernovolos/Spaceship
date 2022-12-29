QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    asteroid.cpp \
    fallingcircle.cpp \
    game.cpp \
    gamewindow.cpp \
    initmainwindow.cpp \
    laser.cpp \
    main.cpp \
    rules.cpp \
    spaceship.cpp \
    sprite.cpp \
    userlifes.cpp

HEADERS += \
    asteroid.h \
    fallingcircle.h \
    game.h \
    gamewindow.h \
    initmainwindow.h \
    laser.h \
    rules.h \
    spaceship.h \
    sprite.h \
    userlifes.h

FORMS += \
    initmainwindow.ui \
    mainwindow.ui \
    rules.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    .gitignore \
    images/white_heart (2).png

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

CONFIG += console
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Board.cpp \
    Game.cpp \
    MoveCircleItem.cpp \
    Piece.cpp \
    PieceItem.cpp \
    Player.cpp \
    SuperSickAI.cpp \
    main.cpp \
    chess.cpp
    Board.cpp
    Piece.cpp
    Game.cpp

HEADERS += \
    Board.h \
    Game.h \
    MoveCircleItem.h \
    Piece.h \
    PieceItem.h \
    Player.h \
    SuperSickAI.h \
    chess.h
    Board.h
    Game.h
    Piece.h
FORMS += \
    chess.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

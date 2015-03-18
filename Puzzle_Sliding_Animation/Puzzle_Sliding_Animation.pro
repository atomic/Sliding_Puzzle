TEMPLATE = app
CONFIG += console

SOURCES += main.cpp \
    game.cpp

HEADERS += \
    game.h \
    ../slidingpuzzle/node.h \
    ../slidingpuzzle/sliding_puzzle.h \
    ../alex_solution/Node.h \
    ../alex_solution/board.h \
    ../alex_solution/functions.h

CONFIG += c++11

LIBS += -L"/usr/loca/lib"

#------------------------------------------
##Add these lines for SFML:

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "/usr/loca/include"
DEPENDPATH += "/usr/loca/include"


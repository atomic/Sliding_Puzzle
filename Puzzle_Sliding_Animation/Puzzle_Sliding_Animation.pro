TEMPLATE = app
CONFIG += console

SOURCES += main.cpp \
    game.cpp

HEADERS += \
    game.h \
    yekun_solution/node.h \
    yekun_solution/sliding_puzzle.h \
    alex_solution/anode.h \
    alex_solution/board.h \
    alex_solution/functions.h \
    algol/solvability.h

CONFIG += c++11

LIBS += -L"/usr/loca/lib"

#------------------------------------------
##Add these lines for SFML:

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "/usr/loca/include"
DEPENDPATH += "/usr/loca/include"


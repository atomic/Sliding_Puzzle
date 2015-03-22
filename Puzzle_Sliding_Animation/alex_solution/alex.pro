TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp

HEADERS += \
		   board.h \
		   functions.h \
		   anode.h

OTHERFILE += \
#   test.txt \

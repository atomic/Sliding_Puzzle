#
# By Tony Lim, 2015-03-03 16:35
# email: <atomictheorist@gmail.com>
#

CC         = g++
CFLAGS     = -c -Wall -std=c++11
LDFLAGS    =
SOURCES    = main.cpp node.h sliding_puzzle.h
OBJECTS    = $(SOURCES:.cpp=.o)
EXEC   	   = ${notdir ${CURDIR}}.exe

all: $(SOURCES) $(EXEC)
	
$(EXEC): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run: ${EXEC}
	./${EXEC}

clean:
	rm -rf *\.o ${EXEC}


# vim:ft=make
#

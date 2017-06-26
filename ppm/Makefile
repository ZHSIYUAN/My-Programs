CXX = g++-4.9 # compiler
CXXFLAGS = -g -Wall -Werror -std=c++11 -MMD # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}} # makefile name

OBJECTS1 = ppm.o # object files forming executable
EXEC1 = ppm # executable name

OBJECTS2 = include.o # object files forming executable
EXEC2 = include # executable name

OBJECTS = ${OBJECTS1} ${OBJECTS2}
EXECS = ${EXEC1} ${EXEC2}
DEPENDS = ${OBJECTS:.o=.d} # substitute ".o" with ".d"

.PHONY : all clean

all : ${EXECS}

${EXEC1} : ${OBJECTS1}        # link step
	${CXX} $^ -o $@

${EXEC2} : ${OBJECTS2}        # link step
	${CXX} $^ -o $@

${OBJECTS} : ${MAKEFILE_NAME} # OPTIONAL : changes to this file => recompile

-include ${DEPENDS}           # include *.d files containing program dependences

clean :                       # remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}

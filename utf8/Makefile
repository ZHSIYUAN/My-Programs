CXX = g++-4.9									# compiler
CXXFLAGS = -g -Wall -Werror -std=c++11 -MMD	# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS2 = utf8char.o q2.o						# object files forming executable
EXEC2 = utf8ch									# executable name

OBJECTS3 = utf8char.o utf8string.o q3.o		 	# object files forming executable
EXEC3 = utf8str									# executable name

OBJECTS = ${OBJECTS2} ${OBJECTS3}
EXECS = ${EXEC2} ${EXEC3}
DEPENDS = ${OBJECTS:.o=.d}						# substitute ".o" with ".d"

.PHONY : all clean

all : ${EXECS}

${EXEC2} : ${OBJECTS2}							# link step
	${CXX} $^ -o $@

${EXEC3} : ${OBJECTS3}							# link step
	${CXX} $^ -o $@

${OBJECTS} : ${MAKEFILE_NAME}					# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}								# include *.d files containing program dependences

clean :											# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}

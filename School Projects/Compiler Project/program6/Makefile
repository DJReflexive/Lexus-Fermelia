# Makefile
# Lexus Fermelia
# COSC 4785 Fall 2025
# Program 6
# December 2, 2025
#
# The Makefile for program 6.


CXX=g++
CXXFLAGS= -Wall -ggdb
RM=/bin/rm -f
FILES=program6.cpp program6_lex.cpp program6.tab.cpp \
nodes.cpp tables.cpp typecheck.cpp

.PHONY: all clean

all: program6

program6.tab.cpp program6.tab.hpp: program6.ypp
	bison -d program6.ypp

program6_lex.cpp: program6.lpp program6.tab.hpp
	flex++ --warn program6.lpp

program6: ${FILES}
	${CXX} ${CXXFLAGS} ${FILES} -o program6

clean:
	${RM} program6 program6_lex.cpp program6.tab.cpp program6.tab.hpp *.o

# Makefile
# Lexus Fermelia
# COSC 4785 Fall 2025
# Program 5
# November 5, 2025
#
# The Makefile for program 5.


CXX=g++
CXXFLAGS= -Wall -ggdb
RM=/bin/rm -f
FILES=program5.cpp program5_lex.cpp program5.tab.cpp nodes.cpp tables.cpp

.PHONY: all clean

all: program5

program5.tab.cpp program5.tab.hpp: program5.ypp
	bison -d program5.ypp

program5_lex.cpp: program5.lpp program5.tab.hpp
	flex++ --warn program5.lpp

program5: ${FILES}
	${CXX} ${CXXFLAGS} ${FILES} -o program5

clean:
	${RM} program5 program5_lex.cpp program5.tab.cpp program5.tab.hpp *.o

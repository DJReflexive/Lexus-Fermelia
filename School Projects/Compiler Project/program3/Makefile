# Makefile
# Lexus Fermelia
# COSC 4785 Fall 2025
# Program 3
# October 8, 2025
#
# The Makefile for program 3.


CXX=g++
CXXFLAGS= -Wall -ggdb
RM=/bin/rm -f
FILES=program3.cpp program3_lex.cpp program3.tab.cpp nodes.cpp

.PHONY: all clean

all: program3

program3.tab.cpp program3.tab.hpp: program3.ypp
	bison -d program3.ypp

program3_lex.cpp: program3.lpp program3.tab.hpp
	flex++ --warn program3.lpp

program3: ${FILES}
	${CXX} ${CXXFLAGS} ${FILES} -o program3

clean:
	${RM} program3 program3_lex.cpp program3.tab.cpp program3.tab.hpp *.o

# Makefile
# Lexus Fermelia
# COSC 4785 Fall 2025
# Program 4
# October 28, 2025
#
# The Makefile for program 4.


CXX=g++
CXXFLAGS= -Wall -ggdb
RM=/bin/rm -f
FILES=program4.cpp program4_lex.cpp program4.tab.cpp nodes.cpp

.PHONY: all clean

all: program4

program4.tab.cpp program4.tab.hpp: program4.ypp
	bison -d program4.ypp

program4_lex.cpp: program4.lpp program4.tab.hpp
	flex++ --warn program4.lpp

program4: ${FILES}
	${CXX} ${CXXFLAGS} ${FILES} -o program4

clean:
	${RM} program4 program4_lex.cpp program4.tab.cpp program4.tab.hpp *.o

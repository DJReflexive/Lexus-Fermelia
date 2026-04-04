# Makefile
# Lexus Fermelia
# COSC 4785 Fall 2025
# Program 2
# September 13, 2025
#
# The Makefile for program 2.


CXX=g++
CXXFLAGS=-std=c++11 -Wall -ggdb
RM=/bin/rm -f
FILES=program2.cpp program2_lex.cpp LexData.cpp

.PHONY: all clean

all: program2

program2_lex.cpp: program2.lpp tokens.hpp
	flex++ --warn program2.lpp

program2: ${FILES}
	${CXX} ${CXXFLAGS} ${FILES} -o program2

clean:
	${RM} program2 program2_lex.cpp *.o

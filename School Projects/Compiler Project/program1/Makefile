# Makefile
# Lexus Fermelia
# COSC 4785 Fall 2025
# Program 1
# August 28, 2025
#
# The Makefile for program 1.

CXX=g++
CXXFLAGS=-std=c++11 -Wall -ggdb
RM=/bin/rm -f

.PHONY: all clean

all: program1

program1_lex.cpp: program1.lpp tokens.hpp
	flex++ --warn program1.lpp

program1: program1.cpp program1_lex.cpp
	${CXX} ${CXXFLAGS} program1.cpp program1_lex.cpp -o program1

clean:
	\${RM} program1 program1_lex.cpp *.o

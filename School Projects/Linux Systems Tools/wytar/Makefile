# Makefile
# Lexus Fermelia
# COSC 3750, SP 2025
# Homework 6
# March 6, 2025
#
# This file is the Makefile that will compile my
# homework 6 programming assignment


CC=gcc
CFLAGS= -ggdb -Wall -I .

# Files that will be created
OBJS=wytar.o helperFuncs.o


.PHONY: clean tidy


wytar: ${OBJS}
	${CC} ${CFLAGS} -o wytar ${OBJS}

helperFuncs.o: helperFuncs.h helperFuncs.c
	${CC} ${CFLAGS} -c helperFuncs.c



tidy:
	/bin/rm -f *.o

clean: tidy
	/bin/rm -f wytar core



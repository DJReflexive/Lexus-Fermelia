# Makefile
# Lexus Fermelia
# COSC 3750, SP 2025
# Homework 7
# March 31, 2025
#
# This file is the Makefile that will compile my
#   homework 7 programming assignment.


CC=gcc
CFLAGS= -ggdb -Wall -I .

# Files that will be created
OBJS=wytalkC.o wytalkD.o socketfun.o


.PHONY: clean tidy



all:wytalkC wytalkD


wytalkC: ${OBJS}
	${CC} ${CFLAGS} wytalkC.c socketfun.c -o wytalkC

wytalkD: ${OBJS}
	${CC} ${CFLAGS} wytalkD.c socketfun.c -o wytalkD

socketfun.o: socketfun.h socketfun.c
	${CC} ${CFLAGS} -c socketfun.c



tidy:
	/bin/rm -f *.o

clean: tidy
	/bin/rm -f wytalkC wytalkD core



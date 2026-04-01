# Makefile
# Lexus Fermelia
# COSC 3750, SP 2025
# Homework 11
# May 7, 2025
#
# This file is the Makefile that will compile my
#   homework 11 programming assignment.


CC=gcc
CFLAGS= -ggdb -Wall -I .

# Files that will be created
OBJS=matrixFuncs.o


.PHONY: all clean tidy



all: mmult maybe_make_mat

maybe_make_mat:
	@if [ -f make_mat.c ]; then \
		$(MAKE) make_mat; \
	fi

make_mat: make_mat.c ${OBJS}
	${CC} ${CFLAGS} make_mat.c ${OBJS} -o make_mat

mmult: mmult.c ${OBJS} matrix.h helperFuncs.h
	${CC} ${CFLAGS} mmult.c ${OBJS} -o mmult -lpthread

matrixFuncs.o: matrixFuncs.c helperFuncs.h matrix.h
	${CC} ${CFLAGS} -c matrixFuncs.c



tidy:
	/bin/rm -f *.o

clean: tidy
	/bin/rm -f make_mat mmult core



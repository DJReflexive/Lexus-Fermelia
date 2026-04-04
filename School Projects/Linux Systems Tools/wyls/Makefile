# Makefile
# Lexus Fermelia
# COSC 3750, SP 2025
# Homework 5
# February 19, 2025
#
# This file is the Makefile that will compile my
# homework 5 programming assignment


CC=gcc
CFLAGS= -ggdb -Wall -I .


.PHONY: clean


wyls: wyls.c
	${CC} ${CFLAGS} -o wyls wyls.c


clean:
	/bin/rm -f wyls core

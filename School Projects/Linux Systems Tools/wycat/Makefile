# Makefile
# Lexus Fermelia
# COSC 3750, SP 2025
# Homework 4
# February 14, 2025
#
# This file is the Makefile that will compile my
# homework 4 programming assignment


CC=gcc
CFLAGS= -ggdb -Wall -I .


.PHONY: tidy clean


wycat: wycat.c
	${CC} ${CFLAGS} -o wycat wycat.c


clean:
	/bin/rm -f wycat core

# Makefile
# Lexus Fermelia
# COSC 3750, SP 2025
# Homework 8
# April 18, 2025
#
# The Makefile for Homework 8 program.

CC = gcc
CFLAGS = -ggdb -Wall
OBJS = wyshell.o wyscanner.o tokenPrinting.o

.PHONY: clean tidy


wyshell: $(OBJS)
	$(CC) $(CFLAGS) -o wyshell $(OBJS)

wyshell.o: wyshell.c wyscanner.h
	$(CC) $(CFLAGS) -c wyshell.c

wyscanner.o: wyscanner.c wyscanner.h
	$(CC) $(CFLAGS) -c wyscanner.c

tokenPrinting.o: tokenPrinting.c helperFuncs.h
	$(CC) $(CFLAGS) -c tokenPrinting.c


clean:
	rm -f wyshell

tidy:
	rm -f *.o *~ core


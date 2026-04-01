# Makefile
# Lexus Fermelia
# COSC 3750, SP 2025
# Homework 9
# April 20, 2025
#
# The Makefile for Homework 9 program.

CC = gcc
CFLAGS = -ggdb -Wall -Wno-unused-function
OBJS = wyshell.o wyscanner.o cleanup.o execution.o

.PHONY: clean tidy


wyshell: $(OBJS)
	$(CC) $(CFLAGS) -o wyshell $(OBJS)

wyshell.o: wyshell.c wyscanner.h
	$(CC) $(CFLAGS) -c wyshell.c

wyscanner.o: wyscanner.c wyscanner.h
	$(CC) $(CFLAGS) -c wyscanner.c
cleanup.o: cleanup.c helperFuncs.h
	$(CC) $(CFLAGS) -c cleanup.c
execution.o: execution.c helperFuncs.h
	$(CC) ${CFLAGS} -c execution.c


tidy:
	rm -f *.o *~ core


clean: tidy
	rm -f wyshell

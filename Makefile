CTARGET = tttoe
CFLAGS = -Wall -O2 -pedantic-errors -std=c11

default: all

all:
	gcc ${CTARGET}.c -o Prog ${CFLAGS}

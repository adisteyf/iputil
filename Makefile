.POSIX:

SRC = $(wildcard *.c)

all: iputil
include config.mk

iputil:
	${CC} ${SRC} -o $@ ${CFLAGS}

.PHONY: iputil all

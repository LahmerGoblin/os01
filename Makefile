CC = gcc
CFLAGS = -std=c99 -pedantic -D_XOPEN_SOURCE=600 -Wall


all: hello

clean: 
	rm *.exe *.o
hello: 
	${CC} ${CFLAGS} -o hello.exe hello.c



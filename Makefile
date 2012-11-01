CC = gcc
CFLAGS = -std=c99 -pedantic -D_XOPEN_SOURCE=600 -Wall


all: hello prompt

clean: 
	rm *.exe *.o
hello: prompt
	${CC} ${CFLAGS} -o hello.exe hello.c
prompt: 
	${CC} ${CFLAGS} -o prompt.exe prompt.c shellutils.c

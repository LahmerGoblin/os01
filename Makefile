CC = gcc
CFLAGS = -std=c99 -pedantic -D_XOPEN_SOURCE=600 -Wall

run:
	./bin/parse.exe

all: hello prompt parse
	mkdir bin
	mv hello.exe prompt.exe parse.exe bin/

clean: 
	rm -rf bin/ *.exe *.o
hello: prompt
	${CC} ${CFLAGS} -o hello.exe hello.c
prompt: 
	${CC} ${CFLAGS} -o prompt.exe prompt.c shellutils.c
parse: 
	${CC} ${CFLAGS} -o parse.exe parse.c shellutils.c

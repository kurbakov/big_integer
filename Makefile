CC = g++
CFLAGS = -O3 -Wall -std=c++14

main:
	${CC} ${CFLAGS} -o $@ main.cpp

clean:
	rm -f main
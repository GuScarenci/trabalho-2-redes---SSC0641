CC=g++
CFLAGS=-Iinclude

trabalho2: main.o camadaEnlace.o
	\$(CC) -o trabalho2 main.o camadaEnlace.o

main.o: src/main.cpp
	\$(CC) -c src/main.cpp

camadaEnlace.o: src/camadaEnlace.cpp include/camadaEnlace.h
	\$(CC) -c src/camadaEnlace.cpp

clean:
	rm -f *.o trabalho2
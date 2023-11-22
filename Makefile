CC=g++
CFLAGS=-Iinclude

trabalho2: main.o meio.o transmissor.o receptor.o
	\$(CC) -o trabalho2 main.o meio.o transmissor.o receptor.o

main.o: src/main.cpp
	\$(CC) -c src/main.cpp

meio.o: src/meio.cpp include/meio.h
	\$(CC) -c src/meio.cpp

transmissor.o: src/transmissor.cpp include/transmissor.h
	\$(CC) -c src/transmissor.cpp

receptor.o: src/receptor.cpp include/receptor.h
	\$(CC) -c src/receptor.cpp

clean:
	rm -f *.o trabalho2
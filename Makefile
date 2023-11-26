CC=g++
CFLAGS=-Iinclude

trabalho2: main.o meio.o transmissor.o receptor.o helper.o
	\$(CC) -o trabalho2 main.o meio.o transmissor.o receptor.o helper.o

main.o: src/main.cpp
	\$(CC) -c -g src/main.cpp

meio.o: src/meio.cpp include/meio.h
	\$(CC) -c -g src/meio.cpp

transmissor.o: src/transmissor.cpp include/transmissor.h
	\$(CC) -c -g src/transmissor.cpp

receptor.o: src/receptor.cpp include/receptor.h
	\$(CC) -c -g src/receptor.cpp

helper.o: src/helper.cpp include/helper.h
	\$(CC) -c -g src/helper.cpp

clean:
	rm -f *.o trabalho2
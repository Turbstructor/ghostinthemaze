CC = g++
TARGET = p2.out

$(TARGET) : .p2.o .check.o
	$(CC) -o $(TARGET) .p2.o .check.o -lpthread

.p2.o : p2.cpp
	$(CC) -c -o .p2.o p2.cpp

clean : 
	rm .p2.o $(TARGET)

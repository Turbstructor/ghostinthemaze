CC = g++
TARGET = p1.out

$(TARGET) : .p1.o .check.o
	$(CC) -o $(TARGET) .p1.o .check.o -lpthread

.p1.o : p1.cpp
	$(CC) -c -o .p1.o p1.cpp

clean : 
	rm .p1.o $(TARGET)

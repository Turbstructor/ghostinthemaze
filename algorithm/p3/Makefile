CC = g++
TARGET = p3.out

$(TARGET) : .p3.o .check.o
	$(CC) -o $(TARGET) .p3.o .check.o -lpthread

.p3.o : p3.cpp
	$(CC) -c -o .p3.o p3.cpp


clean : 
	rm .p3.o $(TARGET)

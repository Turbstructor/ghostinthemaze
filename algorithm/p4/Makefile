CC = g++
TARGET = p4.out

$(TARGET) : .p4.o .check.o
	$(CC) -o $(TARGET) .p4.o .check.o -lpthread

.p4.o : p4.cpp
	$(CC) -c -o .p4.o p4.cpp


clean : 
	rm .p4.o $(TARGET)

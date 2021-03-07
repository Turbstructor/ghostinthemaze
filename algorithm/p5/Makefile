CC = g++
TARGET = p5.out

$(TARGET) : .p5.o .check.o
	$(CC) -o $(TARGET) .p5.o .check.o -lpthread

.p5.o : p5.cpp
	$(CC) -c -o .p5.o p5.cpp


clean : 
	rm .p5.o $(TARGET)

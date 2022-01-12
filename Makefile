
INCLUDE = /usr/include
LIB     = /usr/lib
LINK    = -lamqpcpp -ldl -lev

all: main.o  MyHandler.o
	g++ -Wall -o app main.o MyHandler.o Producer.o -pthread -I./Includes $(LINK)

main.o: MyHandler.o Producer.o
	g++ -c main.cpp -I./Includes -pthread

Producer.o: MyHandler.o
	g++ -c ./Includes/Producer.cpp -pthread

MyHandler.o:
	g++ -c ./Includes/MyHandler.cpp -pthread  -I$(INCLUDE) -L$(LIB)  $(LINK)

clean:
	rm -f  ./app  *.o


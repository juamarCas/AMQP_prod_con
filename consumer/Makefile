
INCLUDE = /usr/include
LIB     = /usr/lib
LINK    = -lamqpcpp -ldl -lev 
FLAGS   = -Wall -g -O3

all: main.o consumer.o  MyHandler.o
	g++ $(FLAGS) -o app main.o Consumer.o  MyHandler.o -pthread -I./Includes $(LINK)

main.o: MyHandler.o consumer.o
	g++ -c main.cpp -I./Includes -pthread

consumer.o: MyHandler.o
	g++ -c ./Includes/Consumer.cpp -pthread

MyHandler.o:
	g++ -c ./Includes/MyHandler.cpp -pthread  -I$(INCLUDE) -L$(LIB)  $(LINK)

clean:
	rm -f  ./app  *.o


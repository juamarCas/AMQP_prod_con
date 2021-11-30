
INCLUDE = /usr/include
LIB     = /usr/lib
LINK    = -lamqpcpp -ldl -lev 
FLAGS   = -Wall -g

all: main.o  MyHandler.o
	g++ $(FLAGS) -o app main.o MyHandler.o -pthread -I./Includes $(LINK)

main.o: MyHandler.o
	g++ -c main.cpp -I./Includes -pthread

MyHandler.o:
	g++ -c ./Includes/MyHandler.cpp -pthread  -I$(INCLUDE) -L$(LIB)  $(LINK)

clean:
	rm -f  ./app  *.o


INCLUDE = /usr/include
LIB     = /usr/lib
LINK    = -lamqpcpp -ldl -lev 
FLAGS   = -Wall -g -O3

all: main.o
	g++ $(FLAGS) -o app main.o Consumer.o Producer.o  MyHandler.o -pthread -I./Includes $(LINK)

main.o: Producer.o Consumer.o
	g++ -c main.cpp -I./Includes -pthread

Producer.o: MyHandler.o
	g++ -c Producer.cpp -I./Includes -pthread

Consumer.o: MyHandler.o
	g++ -c Consumer.cpp -I./Includes -pthread

MyHandler.o: 
	g++ -c MyHandler.cpp -I./Includes -pthread -I$(INCLUDE) -L$(LIB)  $(LINK)
	
clean: 
	rm -f  ./app  *.o
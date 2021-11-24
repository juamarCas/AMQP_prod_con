
INCLUDE = /usr/include
LIB     = /usr/lib
LINK    = -lamqpcpp -ldl -lev

all: main.o  MyHandler.o
        g++ -Wall -o app main.o MyHandler.o -pthread $(LINK)

main.o:
        g++ -c main.cpp -I./Includes -pthread $(LINK)

MyHandler.o:
        g++ -c ./Includes/MyHandler.cpp -pthread  -I$(INCLUDE) -L$(LIB)  $(LINK)

clean:
        rm -f  ./app  *.o


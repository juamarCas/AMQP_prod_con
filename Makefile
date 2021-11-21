INCLUDE = /usr/include
LINK = /usr/lib

all: 
	g++ -Wall main.cpp -o app -pthread -I$(INCLUDE) -L$(LINK) -lamqpcpp -ldl -lev
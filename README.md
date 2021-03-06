# AMQP CPP client 

This repository contain test code in order to implement a communication with two procceses via AMQP protocol.<br/>

The project contains a C++ script for produce messages and C++ script (in consumer folder) to consume messages from a queue.

## Preparing the development environment

1) Install [AMQ-CPP](https://github.com/CopernicaMarketingSoftware/AMQP-CPP/blob/master/examples/libevent.cpp)
2) If you have the _"ev.h not found error"_ install the following package: 
```
sudo apt install libev-dev
```
4) If you install the AMQ-CPP library in a non-default folder, specify the *INCLUDE* and *LINK* routes variables in the Makefile where did you install the libraries. 
5) Compile the example code with the following command. 
```
make
```
6) Run the application
```
./app
```

7) you can clean the folder with the following command. 
```
make clean
```

## JSON
For serializing and parsing JSON the project uses [JSON for modern C++](https://github.com/nlohmann/json)

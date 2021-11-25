#include <iostream>
#include <string>
#include "MyHandler.h"

int main()
{
   auto *loop = EV_DEFAULT;
   MyHandler myHandler(loop);
   AMQP::Address address("amqp://guest:guest@localhost/");
   AMQP::TcpConnection connection(&myHandler, address);

   AMQP::TcpChannel channel(&connection);
   channel.declareQueue("myqueue").onSuccess([&channel](const std::string &name, uint32_t messageCount, uint32_t consumercount){
            std::cout<<"declared queue: myqueue"<<std::endl;
            while(1){
               std::string msg; 
               std::cout<<"type a message: "<<std::endl;
               std::getline(std::cin, msg);  
               channel.publish("", "myqueue", msg); 
            }
   });


   ev_run(loop);

   return 0;

}

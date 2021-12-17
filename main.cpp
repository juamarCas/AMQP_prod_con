#include <iostream>
#include <string>
#include "json.hpp"
#include "MyHandler.h"

int main()
{

   auto *loop = EV_DEFAULT;
   MyHandler myHandler(loop);
   AMQP::Address address("amqp://guest:guest@localhost/");
   AMQP::TcpConnection connection(&myHandler, address); 

   nlohmann::json j;
   int var1 = 15; 
   float var2 = 5.5; 

   j["pos"]  = var1; 
   j["temp"] = var2; 

   std::string msg = j.dump(); 
   AMQP::TcpChannel channel(&connection);
   channel.declareQueue("myqueue").onSuccess([&channel, msg](const std::string &name, uint32_t messageCount, uint32_t consumercount){
            std::cout<<"declared queue: myqueue"<<std::endl;
            while(1){        
               std::cin.get();  
               channel.publish("", "myqueue", msg); 
            }
   });


   ev_run(loop);

   return 0;

}

#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <utility>
#include "MyHandler.h"
#include "json.hpp"
#include "Consumer.h"

#define DEBUG 1
#define LOG(x) std::cout<<x<<std::endl

int main()
{

  auto success_cb = [](const std::string& consumertag){
    #if DEBUG
      LOG("connection has been succesfull!");
    #endif
  };
  auto error_cb   = [](const char *message){};

  /*message received as json format*/
  auto message_cb = [](const std::string& message){
    #if DEBUG
      LOG(message);
    #endif
    //auto j_parsed = nlohmann::json::parse(message); 
    // std::cout<<j_parsed.dump(4)<<j_receive<<"\n\n"; 
  };

  Consumer::C_callbacks cbb{
	  success_cb, 
	  error_cb, 
	  message_cb 
  };
   std::string user     = "test"; 
   std::string pass     = "test123"; 
   std::string host     = "localhost"; 
   std::string vhost    = "";
   std::string queue    = "fp";
   std::string exchange = "exchange"; 

   IAMQP * consumer = new Consumer(user, pass, host, vhost, queue, cbb);
   std::thread Consumer_Thread(
      [&consumer](){
        consumer->Start();
      }
   
   );
   Consumer_Thread.join(); 
  
    delete consumer; 
    return 0;

}


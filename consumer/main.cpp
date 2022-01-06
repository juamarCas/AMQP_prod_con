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

  auto success_cb = [](const std::string& consumertag){std::cout<<"hello from cb!"<<std::endl;};
  auto error_cb   = [](const char *message){}; 
  auto message_cb = [](const std::string& message){
    LOG(message);
  };

  Consumer::C_callbacks cbb{
	  success_cb, 
	  error_cb, 
	  message_cb 
  };
   std::string user  = "guest"; 
   std::string pass  = "guest"; 
   std::string host  = "localhost"; 
   std::string vhost = "";
   std::string queue = "myqueue";

   IAMQP * consumer = new Consumer(user, pass, host, vhost, queue,cbb);
   std::thread Consumer_Thread(
      [&consumer](){
        consumer->Start();
      }
   
   );
   Consumer_Thread.join(); 
   // callback function that is called when the consume operation starts
   // auto j_parsed = nlohmann::json::parse(j_final); 
   // std::cout<<j_parsed.dump(4)<<j_receive<<"\n\n"; 
   

    return 0;

}


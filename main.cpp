#include <iostream>
#include <string>
#include <thread>
#include "json.hpp"
#include "Producer.h"

int main()
{
  auto success_cb = [](const std::string& consumertag){
    
  };
  auto error_cb   = [](const char *message){};

  /*message received as json format*/
  auto message_cb = [](const std::string& message){
    //auto j_parsed = nlohmann::json::parse(message);
    // std::cout<<j_parsed.dump(4)<<j_receive<<"\n\n";
  };

  Producer::P_callbacks cbb{
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

  Producer producer(user, pass, host, vhost, queue, cbb);

  std::thread Producer_Thread(
    [&producer](){
      producer.Start();
    }  
  );

  Producer_Thread.detach();
  while(!producer.GetIsReady()){}
  producer.PublishMsg("Hello"); 
  while(1){}
   
  return 0;
}

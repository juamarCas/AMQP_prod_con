#include <iostream>
#include <string>
#include "MyHandler.h"
#include "json.hpp"
#include "Consumer.h"

#define DEBUG 1
#define LOG(x) std::cout<<x<<std::endl

void success_callback(); 
void start_callback(); 
void error_callback(); 
void message_callback(const std::string& data);

int main()
{
   auto *loop = EV_DEFAULT;
   MyHandler myHandler(loop);
   AMQP::Address address("amqp://guest:guest@localhost/");
   AMQP::TcpConnection connection(&myHandler, address);

   AMQP::TcpChannel channel(&connection);
   channel.declareQueue("myqueue").onSuccess([&channel](const std::string &name, uint32_t messageCount, uint32_t consumercount){
            std::cout<<"declared queue"<<std::endl;
   });

  // Consumer::C_callbacks cbb(ssc, stc, erc, msc); 
  Consumer::C_callbacks cbb{
	&success_callback, 
	&start_callback, 
	&error_callback, 
	&message_callback
  };
   std::string name  = "juanito"; 
   std::string pass  = "1234"; 
   std::string host  = "/"; 
   std::string vhost = " ";
#if DEBUG
	LOG("hey");
#endif 
   IAMQP * consumer = new Consumer(name, pass, host, vhost, cbb);
   consumer->Start();
   // callback function that is called when the consume operation starts
   auto startCb = [](const std::string &consumertag) {

    std::cout << "consume operation started" << std::endl;
};

// callback function that is called when the consume operation failed
auto errorCb = [](const char *message) {

    std::cout << "consume operation failed" << std::endl;
};

// consume a message with JSON notation and parse it
auto messageCb = [&channel](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {

    std::cout << "message received:" << std::endl;
      

    char j_receive[message.bodySize() + 1];
    strncpy(j_receive, message.body(), message.bodySize() + 1); 
    j_receive[message.bodySize()] = '\0'; 

    std::string j_final = std::string(j_receive);
    auto j_parsed = nlohmann::json::parse(j_final); 
    std::cout<<j_parsed.dump(4)<<j_receive<<"\n\n"; 
    channel.ack(deliveryTag);
};

channel
    .consume("myqueue")
    .onReceived(messageCb)
    .onSuccess(startCb)
    .onError(errorCb);

    ev_run(loop);

    return 0;

}

void success_callback(){

}

void start_callback(){
	LOG("Hello world from callback");
}

void error_callback(){

}

void message_callback(const std::string& msg){

}

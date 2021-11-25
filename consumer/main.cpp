#include <iostream>
#include <string>
#include "MyHandler.h"
#include "json.hpp"

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
    std::cout.write(message.body(), message.bodySize())<<std::endl;  
    channel.ack(deliveryTag);  

    char j_receive[message.bodySize()];
    strncpy(j_receive, message.body(), message.bodySize()); 

    std::string j_final = std::string(j_receive);
    auto j_parsed = nlohmann::json::parse(j_final); 
    std::cout<<j_parsed.dump(4)<<j_receive<<"\n\n"; 
   
};

channel.consume("myqueue")
       .onReceived(messageCb)
       .onSuccess(startCb)
       .onError(errorCb);

   ev_run(loop);

   return 0;

}

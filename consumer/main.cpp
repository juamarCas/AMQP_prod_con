
#include "MyHandler.h"
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

// callback operation when a message was received
auto messageCb = [&channel](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {

    std::cout << "message received:" << std::endl;
    std::cout.write(message.body(), message.bodySize())<<std::endl;    
    channel.ack(deliveryTag);
};

channel.consume("myqueue")
       .onReceived(messageCb)
       .onSuccess(startCb)
       .onError(errorCb);

   ev_run(loop);

   return 0;

}

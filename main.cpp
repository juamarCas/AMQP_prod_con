
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
            channel.publish("","myqueue","hello world");
            while(1){}
   });


   ev_run(loop);

   return 0;

}

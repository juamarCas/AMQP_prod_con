
#include <ev.h>
#include <amqpcpp.h>
#include <amqpcpp/libev.h>


class MyHandler: public AMQP::LibEvHandler{

    virtual void onAttached(AMQP::TcpConnection *connection) override
    {

     }
    virtual void onConnected(AMQP::TcpConnection *connection) override
    {

    }

    virtual bool onSecured(AMQP::TcpConnection *connection, const SSL *ssl) override
    {
        return true;
    }

    virtual void onReady(AMQP::TcpConnection *connection) override
    {
        std::cout<<"ready"<<std::endl;
    }

    virtual void onError(AMQP::TcpConnection *connection, const char *message) override
    {

    }

    virtual void onClosed(AMQP::TcpConnection *connection) override
    {

    }

    virtual void onLost(AMQP::TcpConnection *connection) override
    {

    }

    virtual void onDetached(AMQP::TcpConnection *connection) override
    {

    }

public:
        MyHandler(struct ev_loop *loop): AMQP::LibEvHandler(loop){}
};



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

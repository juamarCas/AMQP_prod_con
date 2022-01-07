#ifndef PRODUCER_H
#define PRODUCER_H
#include "IAMQP.h"

class Producer: public IAMQP{
    public: 

    private: 
        MyHandler           m_myHandler; 
        AMQP::Adress        m_adress; 
        AMQP::TcpConnection m_connection;
        AMQP::TcpChannel    m_channel
    public: 

        /**
        *@brief constructor for AMQP producer
        *@param user Username to sign in to the AMQP broker
        *@param password Password to sign in to the AMQP broker
        *@param host IP address of the AMQP broker
        *@param vhost Vhost the user wants to sign in
        *@param queue AMQP queue the channel will subscribe
        *@param exchange AMQP exchange the queue will be binded
        *@param routingKey AMQP routing key for the channel
        *@param callbacks struct of functions defined by the user that will be excecuted depending of the action
        */
        Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, C_callbacks& callbacks);
        Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, C_callbacks& callbacks);
        
        /*
        *Not implemented yet
        */
        Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, const std::string& routingKey, C_callbacks& callbacks);
        Producer(const Producer&) = delete;
        ~Producer(){} 
        void Start(); 
};

#endif
#ifndef PRODUCER_H
#define PRODUCER_H
#include "IAMQP.h"
#include <utility>


/**
*@brief Class object used to create a consumer client
*/
class Producer: public IAMQP{

    public:
        typedef struct Producer_callbacks{
            IAMQP::vf_s  success_callback; 
            IAMQP::vf_ca error_callback; 
            IAMQP::vf_s  message_callback;
        }P_callbacks;
    private: 
       
        
        P_callbacks * m_callbacks;
        IAMQP::vf_s   PublishMSGLmbda; 
	    //AMQP::TcpChannel m_channel(AMQP::TcpConnection *);

        /**
        *@brief indicates whenever a queue, exchange o routing key is ready. Helper method to start the publisher
        */
        

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
        Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, P_callbacks& callbacks);
        Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, IAMQP::QEConf conf, P_callbacks& callbacks);
        Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, const std::string& routingKey, IAMQP::QEConf conf,P_callbacks& callbacks);
       
        Producer(const Producer&) = delete;
        ~Producer(){} 
        void Start(); 


        /**
        *@brief publish a message to the AMQP server
        *@param queue, the queue the message is for
        *@param exchange, the exchange the message is for
        *@param routeKey, the routing ey the message is for
        *@param msg, actual message, duh
        */
        void PublishMsg(const std::string& msg);
        void PublishMsg(const std::string& queue, const std::string& msg); 
        void PublishMsg(const std::string& queue, const std::string& exchange, const std::string& msg);
        void PublishMsg(const std::string& queue, const std::string& exchange, const std::string& routeKey, const std::string& msg);

        /*topic usage methods*/
        void Subscribe(const std::string& topic);
        void PublishToTopic(const std::string& msg, const std::string& topic);

        inline bool GetIsReady(){ return isReady; }
};

#endif
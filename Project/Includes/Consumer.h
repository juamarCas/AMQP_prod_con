#ifndef CONSUMER_H
#define CONSUMER_H
#define CONSUMER_DEBUG 1
#include "IAMQP.h"

/**
*@brief Class for consumer of AMQP broker
*/

class Consumer: public IAMQP{



public:
/**
*@brief callback structure. It uses the typedefs defined in IAMQP class
*@brief success_callback is a function that will excecute once the client is connected to the broker
*@brief error_callback is a function excecuted when an error ocurrs
*@brief message_callback is a function that is called everytime a message is received
*/
    typedef struct Consumer_callbacks{
        IAMQP::vf_s  success_callback; 
        IAMQP::vf_ca error_callback; 
        IAMQP::vf_s  message_callback;
    }C_callbacks;

private: 
	C_callbacks * m_callbacks;

public:
    /**
    *@brief constructor for AMQP consumer
    *@param user Username to sign in to the AMQP broker
    *@param password Password to sign in to the AMQP broker
    *@param host IP address of the AMQP broker
    *@param vhost Vhost the user wants to sign in
    *@param queue AMQP queue the channel will subscribe
    *@param exchange AMQP exchange the queue will be binded
    *@param routingKey AMQP routing key for the channel
    *@param callbacks struct of functions defined by the user that will be excecuted depending of the action
    */
    Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, C_callbacks& callbacks);
    Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, const std::string& routingKey, IAMQP::QEConf conf, C_callbacks& callbacks);
    Consumer(const Consumer&) = delete;
    ~Consumer(){} 

    void SetQueue(const std::string& queue, const std::function<void(void)>& callback); 

    /**
    *@brief starts consumer operations
    */
    void Start();

};

#endif

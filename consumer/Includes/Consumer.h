#include <iostream>
#include <functional>
#include "MyHandler.h"
#include "IAMQP.h"
#ifndef CONSUMER_H
#define CONSUMER_H
#define CONSUMER_DEBUG 1

/**
*@brief Class for consumer of AMQP broker
*/

class Consumer: public IAMQP{

//Typedefs -------------------------------
/**
* @brief abbreviation for function declaration as variables
*/
    typedef std::function<void()>                        vf;  
    typedef std::function<void(const std::string& msg)>  vf_s;
    typedef std::function<void(const char *message)>     vf_ca; 

public:
/**
*@brief callback structure. It uses the typedefs defined earlier
*@brief success_callback is a function that will excecute once the client is connected to the broker
*@brief error_callback is a function excecuted when an error ocurrs
*@brief message_callback is a function that is called everytime a message is received
*/
    typedef struct Consumer_callbacks{
        vf_s  success_callback; 
        vf_ca error_callback; 
        vf_s  message_callback;
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
    *@param queuue AMQP queue the channel will subscribe
    *@param exchange AMQP exchange the queue will be binded
    *@param routingKey AMQP routing key for the channel
    *@param callbacks struct of functions defined by the user that will be excecuted depending of the action
    */
    Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, C_callbacks& callbacks);
    Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, C_callbacks& callbacks);
    Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, const std::string& routingKey, C_callbacks& callbacks);
    Consumer(const Consumer&) = delete;
    ~Consumer(){} 

    void SetQueue(const std::string& queue, const std::function<void(void)>& callback); 

    /**
    *@brief starts consumer operations
    */
    void Start();

};

#endif

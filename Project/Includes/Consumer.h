#ifndef CONSUMER_H
#define CONSUMER_H
#include "IAMQP.h"
#define DEBUG 1
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
    Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, IAMQP::QEConf conf, C_callbacks& callbacks);
    Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& exchange, IAMQP::QEConf conf, C_callbacks& callbacks);
    Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, IAMQP::QEConf conf, C_callbacks& callbacks);
    Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, const std::string& routingKey, IAMQP::QEConf conf, C_callbacks& callbacks);
    Consumer(const Consumer&) = delete;
    ~Consumer(){
        delete m_myHandler;
        delete m_address;
        delete m_connection;
        delete m_channel;
    } 

    void SetQueue(const std::string& queue, const std::function<void(void)>& callback); 

    /**
    *@brief starts consumer operations
    */
    void Start();

    /*Topic usage methods*/
    /**
     * @brief Subscribe to a topic on the AMQP broker
     * 
     * @param topic topic to be subscribe
     * example: sensor.building1.*
     */
    void Subscribe(const std::string& topic);

    /**
     * @brief Send a message to a topic
     * 
     * @param msg message to be sent
     * @param topic topic the message is going to be sent
     */
    void PublishToTopic(const std::string& msg, const std::string& topic);

    /**
     * @brief Get the Is Ready object
     * 
     * @return true it has started operating
     * @return false it hasn't started operating
     */
    inline bool GetIsReady(){ return isReady; }
};

#endif

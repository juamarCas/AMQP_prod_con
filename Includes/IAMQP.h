#include <iostream>
#include <functional>
#include "MyHandler.h"
#ifndef IAMQP_H
#define IAMQP_H
#define IAMQP_DEBUG 1

class IAMQP{

protected:
    /*used to know which construtor was called*/
    enum AMQP_STATE {QUEUE_ONLY = 0, QUEUE_EXCHANGE, QUEUE_EXCHANGE_RK};
    //Typedefs -------------------------------
    /**
    * @brief abbreviation for function declaration as variables
    */
    typedef std::function<void()>                        vf;  
    typedef std::function<void(const std::string& msg)>  vf_s;
    typedef std::function<void(const char *message)>     vf_ca; 

    AMQP_STATE m_amqpState; 
private: 

public: 
   

    IAMQP(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue):
    m_user(user), m_password(password), m_host(host), m_vhost(vhost), m_queue(queue)
    {
        m_url = "amqp://" + m_user + ":" + m_password + "@" + m_host + "/" + m_vhost;
        m_amqpState = QUEUE_ONLY;
    }

    IAMQP(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange):
    m_user(user), m_password(password), m_host(host), m_vhost(vhost), m_queue(queue), m_exchange(exchange)
    {
        m_url = "amqp://" + m_user + ":" + m_password + "@" + m_host + "/" + m_vhost;
        m_amqpState = QUEUE_EXCHANGE;
    }

    IAMQP(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, const std::string& routingKey):
    m_user(user), m_password(password), m_host(host), m_vhost(vhost), m_queue(queue), m_exchange(exchange), m_routeKey(routingKey)
    {
        m_url = "amqp://" + m_user + ":" + m_password + "@" + m_host + "/" + m_vhost;
        m_amqpState = QUEUE_EXCHANGE_RK; 
    }

    virtual ~IAMQP(){} 
    IAMQP(const IAMQP&) = delete;

   virtual void Start() = 0; 
	
protected:
    std::string m_user; 
    std::string m_password; 
    std::string m_host; 
    std::string m_vhost;

    std::string m_queue;
    std::string m_exchange;
    std::string m_routeKey;

    std::string m_url;

    inline AMQP_STATE Get_AMQP_State(){ 
        return m_amqpState;
    }

};

#endif

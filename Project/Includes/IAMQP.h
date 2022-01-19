#ifndef IAMQP_H
#define IAMQP_H

#define IAMQP_DEBUG 1
#include <iostream>
#include <functional>
#include "MyHandler.h"

class IAMQP{

protected:
    /*used to know which construtor was called*/
    enum AMQP_STATE {QUEUE_ONLY = 0, QUEUE_EXCHANGE, QUEUE_EXCHANGE_RK, EXCHANGE_ONLY, SERVER_ASSIGNS};

    //Typedefs -------------------------------
    /**
    * @brief abbreviation for function declaration as variables
    */
    typedef std::function<void()>                                                 vf;
    typedef std::function<void(const std::string& str)>                           vf_s;
    typedef std::function<void(const std::string& str1, const std::string& str2)> vf_ss;
    typedef std::function<void(const char *message)>                              vf_ca;

    vf_s  subscribeTopicLmda;
    vf_ss publishToTopicLmda;

private:
    AMQP_STATE m_amqpState;

public:
   typedef struct Queue_Exchange_Configure {
       int QueueFlags;
       int ExchangeFlags;
       AMQP::ExchangeType ETypes;
   }QEConf;

    IAMQP(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue):
    m_user(user), m_password(password), m_host(host), m_vhost(vhost), m_queue(queue)
    {
        m_url = "amqp://" + m_user + ":" + m_password + "@" + m_host + "/" + m_vhost;
        m_amqpState = QUEUE_ONLY;
    }

    IAMQP(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, QEConf qeconf):
    m_user(user), m_password(password), m_host(host), m_vhost(vhost), m_queue(queue), m_exchange(exchange), m_conf(qeconf)
    {
        m_url = "amqp://" + m_user + ":" + m_password + "@" + m_host + "/" + m_vhost;
        m_amqpState = QUEUE_EXCHANGE;
    }

    IAMQP(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& exchange, QEConf qeconf):
    m_user(user), m_password(password), m_host(host), m_vhost(vhost), m_exchange(exchange), m_conf(qeconf)
    {
        m_url = "amqp://" + m_user + ":" + m_password + "@" + m_host + "/" + m_vhost;
        m_amqpState = EXCHANGE_ONLY;
    }

    IAMQP(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, QEConf qeconf):
    m_user(user), m_password(password), m_host(host), m_vhost(vhost), m_conf(qeconf)
    {
        m_url = "amqp://" + m_user + ":" + m_password + "@" + m_host + "/" + m_vhost;
        m_amqpState = SERVER_ASSIGNS;
    }

    IAMQP(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, const std::string& routingKey, QEConf qeconf):
    m_user(user), m_password(password), m_host(host), m_vhost(vhost), m_queue(queue), m_exchange(exchange), m_routeKey(routingKey), m_conf(qeconf)
    {
        m_url = "amqp://" + m_user + ":" + m_password + "@" + m_host + "/" + m_vhost;
        m_amqpState = QUEUE_EXCHANGE_RK; 
    }

    virtual ~IAMQP(){}

    /*No copy constructors can be called*/
    IAMQP(const IAMQP&) = delete;
    IAMQP &operator=(const IAMQP &IAMQP) = delete;

    virtual void Start() = 0;
    virtual void Subscribe(const std::string& topic) = 0;
    virtual void PublishToTopic(const std::string& msg, const std::string& topic) = 0;

protected:
    std::string m_user;
    std::string m_password;
    std::string m_host;
    std::string m_vhost;

    std::string m_queue;
    std::string m_exchange;
    std::string m_routeKey;

    std::string m_url;

    int m_flags;
    QEConf m_conf;
    AMQP::ExchangeType m_types;
    bool isReady; 
    inline AMQP_STATE Get_AMQP_State(){
        return m_amqpState;
    }

};

#endif

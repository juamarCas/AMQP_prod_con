#include <iostream>

#ifndef IAMQP_H
#define IAMQP_H

#define IAMQP_DEBUG 1

class IAMQP{
public: 

    IAMQP(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost):
    m_user(user), m_password(password), m_host(host), m_vhost(vhost)
    {
        m_url = "amqp//" + user + ":" + password + "@" + host + "/" + vhost;
#if IAMQP_DEBUG
        std::cout<<m_url<<std::endl;
#endif
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

};

#endif

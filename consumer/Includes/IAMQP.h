#include <iostream>

#ifndef IAMQP_H
#define IAMQP_H

class IAMQP{
public: 

    IAMQP(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost):
    m_user(user), m_password(password), m_host(host), m_vhost(vhost)
    {
        
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

};

#endif

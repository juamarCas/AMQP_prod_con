#include <iostream>

#ifndef CAMQP_H
#define CAMQP_H

class CAMQP{
public: 

    CAMQP(std::string&& user, std::string&& password, std::string&& host, std::string&& vhost):
    m_user(user), m_password(password), m_host(host), m_vhost(vhost)
    {
        
    } 
    CAMQP(const CAMQP&) = delete; 

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
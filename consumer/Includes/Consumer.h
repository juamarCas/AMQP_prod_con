#include <iostream>
#include <functional>
#include "MyHandler.h"
#include "CAMQP.h"
#ifndef CONSUMER_H
#define CONSUMER_H
/*
*@brief Class for consumer of AMQP broker
*/
class Consumer: public CAMQP{

public:
/*
a struct that contains callbacks for receiving data
*/
typedef struct Consumer_callbacks{
    Consumer_callbacks(); 
    std::function<void()>&                      success_callback;
    std::function<void()>&                      start_callback;
    std::function<void()>&                      error_callback; 
    std::function<void(std::string&& message)>& message_callback;
}C_callbacks;

private: 
 
public:
    Consumer(std::string&& user, std::string&& password, std::string&& host, std::string&& vhost);
    Consumer(const Consumer&) = delete;

    void SetQueue(std::string&& queue, const std::function<void(void)>& callback); 

    void Start();

    C_callbacks  m_callbacks; 

};

#endif
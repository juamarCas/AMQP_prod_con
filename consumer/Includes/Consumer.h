#include <iostream>
#include <functional>
#include "MyHandler.h"
#include "IAMQP.h"
#ifndef CONSUMER_H
#define CONSUMER_H
#define CONSUMER_DEBUG 1

/*
*@brief Class for consumer of AMQP broker
*/

class Consumer: public IAMQP{

//Typedefs -------------------------------
/*
* abbreviation for function declaration, i'm to lazy to write those declaration over and over
*/
    typedef std::function<void()>                        vf;  
    typedef std::function<void(const std::string& msg)>  vf_s;
    typedef std::function<void(const char *message)>     vf_ca; 

public:
/*
callback containers
*/
    typedef struct Consumer_callbacks{
        vf_s  success_callback; 
        vf_ca error_callback; 
        vf_s  message_callback;
    }C_callbacks;

private: 
	C_callbacks * m_callbacks;

public:
    Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, C_callbacks& callbacks);
    Consumer(const Consumer&) = delete;
    ~Consumer(){} 

    void SetQueue(const std::string& queue, const std::function<void(void)>& callback); 

    void Start();

};

#endif

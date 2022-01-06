#include <iostream>
#include <functional>
#include "MyHandler.h"
#include "IAMQP.h"
#ifndef CONSUMER_H
#define CONSUMER_H
#define CONUMER_DEBUG 1

/*
*@brief Class for consumer of AMQP broker
*/

class Consumer: public IAMQP{

//Typedefs -------------------------------
/*
 * vf   -> void function
 * vf_s -> void function, string parameter 
 */
typedef std::function<void()>                        vf;  
typedef std::function<void(const std::string& msg)>  vf_s;

public:
/*
a struct that contains callbacks for receiving data
*/
typedef struct Consumer_callbacks{
	vf   success_callback;
    vf   start_callback; 
    vf   error_callback; 
    vf_s message_callback;
}C_callbacks;

private: 
	C_callbacks * m_callbacks;
    
public:
    Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, C_callbacks& callbacks);
    Consumer(const Consumer&) = delete;
    ~Consumer(){} 

    void SetQueue(const std::string& queue, const std::function<void(void)>& callback); 

    void Start();

   // C_callbacks *  m_callbacks; 

};

#endif

#include "Consumer.h"

Consumer::Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, C_callbacks& callbacks):
IAMQP(user, password, host, vhost){
	m_callbacks = &callbacks;
}

void Consumer::Start(){
	
	(m_callbacks ->start_callback)();
}

void SetQueue(const std::string& queue, const std::function<void(void)>& callback){

}

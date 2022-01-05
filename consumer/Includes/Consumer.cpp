#include "Consumer.h"

Consumer::Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost):
CAMQP(user, password, host, vhost){

}

void Consumer::Start(){

}

void SetQueue(const std::string& queue, const std::function<void(void)>& callback){

}

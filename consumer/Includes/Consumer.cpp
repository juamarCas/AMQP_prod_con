#include "Consumer.h"

Consumer::Consumer(std::string&& user, std::string&& password, std::string&& host, std::string&& vhost):
CAMQP(std::move(user), std::move(password), std::move(host), std::move(vhost)){

}

void Consumer::Start(){

}

void SetQueue(std::string&& queue, const std::function<void(void)>& callback){

}
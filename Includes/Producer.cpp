Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, C_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue){
    m_amqpState = IAMQP::QUEUE_ONLY;
}
Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, C_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue, exchange){
    m_amqpState = IAMQP::QUEUE_EXCHANGE;
}

void Producer::Start(){
    
}
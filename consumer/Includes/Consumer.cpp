#include "Consumer.h"

Consumer::Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, C_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue){
	m_callbacks = &callbacks;
}

void Consumer::Start(){
	auto *loop = EV_DEFAULT;
	MyHandler myHandler(loop);
	AMQP::Address address(m_url);
	AMQP::TcpConnection connection(&myHandler, address);
	AMQP::TcpChannel channel(&connection);

	channel.declareQueue(m_queue).onSuccess([&channel](const std::string &name, uint32_t messageCount, uint32_t consumercount){
            std::cout<<"declared queue"<<std::endl;
   	});

	auto messageCb = [&channel, this](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered){
#if CONSUMER_DEBUG
		std::cout << "message received!!" << std::endl;
#endif
		char msg_receive[message.bodySize() + 1];
    	strncpy(msg_receive, message.body(), message.bodySize() + 1); 
    	msg_receive[message.bodySize()] = '\0'; 
    	std::string msg_final = std::string(msg_receive);
		(m_callbacks->message_callback)(msg_final);
		channel.ack(deliveryTag);
	};

	channel
    .consume(m_queue)
    .onReceived(messageCb)
    .onSuccess(m_callbacks->success_callback)
    .onError(m_callbacks->error_callback);
	ev_run(loop);
}


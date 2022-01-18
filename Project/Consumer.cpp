#include "Consumer.h"

Consumer::Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, C_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue){
	m_callbacks = &callbacks;	
}

Consumer::Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, const std::string& routingKey, IAMQP::QEConf conf, C_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue, exchange, routingKey, conf){
	m_callbacks = &callbacks;	
}


/*
* starts the consumer operations and prepare messages from broker to be sent
*/
void Consumer::Start(){
	
	#if CONSUMER_DEBUG
		std::cout<<"entered to start"<<std::endl;
	#endif
	auto *loop = ev_loop_new(0);
	MyHandler myHandler(loop);
	AMQP::Address address(m_url);
	AMQP::TcpConnection connection(&myHandler, address);
	AMQP::TcpChannel channel(&connection);

	channel.declareQueue(m_queue).onSuccess([&channel](const std::string &name, uint32_t messageCount, uint32_t consumercount){
		#if CONSUMER_DEBUG
            std::cout<<"declared queue"<<std::endl;
		#endif
   	});

	if(Get_AMQP_State() == IAMQP::QUEUE_EXCHANGE_RK){

	}

	auto messageCb = [&channel, this](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered){
#if CONSUMER_DEBUG
		std::cout << "message received!!" << std::endl;
#endif
		char msg_receive[message.bodySize() + 1];
    	strncpy(msg_receive, message.body(), message.bodySize() + 1); 
    	msg_receive[message.bodySize()] = '\0';  //extract message from broker and converts it into string
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


#include "Consumer.h"

Consumer::Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, C_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue){
	m_callbacks = &callbacks;	
}

Consumer::Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, IAMQP::QEConf conf, C_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue, exchange, conf){
	m_callbacks = &callbacks;
}

Consumer::Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& exchange, IAMQP::QEConf conf, C_callbacks& callbacks):
IAMQP(user, password, host, vhost, exchange, conf){
	m_callbacks = &callbacks;
}

Consumer::Consumer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, IAMQP::QEConf conf, C_callbacks& callbacks):
IAMQP(user, password, host, vhost, conf){
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
	isReady = false;
	#if DEBUG
		std::cout<<"entered to start"<<std::endl;
	#endif
	auto *loop = ev_loop_new(0);
	MyHandler myHandler(loop);
	AMQP::Address address(m_url);
	AMQP::TcpConnection connection(&myHandler, address);
	AMQP::TcpChannel channel(&connection);

	channel.declareQueue(m_queue).onSuccess([&channel](const std::string &name, uint32_t messageCount, uint32_t consumercount){
		#if DEBUG
            std::cout<<"declared queue"<<std::endl;
		#endif
   	});

	if(Get_AMQP_State() != EXCHANGE_ONLY){
      channel.declareQueue(m_queue).onSuccess([&channel, this](const std::string &name, uint32_t messageCount, uint32_t consumercount){
         #if DEBUG
            std::cout<<"declared queue: "<<m_queue<<std::endl;
         #endif
      });
   }else{
      channel.declareQueue(m_conf.QueueFlags).onSuccess([&channel, this](const std::string &name, uint32_t messageCount, uint32_t consumercount){
         #if DEBUG
            std::cout<<"declared queue with no name!"<<std::endl;
         #endif
         m_queue = name;
      });
   } 
   

   if(Get_AMQP_State() == IAMQP::QUEUE_EXCHANGE_RK){

	}else if(Get_AMQP_State() == IAMQP::QUEUE_EXCHANGE || Get_AMQP_State() == IAMQP::EXCHANGE_ONLY){
		channel.declareExchange(m_exchange, m_conf.ETypes, m_conf.ExchangeFlags).onSuccess([&channel, this](){
         #if DEBUG
            std::cout<<"producer has binded its queue "<<m_queue<<"to exchange: "<<m_exchange<<std::endl;
         #endif
         if(Get_AMQP_State() == IAMQP::EXCHANGE_ONLY){
            #if DEBUG
               std::cout<<"binded queue "<<m_queue<<"to exchange "<<m_exchange<<std::endl;
            #endif
            channel.bindQueue(m_exchange, m_queue, "");
         }  

      });
	}

	auto messageCb = [&channel, this](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered){
#if DEBUG
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
	isReady = true;
	ev_run(loop);
}

void Consumer::Subscribe(const std::string& topic){
	if(m_conf.ETypes != AMQP::topic){
      #if DEBUG
      std::cout<<"You are not using topic exchange type!"<<std::endl;
      #endif
      return;
   }
	(subscribeTopicLmda)(topic);
}

void Consumer::PublishToTopic(const std::string& msg, const std::string& topic){
	if(m_conf.ETypes != AMQP::topic){
      #if DEBUG
      std::cout<<"You are not using topic exchange type!"<<std::endl;
      #endif
      return;
   }
   (publishToTopicLmda)(msg, topic);
}

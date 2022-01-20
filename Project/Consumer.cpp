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
	#ifdef DEBUG
		std::cout<<"entered to start"<<std::endl;
	#endif
	m_loop = ev_loop_new(0); 
	m_myHandler = new MyHandler(m_loop);
  	m_address = new AMQP::Address(m_url);
  	m_connection = new AMQP::TcpConnection(m_myHandler, *m_address);
  	m_channel = new AMQP::TcpChannel(m_connection);

	m_channel->declareQueue(m_queue).onSuccess([this](const std::string &name, uint32_t messageCount, uint32_t consumercount){
		#ifdef DEBUG
            std::cout<<"consumer declared queue"<<std::endl;
		#endif
   	});

	if(Get_AMQP_State() != EXCHANGE_ONLY){
        m_channel->declareQueue(m_queue).onSuccess([this](const std::string &name, uint32_t messageCount, uint32_t consumercount){
        #ifdef DEBUG
        std::cout<<"consumer declared queue: "<<m_queue<<std::endl;
        #endif
      });
   }else{
      	m_channel->declareQueue(m_conf.QueueFlags).onSuccess([this](const std::string &name, uint32_t messageCount, uint32_t consumercount){
        #ifdef DEBUG
        std::cout<<"consumer declared queue with no name!"<<std::endl;
        #endif
        m_queue = name;
      });
   } 
   

   if(Get_AMQP_State() == IAMQP::QUEUE_EXCHANGE_RK){
	
	}else if(Get_AMQP_State() == IAMQP::QUEUE_EXCHANGE || Get_AMQP_State() == IAMQP::EXCHANGE_ONLY){
		 /*Check if the exchange exists first*/
        m_channel->declareExchange(m_exchange, m_conf.ETypes, m_conf.ExchangeFlags).onSuccess([this](){
        #ifdef DEBUG
            std::cout<<"consumer confirms the exchange exists!"<<std::endl;
        #endif

    	   
          
        if(Get_AMQP_State() == IAMQP::EXCHANGE_ONLY){
            #ifdef DEBUG
            std::cout<<"consumer binded queue "<<m_queue<<"to exchange "<<m_exchange<<std::endl;
            #endif
            m_channel->bindQueue(m_exchange, m_queue, "");
        }  

      });

	}

	auto messageCb = [this](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered){
#ifdef DEBUG
		std::cout << "message received!!" << std::endl;
#endif
		char msg_receive[message.bodySize() + 1];
    	strncpy(msg_receive, message.body(), message.bodySize() + 1); 
    	msg_receive[message.bodySize()] = '\0';  //extract message from broker and converts it into string
    	std::string msg_final = std::string(msg_receive);
		(m_callbacks->message_callback)(msg_final);
		m_channel->ack(deliveryTag);
	};

	m_channel
    ->consume(m_queue)
    .onReceived(messageCb)
    .onSuccess(m_callbacks->success_callback)
    .onError(m_callbacks->error_callback);
	isReady = true;
	ev_run(m_loop);
}

void Consumer::Subscribe(const std::string& topic){
	if(m_conf.ETypes != AMQP::topic){
      #ifdef DEBUG
      std::cout<<"You are not using topic exchange type!"<<std::endl;
      #endif
      return;
   	}
	m_channel->bindQueue(m_exchange, m_queue, topic);
}

void Consumer::PublishToTopic(const std::string& msg, const std::string& topic){
	if(m_conf.ETypes != AMQP::topic){
      #ifdef DEBUG
      std::cout<<"You are not using topic exchange type!"<<std::endl;
      #endif
      return;
   }
   m_channel->publish(m_exchange, topic, msg.c_str());
}

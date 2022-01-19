#include "Producer.h"

Producer::Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, P_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue){
      
}

Producer::Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, IAMQP::QEConf conf, P_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue, exchange, conf){
	
}


Producer::Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, const std::string& routingKey, IAMQP::QEConf conf,P_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue, exchange, routingKey, conf){
     
}

void Producer::Start(){
  auto * loop1 = ev_loop_new(0); 
  MyHandler m_myHandler(loop1);
  AMQP::Address m_address(m_url);
  AMQP::TcpConnection m_connection(&m_myHandler, m_address);
  AMQP::TcpChannel m_channel(&m_connection);

   PublishMSGLmbda = [&m_channel, this](const std::string& msg){
      #if DEBUG
         std::cout<<"Publishing a message: "<<msg<<"!"<<std::endl;
      #endif
      m_channel.publish("", m_queue, msg); 
   };
  /* nlohmann::json j;
   int var1 = 15; 
   float var2 = 5.5; 

   j["pos"]  = var1; 
   j["temp"] = var2; 

   std::string msg = j.dump();*/ 
   m_channel.declareQueue(m_queue).onSuccess([&m_channel, this](const std::string &name, uint32_t messageCount, uint32_t consumercount){
      #if DEBUG
         std::cout<<"declared queue: "<<m_queue<<std::endl;
      #endif
   });

   if(Get_AMQP_State() == IAMQP::QUEUE_EXCHANGE_RK){

	}else if(Get_AMQP_State() == IAMQP::QUEUE_EXCHANGE){
		m_channel.declareExchange(m_exchange, m_conf.ETypes, m_conf.ExchangeFlags);

		if(m_conf.ETypes == AMQP::topic){
			subscribeTopicLmda = [&m_channel, this](const std::string& topic){
				m_channel.bindQueue(m_exchange, m_queue, topic);
			};

			publishToTopicLmda = [&m_channel, this](const std::string& msg, const std::string& topic){
				m_channel.publish(m_exchange, topic, msg.c_str());
			};
		}
	}
   
   isReady = true; 
   ev_run(loop1);
}

void Producer::PublishMsg(const std::string& msg){
   (PublishMSGLmbda)(msg);
}

void Producer::Subscribe(const std::string& topic){
   if(m_conf.ETypes != AMQP::topic){
      #if DEBUG
      std::cout<<"You are not using topic exchange type!"<<std::endl;
      #endif
      return;
   }
   (subscribeTopicLmda)(topic);
}

void Producer::PublishToTopic(const std::string& msg, const std::string& topic){
   if(m_conf.ETypes != AMQP::topic){
      #if DEBUG
      std::cout<<"You are not using topic exchange type!"<<std::endl;
      #endif
      return;
   }
   (publishToTopicLmda)(msg, topic);
}

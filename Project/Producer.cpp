#include "Producer.h"

Producer::Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, P_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue){
      
}

Producer::Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, IAMQP::QEConf conf, P_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue, exchange, conf){
	
}

Producer::Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& exchange, IAMQP::QEConf conf, P_callbacks& callbacks):
IAMQP(user, password, host, vhost, exchange, conf){

}

Producer::Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, IAMQP::QEConf conf, P_callbacks& callbacks):
IAMQP(user, password, host, vhost, conf){

}

Producer::Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, const std::string& routingKey, IAMQP::QEConf conf,P_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue, exchange, routingKey, conf){
     
}

void Producer::Start(){
  m_loop = ev_loop_new(0); 
  m_myHandler = new MyHandler(m_loop);
  m_address = new AMQP::Address(m_url);
  m_connection = new AMQP::TcpConnection(m_myHandler, *m_address);
  m_channel = new AMQP::TcpChannel(m_connection);
  
   if(Get_AMQP_State() != EXCHANGE_ONLY){
      m_channel->declareQueue(m_queue, m_conf.QueueFlags).onSuccess([this](const std::string &name, uint32_t messageCount, uint32_t consumercount){
         #ifdef DEBUG
            std::cout<<"producer declared queue: "<<m_queue<<std::endl;
         #endif
      });
   }else{
      m_channel->declareQueue(m_conf.QueueFlags).onSuccess([this](const std::string &name, uint32_t messageCount, uint32_t consumercount){
         #ifdef DEBUG
            std::cout<<"producer declared queue with no name!"<<std::endl;
         #endif
         m_queue = name;
      });
   } 
   

   if(Get_AMQP_State() == IAMQP::QUEUE_EXCHANGE_RK){

	}else if(Get_AMQP_State() == IAMQP::QUEUE_EXCHANGE || Get_AMQP_State() == IAMQP::EXCHANGE_ONLY){
            /*Check if the exchange exists first*/
      m_channel->declareExchange(m_exchange, m_conf.ETypes, m_conf.ExchangeFlags).onSuccess([this](){
        #ifdef DEBUG
            std::cout<<"producer confirms the exchange exists!"<<std::endl;
        #endif    
        if(Get_AMQP_State() == IAMQP::EXCHANGE_ONLY){
            #ifdef DEBUG
               std::cout<<"producer binded queue "<<m_queue<<"to exchange "<<m_exchange<<std::endl;
            #endif
              m_channel->bindQueue(m_exchange, m_queue, "");
        }

      });
	}
   
   isReady = true; 
   ev_run(m_loop);
}

void Producer::PublishMsg(const std::string& msg){
   #ifdef DEBUG
      std::cout<<"Publishing a message: "<<msg<<"!"<<std::endl;
   #endif
   m_channel->publish(m_exchange, "", msg); 
}

void Producer::Subscribe(const std::string& topic){
   if(m_conf.ETypes != AMQP::topic){
      #ifdef DEBUG
      std::cout<<"You are not using topic exchange type!"<<std::endl;
      #endif
      return;
   }
   m_channel->bindQueue(m_exchange, m_queue, topic);
}

void Producer::PublishToTopic(const std::string& msg, const std::string& topic){
   if(m_conf.ETypes != AMQP::topic){
      #ifdef DEBUG
      std::cout<<"You are not using topic exchange type!"<<std::endl;
      #endif
      return;
   }
   #ifdef DEBUG
      std::cout<<"Publishing a message: "<<msg<<"!"<<std::endl;
   #endif
   m_channel->publish(m_exchange, topic, msg.c_str());
}

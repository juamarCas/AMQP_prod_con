#include "Producer.h"

Producer::Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, P_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue){
      
}

Producer::Producer(const std::string& user, const std::string& password, const std::string& host, const std::string& vhost, const std::string& queue, const std::string& exchange, const std::string& routingKey, IAMQP::QEConf conf,P_callbacks& callbacks):
IAMQP(user, password, host, vhost, queue, exchange, routingKey){
     
}

void Producer::Start(){
  auto * loop1 = ev_loop_new(0); 
  MyHandler m_myHandler(loop1);
  AMQP::Address m_address(m_url);
  AMQP::TcpConnection m_connection(&m_myHandler, m_address);
  AMQP::TcpChannel m_channel(&m_connection);
  
  //auto pub = 

   PublishMSGLmbda = [&m_channel, this](const std::string& msg){
      #if PRODUCER_DEBUG
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
      #if PRODUCER_DEBUG
         std::cout<<"declared queue: "<<m_queue<<std::endl;
      #endif
   });

   
   isReady = true; 
   ev_run(loop1);
}

void Producer::PublishMsg(const std::string& msg){
   (PublishMSGLmbda)(msg);
}

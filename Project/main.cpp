#include <iostream>
#include <thread>
#include <fstream>
#include "Producer.h"
#include "Consumer.h"
#include "json.hpp"

#define LOG(x) std::cout<<x<<std::endl;

int main(){

    IAMQP::QEConf p_conf;
    p_conf.QueueFlags    = 0; 
    p_conf.ExchangeFlags = 0;
    p_conf.ETypes        = AMQP::topic;

    IAMQP::QEConf c_conf; 
    c_conf.QueueFlags    = 0; 
    c_conf.ExchangeFlags = 0;
    c_conf.ETypes        = AMQP::topic;

    /*json labels
    *consts with 'car' means "characteristic", like name for example
    */
    static const std::string json_path  = "./config.json";

    static const std::string j_login           = "login";
    static const std::string j_username        = "username";
    static const std::string j_password        = "password";
    static const std::string j_host            = "host";
    static const std::string j_vhost           = "vhost";

    static const std::string j_consumer        = "Consumer";
    static const std::string j_producer        = "Producer";

    static const std::string j_car_name        = "name";
    static const std::string j_car_durable     = "durable";
    static const std::string j_car_passive     = "passive"; 
    static const std::string j_car_exclusive   = "exclusive";
    static const std::string j_car_internal    = "internal"; 
    static const std::string j_car_type        = "type";
    static const std::string j_car_enable      = "enable";

    static const std::string j_flag_durable    = "durable";
    static const std::string j_flag_autodelete = "autodelete";
    static const std::string j_flag_passive    = "passive";
    static const std::string j_flag_exclusive  = "exclusive";
    static const std::string j_flag_internal   = "internal";

    static const std::string j_topic           = "topic"; 

    static const std::string j_queue           = "queue";
    static const std::string j_exchange        = "exchange";
    static const std::string j_routeKey        = "routeKey";

    /*reading the config json*/
    std::ifstream i(json_path);
    nlohmann::json j;
    i >> j;

    /*broker*/
    std::string username = j[j_login][j_username];
    std::string password = j[j_login][j_password];
    std::string host     = j[j_login][j_host];
    std::string vhost    = j[j_login][j_vhost];
    
    /*Consumer*/
    std::string consumer_queue    = j[j_consumer][j_queue][j_car_name];
    std::string consumer_exchange = j[j_consumer][j_exchange][j_car_name];
    std::string consumer_rk       = j[j_consumer][j_routeKey];
    
    /*Consumer queue flags*/
    bool consumer_q_durable    = j[j_consumer][j_queue][j_flag_durable][j_car_enable];
    bool consumer_q_autodelete = j[j_consumer][j_queue][j_flag_autodelete][j_car_enable];
    bool consumer_q_passive    = j[j_consumer][j_queue][j_flag_passive][j_car_enable];
    bool consumer_q_exclusive  = j[j_consumer][j_queue][j_flag_exclusive][j_car_enable];
    int consumer_q_flags = 0;
    
    /*Consumer exchange flags*/
    bool consumer_e_durable    = j[j_consumer][j_exchange][j_flag_durable][j_car_enable];
    bool consumer_e_autodelete = j[j_consumer][j_exchange][j_flag_autodelete][j_car_enable];
    bool consumer_e_passive    = j[j_consumer][j_exchange][j_flag_passive][j_car_enable];
    bool consumer_e_internal   = j[j_consumer][j_exchange][j_flag_internal][j_car_enable];
    int consumer_e_flags = 0; 

    /*Consumer exchange type*/
    std::string consumer_e_type = j[j_consumer][j_exchange][j_car_type];
    if(consumer_e_type == "topic"){
        c_conf.ETypes = AMQP::topic;
    }else if(consumer_e_type == "fanout"){
        
    }

    /*Producer*/
    std::string producer_queue    = j[j_producer][j_queue][j_car_name];
    std::string producer_exchange = j[j_producer][j_exchange][j_car_name];
    std::string producer_rk       = j[j_producer][j_routeKey];

    /*Producer queue flags*/
    bool producer_q_durable    = j[j_producer][j_queue][j_flag_durable][j_car_enable];
    bool producer_q_autodelete = j[j_producer][j_queue][j_flag_autodelete][j_car_enable];
    bool producer_q_passive    = j[j_producer][j_queue][j_flag_passive][j_car_enable];
    bool producer_q_exclusive  = j[j_producer][j_queue][j_flag_exclusive][j_car_enable];

    /*Producer exchange flags*/
    bool producer_e_durable    = j[j_producer][j_exchange][j_flag_durable][j_car_enable];
    bool producer_e_autodelete = j[j_producer][j_exchange][j_flag_autodelete][j_car_enable];
    bool producer_e_passive    = j[j_producer][j_exchange][j_flag_passive][j_car_enable];
    bool producer_e_internal   = j[j_producer][j_exchange][j_flag_internal][j_car_enable];
    int producer_e_flags = 0; 

    /*Producer exchange type*/
    std::string producer_e_type = j[j_producer][j_exchange][j_car_type];
    if(producer_e_type == "topic"){
        p_conf.ETypes = AMQP::topic;
    }else if(producer_e_type == "fanout"){

    }
    

    //std::cout<<username<<std::endl; 


/*Configuration for the producer and consumer*/
  auto success_cb1 = [](const std::string& consumertag){
    
  };

  auto error_cb1   = [](const char *message){};

  /*message received as json format*/
  auto message_cb1 = [](const std::string& message){
    //auto j_parsed = nlohmann::json::parse(message);
    // std::cout<<j_parsed.dump(4)<<j_receive<<"\n\n";
    std::cout<<message<<std::endl; 
  };

  Consumer::C_callbacks cbb1{
      success_cb1, 
      error_cb1, 
      message_cb1
  };

 

  auto success_cb = [](const std::string& consumertag){
    
  };
  auto error_cb   = [](const char *message){};

  /*message received as json format*/
  auto message_cb = [](const std::string& message){
    //auto j_parsed = nlohmann::json::parse(message);
    // std::cout<<j_parsed.dump(4)<<j_receive<<"\n\n";
  };

  Producer::P_callbacks cbb{
	  success_cb,
	  error_cb,
	  message_cb
  };

    Consumer c(username, password, host, vhost, consumer_queue, consumer_exchange, c_conf,cbb1);
    Producer p(username, password, host, vhost, producer_queue, producer_exchange, p_conf,cbb); 

    std::thread Producer_thread(
        [&p](){
            p.Start(); 
        }
    );
    Producer_thread.detach();

    while(!p.GetIsReady()){}
    std::thread Consumer_thread(
        [&c](){
            c.Start(); 
        }
    );
    while(!c.GetIsReady()){}
    
    Consumer_thread.detach(); 
    nlohmann::json js;
    int var1 = 15; 
    float var2 = 5.5; 

    js["pos"]  = var1; 
    js["temp"] = var2; 
    c.Subscribe("hello.world");
    std::string msg = js.dump();
    while(1){
        std::cin.get();
        p.PublishToTopic("hello from topic", "hello.world");
       //p.PublishMsg(msg); 
    }

    return 0; 
}
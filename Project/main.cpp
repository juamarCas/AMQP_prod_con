#include <iostream>
#include <thread>
#include <fstream>
#include "Producer.h"
#include "Consumer.h"
#include "json.hpp"

int main(){
    /*json labels*/
    static const std::string json_path  = "./config.json";

    static const std::string j_login    = "login";
    static const std::string j_consumer = "Consumer";
    static const std::string j_producer = "Producer";
    static const std::string j_username = "username";
    static const std::string j_password = "password";
    static const std::string j_host     = "host";
    static const std::string j_vhost    = "vhost";
    static const std::string j_queue    = "queue";
    static const std::string j_exchange = "exchange";
    static const std::string j_routeKey = "routeKey";

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
    std::string consumer_queue    = j[j_consumer][j_queue];
    std::string consumer_exchange = j[j_consumer][j_exchange];
    std::string consumer_rk       = j[j_consumer][j_routeKey];

    /*Producer*/
    std::string producer_queue    = j[j_producer][j_queue];
    std::string producer_exchange = j[j_producer][j_exchange];
    std::string producer_rk       = j[j_producer][j_routeKey];

    std::cout<<username<<std::endl; 

    return 0; 
}
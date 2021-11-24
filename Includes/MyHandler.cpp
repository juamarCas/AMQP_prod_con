#include "MyHandler.h"

void MyHandler::onAttached(AMQP::TcpConnection *connection)
{

}

void MyHandler::onConnected(AMQP::TcpConnection *connection)
{

}

bool MyHandler::onSecured(AMQP::TcpConnection *connection, const SSL *ssl)
{
        return true;
}

void MyHandler::onReady(AMQP::TcpConnection *connection)
{
        std::cout<<"ready"<<std::endl;
}

void MyHandler::onError(AMQP::TcpConnection *connection, const char *message)
{

}

void MyHandler::onClosed(AMQP::TcpConnection *connection)
{

}

void MyHandler::onLost(AMQP::TcpConnection *connection)
{

}

void MyHandler::onDetached(AMQP::TcpConnection *connection)
{

}


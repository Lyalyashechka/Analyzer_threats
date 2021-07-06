#include "NetworkClient.h"

NetworkClient::NetworkClient()
{
    socket_ = socket(AF_UNIX, SOCK_STREAM, 0);
}

NetworkClient::~NetworkClient()
{
    disconnect();
}

void NetworkClient::startConnect(struct sockaddr_un addrConnect)
{
    int len = sizeof(addrConnect.sun_family) + strlen(addrConnect.sun_path);
    connect(socket_, (struct sockaddr *)&addrConnect, (socklen_t)len);
}

void NetworkClient::disconnect()
{
    close(socket_);
}

Message NetworkClient::startRead(int &error)
{
    readHeader(error);
    return readMessage_;
}

void NetworkClient::readHeader(int &error)
{
    if ((error = read(socket_, &readMessage_.header, sizeof(MessageHeader))) < 0)
    {
        std::cout << "Error in readHeader\n";
        return;
    }

    readBody(readMessage_.header.sizeMessage, error);
}

void NetworkClient::readBody(uint32_t sizeBody, int &error)
{
    readMessage_.body.resize(readMessage_.header.sizeMessage);
    
    if ((error = read(socket_, readMessage_.body.data(), readMessage_.header.sizeMessage)) < 0)
    {
        std::cout << "Error in readBody\n";
        return;
    }
}

void NetworkClient::startSend(Message msg)
{
    sendHeader(msg);
}

void NetworkClient::sendHeader(Message msg)
{
    std::cout<< msg.header.sizeMessage<<"\n\n\n";
    int errorSend = send(socket_, &msg.header, sizeof(MessageHeader), 0);
    std::cout<<errorSend;
    sendBody(msg);
}

void NetworkClient::sendBody(Message msg)
{
    send(socket_, msg.body.data(), msg.header.sizeMessage, 0);
}
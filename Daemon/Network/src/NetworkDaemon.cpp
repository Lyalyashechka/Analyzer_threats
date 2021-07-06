#include "NetworkDaemon.h"

NetworkDaemon::NetworkDaemon()
{
    socket_ = socket(AF_UNIX, SOCK_STREAM, 0);
}

NetworkDaemon::~NetworkDaemon()
{
    close(socket_);
}

void NetworkDaemon::start(struct sockaddr_un addrForStart)
{
    int len = sizeof(addrForStart.sun_family) + strlen(addrForStart.sun_path);
    bind(socket_, (struct sockaddr *)&addrForStart, len);
    listen(socket_, MaxCountConnection);
    waitAccept();
}

void NetworkDaemon::waitAccept()
{
    int len;
    addrAccept_ = accept(socket_, (struct sockaddr *)&addrConnnected_, (socklen_t *)&len);
    
    onAccept();
    waitAccept();
}

void NetworkDaemon::onAccept()
{
    readHeader();
}

void NetworkDaemon::readHeader()
{
    read(addrAccept_, &readMessage_.header, sizeof(MessageHeader));
    std::cout<<"readed sizeMessaeg "<<readMessage_.header.sizeMessage<<"\n\n\n";
    readBody(readMessage_.header.sizeMessage);
}

void NetworkDaemon::readBody(const uint32_t& sizeMessage)
{
    std::cout<<"SizeBody:"<< sizeMessage<<"\n\n\n";
    readMessage_.body.resize(readMessage_.header.sizeMessage);
    read(addrAccept_, readMessage_.body.data(), sizeMessage);
    std::cout<<"+readBody\n\n\n";
    int test;
    readMessage_ >> test;
    std::cout << test <<"\n\n\n";
}
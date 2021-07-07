#include "NetworkDaemon.h"

NetworkDaemon::NetworkDaemon(std::shared_ptr<I_Analyzer> &analyzer)
{
    socket_ = socket(AF_UNIX, SOCK_STREAM, 0);
    analyzer_ = analyzer;
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
    readBody(readMessage_.header.sizeStringData);
}

void NetworkDaemon::readBody(const size_t &sizeMessage)
{
    readMessage_.stringData.resize(sizeMessage);
    read(addrAccept_, &readMessage_.stringData[0], sizeMessage);
    analyzer_->startAnalyzing(readMessage_.stringData.c_str(), 4);
    Message msgForSend;
    msgForSend.analyzData = analyzer_->getResultAnalyz();
    std::cout << readMessage_.stringData.c_str() << "\n\n\n";
    sendHeader(msgForSend);
}

void NetworkDaemon::sendHeader(Message &msg)
{   
    send(addrAccept_, &msg.header, sizeof(MessageHeader), 0);
    sendBody(msg);    
}

void NetworkDaemon::sendBody(Message &msg)
{
    send(addrAccept_, &msg.analyzData, sizeof(AnalyzInformation), 0);
}


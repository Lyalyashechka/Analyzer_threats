#include "NetworkDaemon.h"
#include <syslog.h>
NetworkDaemon::NetworkDaemon(std::shared_ptr<I_Analyzer> &analyzer)
{
    socket_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_ < 0)
    {
        syslog(5, "Error create socket");
    }
    analyzer_ = analyzer;
}

NetworkDaemon::~NetworkDaemon()
{
    close(socket_);
}

void NetworkDaemon::start(struct sockaddr_un addrForStart)
{
    struct sockaddr_un saun;
    saun.sun_family = AF_UNIX;
    strcpy(saun.sun_path, "search331");
    unlink(saun.sun_path);

    int len = sizeof(saun.sun_family) + strlen(saun.sun_path);
    if (::bind(socket_, (struct sockaddr *)&saun, len) < 0)
    {
        syslog(5, "Bind error");
    }
    if (::listen(socket_, MaxCountConnection) < 0)
    {
        syslog(5, "Listen error");
    }
}

void NetworkDaemon::waitAccept()
{
    int len;
    addrAccept_ = ::accept(socket_, (struct sockaddr *)&addrConnnected_, (socklen_t *)&len);
    if (addrAccept_ < 0)
    {
        syslog(5, "Accept error");
    }
    onAccept();
    waitAccept();
}

void NetworkDaemon::onAccept()
{
    readHeader();
}

void NetworkDaemon::readHeader()
{
    if (read(addrAccept_, &readMessage_.header, sizeof(MessageHeader)) < 0)
    {
        syslog(5, "Error read header");
    }
    readBody(readMessage_.header.sizeStringData);
}

void NetworkDaemon::readBody(const size_t &sizeMessage)
{
    readMessage_.stringData.resize(sizeMessage);
    if (read(addrAccept_, &readMessage_.stringData[0], sizeMessage) < 0)
    {
        syslog(5, "Error read body");
    }
    analyzer_->startAnalyzing(readMessage_.stringData.c_str(), 4);
    Message msgForSend;
    msgForSend.analyzData = analyzer_->getResultAnalyz();
    sendHeader(msgForSend);
}

void NetworkDaemon::sendHeader(Message &msg)
{
    if (send(addrAccept_, &msg.header, sizeof(MessageHeader), 0) < 0)
    {
        syslog(5, "Error send header");
    }
    sendBody(msg);
}

void NetworkDaemon::sendBody(Message &msg)
{
    if (send(addrAccept_, &msg.analyzData, sizeof(AnalyzInformation), 0) < 0)
    {
        syslog(5, "Error send body");
    }
}

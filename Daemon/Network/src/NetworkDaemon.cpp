#include "NetworkDaemon.h"
#include <syslog.h>
NetworkDaemon::NetworkDaemon(std::shared_ptr<I_Analyzer> &analyzer)
{
    socket_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_ < 0)
    {
        syslog(5, "ya ne sozdal socket");
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
        syslog(5, "kak vsegda bind not work");
    }
    
    
    ::listen(socket_, MaxCountConnection);
    
}

void NetworkDaemon::waitAccept()
{
    int len;
    syslog(5,"before wait accept");
    addrAccept_ = ::accept(socket_, (struct sockaddr *)&addrConnnected_, (socklen_t *)&len);
    syslog(5,"after wait accept");
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
    syslog(5, "ya nachal chitat'");
    readBody(readMessage_.header.sizeStringData);
}

void NetworkDaemon::readBody(const size_t &sizeMessage)
{
    readMessage_.stringData.resize(sizeMessage);
    read(addrAccept_, &readMessage_.stringData[0], sizeMessage);
    analyzer_->startAnalyzing(readMessage_.stringData.c_str(), 4);
    Message msgForSend;
    msgForSend.analyzData = analyzer_->getResultAnalyz();
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


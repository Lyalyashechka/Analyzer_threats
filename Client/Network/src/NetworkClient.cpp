#include "NetworkClient.h"

void printTime_MinSecMs(const long long &ms)
{
    int milSec = ms % 1000;
    int sec = ((ms - milSec) / 1000) % 60;
    int min = ((ms - milSec) / 1000) / 60;
    std::cout << min << ":" << sec << ":" << milSec << " (min:sec:ms)" << std::endl;
}

void printAnalyzResult(const AnalyzInformation &res, const long long &ms)
{
    std::cout << "====== Scan result ======" << std::endl
              << "Processed files: " << res.countProcFiles << std::endl
              << "JS detects: " << res.countJSSus << std::endl
              << "Unix detects: " << res.countUNIXSus << std::endl
              << "macOS detects:" << res.countMACSus << std::endl
              << "Errors: " << res.countErrors << std::endl
              << "Exection time: ";
    printTime_MinSecMs(ms);
    std::cout << "=========================" << std::endl;
}


NetworkClient::NetworkClient()
{
    socket_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_ < 0)
    {
        std::cerr<<"Error in create socket \n";
        exit(1);
    }
}

NetworkClient::~NetworkClient()
{
    disconnect();
}

void NetworkClient::startConnect(struct sockaddr_un addrConnect)
{
    int len = sizeof(addrConnect.sun_family) + strlen(addrConnect.sun_path);
    if (connect(socket_, (struct sockaddr *)&addrConnect, (socklen_t)len) < 0)
    {
        std::cerr << "Error in connect\n";
        exit(1);
    }
}

void NetworkClient::disconnect()
{
    close(socket_);
}

Message NetworkClient::startRead()
{
    readHeader();
    return readMessage_;
}

void NetworkClient::readHeader()
{
    if (read(socket_, &readMessage_.header, sizeof(MessageHeader)) < 0)
    {
        std::cerr << "Error in read answer\n";
        disconnect();
        exit(1);
        return;
    }
    readBodyAnalyzInfo();
}

void NetworkClient::readBodyAnalyzInfo()
{
    if (read(socket_, &readMessage_.analyzData, sizeof(AnalyzInformation)) < 0)
    {
        std::cerr << "Error in read answer\n";
        exit(1);
        return;
    }
    printAnalyzResult(readMessage_.analyzData, 88800555);
}

void NetworkClient::startSend(Message msg)
{
    sendHeader(msg);
}

void NetworkClient::sendHeader(Message msg)
{
    if (send(socket_, &msg.header, sizeof(MessageHeader), 0) < 0)
    {
        std::cerr << "Error in send message header\n";
        disconnect();
        exit(1);
    }
    sendBody(msg);
}

void NetworkClient::sendBody(Message msg)
{
    if (send(socket_, msg.stringData.c_str(), msg.header.sizeStringData, 0) < 0)
    {
        std::cerr << "Error in send message body\n";
        disconnect();
        exit(1);
    }
    startRead();
}
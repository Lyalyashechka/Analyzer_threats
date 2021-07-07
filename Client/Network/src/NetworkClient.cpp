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
    readBodyAnalyzInfo(error);
}

void NetworkClient::readBodyAnalyzInfo(int &error)
{
    if ((error = read(socket_, &readMessage_.analyzData, sizeof(AnalyzInformation))) < 0)
    {
        std::cout << "Error in readBody\n";
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
    int errorSend = send(socket_, &msg.header, sizeof(MessageHeader), 0);
    sendBody(msg);
}

void NetworkClient::sendBody(Message msg)
{
    send(socket_, msg.stringData.c_str(), msg.header.sizeStringData, 0);
    int error;
    startRead(error);
}
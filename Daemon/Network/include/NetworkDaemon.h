#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "Message.h"
#include "Analyzer.h"

#define MaxCountConnection 10

class NetworkDaemon
{
public:
    NetworkDaemon(std::shared_ptr<I_Analyzer> &analyzer);

    NetworkDaemon(const NetworkDaemon &nd) = delete;

    NetworkDaemon& operator=(const NetworkDaemon &nd) = delete;
    
    ~NetworkDaemon();

    void start(struct sockaddr_un addrForStart);
    
    void waitAccept();
private:
    

    void onAccept();

    void readHeader();

    void readBody(const size_t& sizeMessage);

    void sendHeader(Message &msg);

    void sendBody(Message &msg);

    int socket_;

    int addrAccept_;

    struct sockaddr_un addrConnnected_;

    Message readMessage_;

    std::shared_ptr<I_Analyzer> analyzer_;
};
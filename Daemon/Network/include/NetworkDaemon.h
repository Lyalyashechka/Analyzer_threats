#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "Message.h"

#define MaxCountConnection 10

class NetworkDaemon
{
public:
    NetworkDaemon();

    NetworkDaemon(const NetworkDaemon &nd) = delete;

    NetworkDaemon& operator=(const NetworkDaemon &nd) = delete;
    
    ~NetworkDaemon();

    void start(struct sockaddr_un addrForStart);

private:
    void waitAccept();

    void onAccept();

    void readHeader();

    void readBody(const uint32_t& sizeMessage);

    void sendHeader();

    void sendBody();

    int socket_;

    int addrAccept_;

    struct sockaddr_un addrConnnected_;

    Message readMessage_;
};
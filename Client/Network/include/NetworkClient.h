#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "Message.h"
#include "I_NetworkClient.h"

class NetworkClient : public I_NetworkClient
{
public:
    NetworkClient();

    NetworkClient(const NetworkClient &nc) = delete;

    NetworkClient &operator=(const NetworkClient &nc) = delete;

    ~NetworkClient();

    void startConnect(struct sockaddr_un addrConnect) override;

    void disconnect() override;

    Message startRead() override;

    void startSend(Message msg) override;
private:
    void readHeader();

    void readBodyAnalyzInfo();

    void sendHeader(Message msg);

    void sendBody(Message msg);

    int socket_;

    Message readMessage_;
};
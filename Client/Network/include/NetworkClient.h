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

    Message startRead(int &error) override;

    void startSend() override;
private:

    void readHeader(int &error);

    void readBody(uint32_t sizeBody, int &error);

    void sendHeader();

    void sendBody();

    int socket_;

    Message readMessage_;
};
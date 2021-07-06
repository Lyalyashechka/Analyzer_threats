#pragma once

#include "Message.h"

struct I_NetworkClient
{
    virtual void startConnect(struct sockaddr_un addrConnect) = 0;

    virtual void disconnect() = 0;

    virtual Message startRead(int &error) = 0;

    virtual void startSend(Message msg) = 0;
};

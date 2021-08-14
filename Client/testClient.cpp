#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <memory>

#include "Message.h"
#include "NetworkClient.h"

#define ADDRESS "search331"

int main()
{
    struct sockaddr_un saun;
    saun.sun_family = AF_UNIX;
    strcpy(saun.sun_path, ADDRESS);

    std::shared_ptr<I_NetworkClient> nc(new NetworkClient());

    nc->startConnect(saun);
    Message msgForSend;
    std::string buf_test = "/home/lyalyashechka/kasper/SearchThreats/testDirs";
    msgForSend.setStringData(buf_test);
    nc->startSend(msgForSend);

}
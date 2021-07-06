#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <memory>

#include "Message.h"
#include "NetworkClient.h"

#define ADDRESS "SEARCH"

int main()
{
    struct sockaddr_un saun;
    saun.sun_family = AF_UNIX;
    strcpy(saun.sun_path, ADDRESS);

    std::shared_ptr<I_NetworkClient> nc(new NetworkClient());

    nc->startConnect(saun);
    int error;
    Message readed = nc->startRead(error);

    int r;
    readed >> r;
    std::cout << r;
}
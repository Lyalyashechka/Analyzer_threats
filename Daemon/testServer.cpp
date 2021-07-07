#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "Message.h"
#include "NetworkDaemon.h"

#define ADDRESS "SEARCH"

int main()
{
    Analyzer an;
    auto ptr = std::shared_ptr<I_Analyzer> (&an);
    NetworkDaemon nd(ptr);

    struct sockaddr_un saun;
    saun.sun_family = AF_UNIX;
    strcpy(saun.sun_path, ADDRESS);
    unlink(ADDRESS);
    nd.start(saun);
}
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "Message.h"
#include "NetworkDaemon.h"

#define ADDRESS "SEARCH"

int socket_ = socket(AF_UNIX, SOCK_STREAM, 0);

void sendHeader(Message msg)
{
    send(socket_, &msg.header, sizeof(MessageHeader), 0);
}

int main()
{
    NetworkDaemon nd;

    struct sockaddr_un saun;
    saun.sun_family = AF_UNIX;
    strcpy(saun.sun_path, ADDRESS);
unlink(ADDRESS);
    nd.start(saun);
    // printf("hello\n");
    // int len, ns;

    // struct sockaddr_un saun, fsaun;
    // saun.sun_family = AF_UNIX;
    // strcpy(saun.sun_path, ADDRESS);
    // printf("hello\n");
    // unlink(ADDRESS);
    // len = sizeof(saun.sun_family) + strlen(saun.sun_path);
    // bind(socket_, (struct sockaddr *)&saun, len);

    // listen(socket_, 1);

    // ns = accept(socket_, (struct sockaddr *)&fsaun, (socklen_t *)&len);
    // printf("hello\n");
    // FILE *fp;
    // fp = fdopen(ns, "r");
    // Message msg;
    // int sendData = 10;
    // msg<<sendData;
    // std::cout<<msg.header.sizeMessage<<"\n\n\n";
    // // sendHeader(msg);
    // printf("%d", send(ns, &msg.header, sizeof(MessageHeader), 0));
    // // sendData
    // send(ns, msg.body.data(), msg.header.sizeMessage, 0);
    // char c;

    // close(socket_);
}
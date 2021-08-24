#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "Message.h"
#include "NetworkDaemon.h"

#define ADDRESS "search331"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

static void skeleton_daemon()
{
    pid_t pid;
    switch (pid = fork())
    {
    case 0:

        setsid();
        chdir("/");
        close(0);
        close(1);
        close(2);
        openlog("ScanUtil", LOG_NOWAIT | LOG_PID, LOG_USER);
        break;
    default:
        exit(0);
    }

}

int main()
{
    Analyzer an;
    auto ptr = std::shared_ptr<I_Analyzer>(&an);
    NetworkDaemon nd(ptr);
    struct sockaddr_un saun;
    nd.start(saun);
    skeleton_daemon();
    nd.waitAccept();
    closelog();
    return EXIT_SUCCESS;
}
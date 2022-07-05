#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "../ServerInit/ServerInit.h"

int main(int argc, const char *argv[]) {
    int port, server_fd, client_fd;
    _Bool shouldRun = 1;
    char inputBuffer[1024] = {0};
    
    FILE *convLog;
    
    struct sockaddr_in serverAddress, clientAddress;
    
    struct readArgumentsReturn *readArgumentsReturn = readArguments(argc, argv, &port);
    
    free(readArgumentsReturn);
    readArgumentsReturn = 0;
    
    return 0;
}

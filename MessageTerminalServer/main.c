#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "../ServerInit/ServerInit.h"
#include "../Functions/Functions.h"

int main(int argc, const char *argv[]) {
    int port, server_fd, client_fd;
    _Bool shouldRun = 1;
    char inputBuffer[1024] = {0};
    struct sockaddr_in serverAddress, clientAddress;
    
    FILE *convLog;
    struct readArgumentsReturn *readArgumentsReturn = readArguments(argc, argv, &port);
    convLog = openFile(readArgumentsReturn->fileName, "w");
    
    
    
    free(readArgumentsReturn);
    readArgumentsReturn = 0;
    fclose(convLog);
    convLog = 0;
    
    return 0;
}

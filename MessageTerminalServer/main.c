#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../ServerInit/ServerInit.h"
#include "../Functions/Functions.h"

int main(int argc, const char *argv[]) {
    int port, server_fd, client_fd;
    _Bool shouldRun = 1;
    char inputBuffer[1024] = {0};
    struct sockaddr_in serverAddress, clientAddress;
    
    //read configs
    FILE *convLog;
    struct readArgumentsReturn *readArgumentsReturn = readArguments(argc, argv, &port);
    convLog = openFile(readArgumentsReturn->fileName, "w");
    printConfigs(port, readArgumentsReturn->fileName);
    free(readArgumentsReturn->fileName);
    readArgumentsReturn->fileName = 0;
    free(readArgumentsReturn);
    readArgumentsReturn = 0;
    printf("\n\n");
    
    //run program
    server_fd = initializeSocket(port, &serverAddress);
    
    //exit program
    fclose(convLog);
    convLog = 0;
    close(server_fd);
    return 0;
}

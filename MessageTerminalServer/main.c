#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../ServerInit/ServerInit.h"
#include "../Functions/Functions.h"

int main(int argc, const char *argv[]) {
    int port, server_fd, nrUsers = 2;
    struct sockaddr_in serverAddress;
    
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
    
    //start server
    server_fd = initializeSocket(port, &serverAddress);
    runServer(nrUsers, port, convLog, server_fd, serverAddress);
    
    //exit program
    fclose(convLog);
    convLog = 0;
    close(server_fd);
    return 0;
}

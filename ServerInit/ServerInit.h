#ifndef ServerInit_h
#define ServerInit_h

struct readArgumentsReturn {
    char *fileName;
};

struct readArgumentsReturn *readArguments(int argc, const char *argv[], int *port);
int initializeSocket(int port, struct sockaddr_in *server_address);
void printConfigs(int port, char *fileName);

#endif /* ServerInit_h */

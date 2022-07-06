#ifndef ServerInit_h
#define ServerInit_h

struct readArgumentsReturn {
    char *fileName;
};

struct readArgumentsReturn *readArguments(int argc, const char *argv[], int *port);
int initializeSocket(int port, struct sockaddr_in *server_address);
int getClient(int server_fd, struct sockaddr_in server_address, struct sockaddr_in *client_address);
void printConfigs(int port, char *fileName);
void runServer(int num_threads, int port, FILE *log, int server_fd, struct sockaddr_in serverAddress);
void *mainThread(void *arg);

#endif /* ServerInit_h */

#ifndef ServerInit_h
#define ServerInit_h

typedef struct thread_info {
    pthread_t thread_id;
    
    int thread_num;
    char *name;
    
    pthread_cond_t self;
    pthread_cond_t parent;
    pthread_mutex_t m;
} THREAD_INFO;

struct readArgumentsReturn {
    char *fileName;
};

struct readArgumentsReturn *readArguments(int argc, const char *argv[], int *port);
int initializeSocket(int port, struct sockaddr_in *server_address);
void printConfigs(int port, char *fileName);
void runServer(int num_threads, int port, FILE *log, int server_fd, struct sockaddr_in serverAddress);
void *mainThread(void *arg);

#endif /* ServerInit_h */

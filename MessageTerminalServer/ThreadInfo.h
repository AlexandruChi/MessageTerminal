#ifndef ThreadInfo_h
#define ThreadInfo_h

typedef struct thread_info {
    pthread_t thread_id;
    
    int thread_num, server_fd;
    char *name;
    struct sockaddr_in serverAddress;
    
    pthread_cond_t self;
    pthread_cond_t parent;
    pthread_mutex_t m;
} THREAD_INFO;

#endif /* ThreadInfo_h */

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>

#include "ServerInit.h"
#include "../Functions/Functions.h"
#include "../define.h"

void runServer(int num_threads, int port, FILE *log, int server_fd, struct sockaddr_in serverAddress) {
    pthread_attr_t attr;
    THREAD_INFO *tinfo = 0;
    int rcode;
    
    printf("Seting up connections for %d users\n\n", num_threads);
    rcode = pthread_attr_init(&attr);
    if (rcode) {
        fprintf(stderr, __CREATE_ATTR_ERROR);
        exit(EXIT_FAILURE);
    }
    
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    tinfo = (THREAD_INFO*)allocate(num_threads * sizeof(THREAD_INFO));
    
    for (int iter = 0; iter < num_threads; iter++) {
        (tinfo + iter)->thread_num = iter;
        
        (tinfo + iter)->self = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
        (tinfo + iter)->parent = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
        (tinfo + iter)->m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
        
        rcode = pthread_create(&((tinfo + iter)->thread_id), &attr, &mainThread, (void*)(tinfo + iter));
        if (rcode) {
            fprintf(stderr, __CREATE_THREAD_ERROR, iter);
            resetMemory((void*)tinfo, num_threads, sizeof(THREAD_INFO));
            free((void*)tinfo);
            tinfo = 0;
            pthread_attr_destroy(&attr);
            exit(EXIT_FAILURE);
        }
    }
}

void *mainThread(void *arg) {
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "ServerInit.h"
#include "../Functions/Functions.h"
#include "../define.h"
#include "../MessageTerminalServer/ThreadInfo.h"

void runServer(int num_threads, int port, FILE *log, int server_fd, struct sockaddr_in serverAddress) {
    struct sockaddr_in clientAddress;
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
        (tinfo + iter)->status = 0;
        (tinfo + iter)->log = log;
        
        printf("Connection nr. %d sering up\n", (tinfo + iter)->thread_num);
        (tinfo + iter)->client_fd = getClient(server_fd, serverAddress, &clientAddress);
        
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
    THREAD_INFO *ptr_tinfo = (THREAD_INFO*)arg;
    char buffer[2048] = {0};
    long messageSize;
    
    printf("Connection nr. %d created\n", ptr_tinfo->thread_num);
    
    send(ptr_tinfo->client_fd, "Enter name: ",13 , 0);
    
    messageSize = read(ptr_tinfo->client_fd, buffer, 2048);
    
    ptr_tinfo->name = (char*)allocate((strlen(buffer) + 1) * sizeof(char));
    strcpy(ptr_tinfo->name, buffer);
        
    return 0;
}

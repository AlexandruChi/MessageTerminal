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

#define enter_name "Enter name: "
#define waiting_for_users "Waiting for users to connect"
#define conected_users "Conected users: %d"

void runServer(int num_threads, int port, FILE *log, int server_fd, struct sockaddr_in serverAddress) {
    struct sockaddr_in clientAddress;
    pthread_attr_t attr;
    THREAD_INFO *tinfo = 0;
    int rcode, nrUsers = 0;
    
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
        (tinfo + iter)->nrUsers = &nrUsers;
        
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
        
        pthread_mutex_lock(&((tinfo + iter)->m));
        while (*((tinfo + iter)->nrUsers) < 1) {
            pthread_cond_wait(&((tinfo + iter)->parent), &((tinfo + iter)->m));
        }
        
        printf("User %s connected [id: %d]\n", (tinfo + iter)->name, (tinfo + iter)->thread_num);
        
        pthread_mutex_unlock(&((tinfo + iter)->m));
    }
    
}

void *mainThread(void *arg) {
    THREAD_INFO *ptr_tinfo = (THREAD_INFO*)arg;
    char buffer[2048] = {0};
    long messageSize;
    
    pthread_mutex_lock(&(ptr_tinfo->m));
    printf("Connection nr. %d created\n", ptr_tinfo->thread_num);
    
    send(ptr_tinfo->client_fd, enter_name, strlen(enter_name) + 1, 0);
    messageSize = read(ptr_tinfo->client_fd, buffer, 2048);
    ptr_tinfo->name = (char*)allocate((strlen(buffer) + 1) * sizeof(char));
    strcpy(ptr_tinfo->name, buffer);
    
    *(ptr_tinfo->nrUsers) += 1;
    send(ptr_tinfo->client_fd, "\n", 2, 0);
    send(ptr_tinfo->client_fd, conected_users, strlen(conected_users) + 1, 0);
    
    send(ptr_tinfo->client_fd, "\n", 2, 0);
    if (*(ptr_tinfo->nrUsers) < 2) {
        send(ptr_tinfo->client_fd, waiting_for_users, strlen(waiting_for_users) + 1, 0);
    }
    pthread_mutex_unlock(&(ptr_tinfo->m));
    
    pthread_cond_signal(&(ptr_tinfo->parent));
    
    return 0;
}

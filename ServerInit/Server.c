#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../define.h"

void printConfigs(int port, char *fileName) {
    printf("Configs:\n\n    port: %d\n\n    log file: %s", port, fileName);
}

int initializeSocket(int port, struct sockaddr_in *server_address) {
    int server_fd, err_setopt = 0, option_value = 1;
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        fprintf(stderr, __SOCKET_CREATE_ERROR);
        exit(EXIT_FAILURE);
    }
        
    err_setopt = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option_value, sizeof(option_value));
    if (!err_setopt) {
        fprintf(stderr, __SOCKET_CONFIG_ERROR);
        exit(EXIT_FAILURE);
    }
    
    server_address->sin_family = AF_INET;
    server_address->sin_addr.s_addr = INADDR_ANY;
    server_address->sin_port = htons(port);
    
    if(bind(server_fd, (struct sockaddr*)server_address, sizeof(*server_address)) < 0) {
        fprintf(stderr, __SOCKET_CANT_OPEN_ERROR);
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 1) < 0) {
        fprintf(stderr, __SOCKET_CANT_ACCEPT_CONNECTIONS_ERROR);
        exit(EXIT_FAILURE);
    }
    
    return server_fd;
    
}

int getClient(int server_fd, struct sockaddr_in server_address, struct sockaddr_in *client_address) {
    int client_fd, address_lenght = (int)sizeof(server_address);
    
    client_fd = accept(server_fd, (struct sockaddr*)&client_address, (socklen_t*)&address_lenght);
    if (client_fd < 0) {
        fprintf(stderr, __GET_CLIENT_ERROR);
        exit(EXIT_FAILURE);
    }
    
    return client_fd;
}

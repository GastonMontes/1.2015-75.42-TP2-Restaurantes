//
//  server_socket.cpp
//  TP2 - Restaurantes
//
//  Created by Gastón Montes on 5/2/15.
//  Copyright (c) 2015 Gastón Montes. All rights reserved.
//

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>

#include "server_socket.h"

ServerSocket::~ServerSocket() {
}

void ServerSocket::socketBind(const string &address, int port) {
    struct sockaddr_in addr_in = socketAddr(address, port);
    int socketFd = socketGetFileDescriptor();
    int result = bind(socketFd, (struct sockaddr *)&addr_in, sizeof(addr_in));
    if (result == SOCKET_ERROR) {
        perror("Socket bind error");
        printf("Socket bind error:%sn\n", strerror(errno));
        exit(1);
    }
}

void ServerSocket::socketListenConnections(int backlog) {
    if (listen(socketGetFileDescriptor(), backlog)) {
        perror("Socket listen error");
        printf("Socket listen error:%sn\n", strerror(errno));
        exit(1);
    }
}

int ServerSocket::socketAcceptConnection() {
    socklen_t socketLength = sizeof(struct sockaddr_in);
    int socketFd = socketGetFileDescriptor();
    struct sockaddr_in *addr;
    
    clientFd = accept(socketFd, (struct sockaddr *)&addr, &socketLength);
    
    if (clientFd == SOCKET_ERROR) {
        perror("Socket accept error");
        printf("Socket accept error:%sn\n", strerror(errno));
        exit(1);
    }
    
    return clientFd;
}

struct sockaddr_in socketGetAddr(const string &address, int port) {
    struct sockaddr_in newAddr;
    newAddr.sin_family = AF_INET;
    newAddr.sin_port = htons(port);
    newAddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(newAddr.sin_zero), 0, sizeof(newAddr.sin_zero));
    return newAddr;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <netdb.h>
#include <ctype.h>

#include "types.h"
#include "sock.h"
#include <pthread.h>

void* service(void*args){
    int* forClientSockfd = (int*)args;
    char inputBuffer[256] = {};
    char message[] = {"Hi,this is server.\n"};
    send(*forClientSockfd,message,sizeof(message),0);
    recv(*forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
    printf("Get:%s\n",inputBuffer);
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    char *server_port = 0;
    int opt = 0;
    /* Parsing args */
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
        case 'p':
            server_port = malloc(strlen(optarg) + 1);
            strncpy(server_port, optarg, strlen(optarg));
            break;
        case '?':
            fprintf(stderr, "Unknown option \"-%c\"\n", isprint(optopt) ?
                    optopt : '#');
            return 0;
        }
    }

    if (!server_port) {
        fprintf(stderr, "Error! No port number provided!\n");
        exit(1);
    }

    /* Open a listen socket fd */
    int listenfd __attribute__((unused)) = open_listenfd(server_port);

    /* Start coding your server code here! */

    int forClientSockfd;
    struct sockaddr clientInfo;
    int addrlen = sizeof(clientInfo);
    while(1)
        pthread_t t;
        forClientSockfd = accept(listenfd,(struct sockaddr*) &clientInfo, &addrlen);
        pthread_create(&t,NULL,service,(void*)&forClientSockfd);
    return 0;
}


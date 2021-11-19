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

struct msg{
    char key[101];
    char value[101];
};


void* service(void*args){
    int* forClientSockfd = (int*)args;
    struct msg smsg,rmsg;
    char message[] = {"Hi,this is server.\n"};
    strncpy(smsg.key,"123");
    strncpy(smsg.value,"456");
    recv(*forClientSockfd,(void*)&rmsg,sizeof(rmsg),0);
    send(*forClientSockfd,&smsg,sizeof(smsg),0);
    printf("%s\n%s",((struct msg*)rmsg)->key,((struct msg*)rmsg)->value);
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


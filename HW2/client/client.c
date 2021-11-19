#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdlib.h>

#include "sock.h"

struct msg{
    char key[101];
    char value[101];
};

int main(int argc, char **argv)
{
    int opt;
    char *server_host_name = NULL, *server_port = NULL;

    /* Parsing args */
    while ((opt = getopt(argc, argv, "h:p:")) != -1) {
        switch (opt) {
        case 'h':
            server_host_name = malloc(strlen(optarg) + 1);
            strncpy(server_host_name, optarg, strlen(optarg));
            break;
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

    if (!server_host_name) {
        fprintf(stderr, "Error!, No host name provided!\n");
        exit(1);
    }

    if (!server_port) {
        fprintf(stderr, "Error!, No port number provided!\n");
        exit(1);
    }

    /* Open a client socket fd */
    int clientfd __attribute__((unused)) = open_clientfd(server_host_name, server_port);

    /* Start your coding client code here! */

    struct msg smsg,rmsg;

    strncpy(smsg.key,"123");
    strncpy(smsg.value,"456");

    send(*forClientSockfd,&smsg,sizeof(smsg),0);
    recv(*forClientSockfd,(void*)&rmsg,sizeof(rmsg),0);

    printf("%s\n%s",((struct msg*)rmsg)->key,((struct msg*)rmsg)->value);
    printf("close Socket\n");
    close(clientfd);
    return 0;
}

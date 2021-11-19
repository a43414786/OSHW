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

int decode(char*input,(struct msg*)smsg){
    char cmd[7],key[101],value[101];
    int counter = 0;
    int cmdc = 0,kc = 0,vc = 0
    for(int i = 0 ; i < strlen(input),i++){
        if(input[i] == ' '){
            counter += 2;
            break
        }else{
            cmd[cmdc++] = input[i];
            counter++;
        }
    }
    for(int i = counter ; i < strlen(input),i++){
        if(input[i] == ' '){
            counter += 2;
            break
        }else{
            key[kc++] = input[i];
            counter++;
        }
    }
    for(int i = counter ; i < strlen(input),i++){
        if(input[i] == ' '){
            counter += 2;
            break
        }else{
            value[vc++] = input[i];
            counter++;
        }
    }
}

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

    while(1){
        struct msg smsg,rmsg;
        char input[300];
        scanf("%s",&input);
        decode(input,&smsg);
        strcpy(smsg.key,"123");
        strcpy(smsg.value,"456");

        send(clientfd,&smsg,sizeof(smsg),0);
        recv(clientfd,&rmsg,sizeof(rmsg),0);

        printf("%s\n%s",rmsg.key,rmsg.value);
        close(clientfd);
    }
    return 0;
}

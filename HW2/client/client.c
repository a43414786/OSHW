#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdlib.h>

#include "sock.h"

typedef struct msg Msg;

struct msg
{
    char cmd[10];
    char key[101];
    char value[101];
};

int main(int argc, char **argv)
{
    int opt;
    char *server_host_name = NULL, *server_port = NULL;

    /* Parsing args */
    while ((opt = getopt(argc, argv, "h:p:")) != -1)
    {
        switch (opt)
        {
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

    if (!server_host_name)
    {
        fprintf(stderr, "Error!, No host name provided!\n");
        exit(1);
    }

    if (!server_port)
    {
        fprintf(stderr, "Error!, No port number provided!\n");
        exit(1);
    }

    /* Open a client socket fd */

    /* Start your coding client code here! */

    while(1)
    {
        int clientfd __attribute__((unused)) = open_clientfd(server_host_name, server_port);
        int counter = 0;
        int inputc[3] = {0,0,0};
        short flag = 1;
        Msg smsg,rmsg;
        char word;
        char inputs[3][101] = {};
        while((word = getchar()) != '\n')
        {
            if(word == ' ')
            {
                counter++;
                if(counter == 3)
                {
                    flag = 0;
                }
                continue;
            }
            if(flag)
            {
                inputs[counter][inputc[counter]++] = word;
            }
        }
        if(flag)
        {
            if(strcmp(inputs[0],"SET") == 0)
            {
                if(inputc[1] > 0 && counter == 2)
                {
                    strcpy(smsg.cmd,inputs[0]);
                    strcpy(smsg.key,inputs[1]);
                    strcpy(smsg.value,inputs[2]);
                    send(clientfd,&smsg,sizeof(smsg),0);
                    recv(clientfd,&rmsg,sizeof(rmsg),0);
                    printf("%s\n",rmsg.value);
                }
                else
                {
                    printf("unknown/invalid\n");
                }
            }
            else if (strcmp(inputs[0],"GET") == 0)
            {
                if(inputc[1] > 0 && counter == 1)
                {
                    strcpy(smsg.cmd,inputs[0]);
                    strcpy(smsg.key,inputs[1]);
                    strcpy(smsg.value,inputs[2]);
                    send(clientfd,&smsg,sizeof(smsg),0);
                    recv(clientfd,&rmsg,sizeof(rmsg),0);
                    printf("%s\n",rmsg.value);
                }
                else
                {
                    printf("unknown/invalid\n");
                }
            }
            else if (strcmp(inputs[0],"DELETE") == 0)
            {
                if(inputc[1] > 0 && counter == 1)
                {
                    strcpy(smsg.cmd,inputs[0]);
                    strcpy(smsg.key,inputs[1]);
                    strcpy(smsg.value,inputs[2]);
                    send(clientfd,&smsg,sizeof(smsg),0);
                    recv(clientfd,&rmsg,sizeof(rmsg),0);
                    printf("%s\n",rmsg.value);
                }
                else
                {
                    printf("unknown/invalid\n");
                }
            }
            else
            {
                if(inputc[0] || counter)
                {
                    printf("unknown/invalid\n");
                }
            }
        }
        else
        {
            printf("unknown/invalid\n");
        }
        close(clientfd);
    }
    return 0;
}

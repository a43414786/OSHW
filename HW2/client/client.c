#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdlib.h>

#include "sock.h"

typedef struct msg Msg;

typedef struct node Node;

struct msg{
    char cmd[10];
    char key[101];
    char value[101];
};

struct node
{
    char c;
    Node* next;
};
Node* cnode(char c){
    Node*temp = malloc(sizeof(Node*));
    temp->c = c;
    temp->next = NULL;
    return temp;
}
void addnode(Node** root,Node* new){
    Node*temp = *root;
    printf("a");
    if(temp){
        *root = new;
    }else{
        while(temp->next){
            temp = temp->next;
        }
        temp->next = new;
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

    /* Start your coding client code here! */

    while(1){
        int clientfd __attribute__((unused)) = open_clientfd(server_host_name, server_port);
        Node* root = NULL;
        Msg smsg,rmsg;
        char word;
        char cmd[10];
        char key[101];
        char value[101];
        while((word = getchar()) != '\n'){
            printf("%c",word);
            addnode(&root,cnode(word));
        }
        while(root){
            printf("%c",root->c);
            root = root->next;
        }
        strcpy(smsg.cmd,cmd);
        strcpy(smsg.key,key);
        strcpy(smsg.value,value);
        send(clientfd,&smsg,sizeof(smsg),0);
        recv(clientfd,&rmsg,sizeof(rmsg),0);
        printf("%s\n%s\n%s\n",rmsg.cmd,rmsg.key,rmsg.value);
        close(clientfd);
    }
    return 0;
}

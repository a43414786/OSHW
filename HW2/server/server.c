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

typedef struct msg Msg;

typedef struct node Node;

struct msg{
    char cmd[10];
    char key[101];
    char value[101];
};
struct node{
    char key[101];
    char value[101];
    Node* next;
};

Node* database[26] = {NULL};

int tblidx(char* key){
    char head = key[0];
    if('A'<=head<='Z'){
        return head - 'A';
    }else if('a'<=head<='z'){
        return head - 'a';
    }else{
        return head - '0';
    }
}

Node* cnode(char*key,char*value){
    Node*temp;
    strcpy(temp->key,key);
    strcpy(temp->value,value);
    temp->next = NULL;
    return temp;
}

void set(char*key,char*value){
    int index = tblidx(key);
    Node*temp = cnode(key,value);
    Node*temp2 = database[index];
    if(!temp2){
        database[index] = temp;
    }else{
        while(temp2->next){
            temp2 = temp2->next;
        }
        temp2->next = temp;
    }
}

char* get(char*key){
    int index = tblidx(key);
    Node*temp = database[index];
    while(temp){
        if(strcmp(temp->key,key) == 0){
            return temp->value;
        }
        temp->next;
    }
    return "Not Found";
}

void delete(char*key,char*value){
    
}

void* service(void*args){
    int* forClientSockfd = (int*)args;
    struct msg smsg,rmsg;
    bzero(&smsg,sizeof(smsg));
    recv(*forClientSockfd,&rmsg,sizeof(rmsg),0);
    if(strcmp(rmsg.cmd,"SET") == 0){
        set(smsg.key,smsg.value);
        strcpy(smsg.value,"SET");
    }
    else if(strcmp(rmsg.cmd,"GET") == 0){
        strcpy(smsg.value,get(smsg.key));
    }
    else if(strcmp(rmsg.cmd,"DELETE") == 0){
        strcpy(smsg.value,"DELETE");
    }
    send(*forClientSockfd,&smsg,sizeof(smsg),0);
    printf("%s\n%s\n%s\n",rmsg.cmd,rmsg.key,rmsg.value);
    close(*forClientSockfd);
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
    pthread_t t;
    while(1){
        t = malloc(sizeof(pthread_t));
        
        forClientSockfd = accept(listenfd,(struct sockaddr*) &clientInfo, &addrlen);
        pthread_create(&t,NULL,service,(void*)&forClientSockfd);
        pthread_detach(t);
    }
    return 0;
}


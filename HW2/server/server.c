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

Node* database[26] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

int tblidx(char* key){
    char head = key[0];
    if('A'<=head<='Z'){
        return head - 'A';
    }else if('a'<=head<='z'){
        return head - 'a';
    }else if('0'<=head<='9'){
        return head - '0';
    }
}

Node* cnode(char*key,char*value){
    Node*temp = malloc(sizeof(Node*));
    strcpy(temp->key,key);
    strcpy(temp->value,value);
    temp->next = NULL;
    return temp;
}



char* set(char*key,char*value){
    int index = tblidx(key);
    printf("%d",index);
    Node*temp = cnode(key,value);
    Node*temp2 = database[index];
    Node*temp3 = database[index];
    if(!temp2){
        database[index] = temp;
        return "success";
    }else{
        while(temp2){
            if(strcmp(temp2->key,key) == 0){
                return "error";
            }
            temp2 = temp2->next;
        }
        while(temp3->next){
            temp3 = temp3->next;
        }
        temp3->next = temp;
    }
    return "success";
}

char* get(char*key){
    int index = tblidx(key);
    Node*pre = database[index];
    Node*post = pre;
    while(post){
        if(strcmp(post->key,key) == 0){
            return post->value;
        }
        pre = post;
        post = post->next;
    }
    return "error";
}

char* delete(char*key){
    int index = tblidx(key);
    Node*temp = database[index];
    Node*pre = database[index];
    while(temp){
        if(strcmp(temp->key,key) == 0){
            pre->next = temp->next;
            free(temp);
            return "succcess";
        }
        pre = temp;
        temp = temp->next;
    }
    return "error";
}

void* service(void*args){
    int* forClientSockfd = (int*)args;
    struct msg smsg,rmsg;
    bzero(&smsg,sizeof(smsg));
    recv(*forClientSockfd,&rmsg,sizeof(rmsg),0);
    if(strcmp(rmsg.cmd,"SET") == 0){
        strcpy(smsg.value,set(rmsg.key,rmsg.value));
    }
    else if(strcmp(rmsg.cmd,"GET") == 0){
        strcpy(smsg.value,get(rmsg.key));
    }
    else if(strcmp(rmsg.cmd,"DELETE") == 0){
        strcpy(smsg.value,delete(rmsg.key));
    }
    send(*forClientSockfd,&smsg,sizeof(smsg),0);
    free(forClientSockfd);
    return 0;
    //pthread_exit(0);
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

    int* forClientSockfd;
    struct sockaddr clientInfo;
    int addrlen = sizeof(clientInfo);
    pthread_t t;
    while(1){
        forClientSockfd = (int*)malloc(sizeof(int));
        *forClientSockfd = accept(listenfd,(struct sockaddr*) &clientInfo, &addrlen);
        pthread_create(&t,0,service,(void*)forClientSockfd);
        pthread_detach(t);
    }
    return 0;
}


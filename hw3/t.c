#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct thread_status{
    char name[10];
    char function[10];
    int priority;
    int cancelmode;
    struct thread_status *next;
}Thread;

void addnode_thread(Thread**inroot,Thread*input){
    Thread* temp = *inroot;
    if(!temp){
        *inroot = input;
        return;
    }
    while(temp->next){
        temp = temp->next;
    }
    temp->next = input;
    return;
}

typedef struct node{
    char in[20];
    struct node*next;
}Node;

Node* cnode(char*input){
    Node*temp = malloc(sizeof(Node));
    strcpy(temp->in,input);
    temp->next = NULL;
    return temp;
}

void addnode(Node**inroot,Node*input){
    Node* temp = *inroot;
    if(!temp){
        *inroot = input;
        return;
    }
    while(temp->next){
        temp = temp->next;
    }
    temp->next = input;
    return;
}

Thread*getthreads(){
    FILE*fp=fopen("init_threads.json","r");
    Node*root = NULL;
    Thread*thread_root = NULL;
    char input[20];
    char word;
    int flag = 0;
    int counter = 0;
    memset(input,0,sizeof(input));
    while((word = getc(fp)) != EOF){
        if(word == '\"'){
            if(input[0]){
                addnode(&root,cnode(input));
            }
            flag = !flag;
            memset(input,0,sizeof(input));
            counter = 0;
            continue;
        }
        if(flag){
            input[counter++] = word;
        }
    }
    root = root->next;
    counter = 0;
    while(root){
        Thread*temp = malloc(sizeof(Thread));
        memset(temp,0,sizeof(Thread));
        for(int i = 0 ; i < 4 ; i++){
            if(strcmp(root->in,"name") == 0){
                root = root->next;
                strcpy(temp->name,root->in);    
            }
            else if(strcmp(root->in,"entry function") == 0){
                root = root->next;
                strcpy(temp->function,root->in);
            }
            else if(strcmp(root->in,"priority") == 0){
                root = root->next;
                if(strcmp(root->in,"H") == 0){
                    temp->priority = 2;
                }else if(strcmp(root->in,"M") == 0){
                    temp->priority = 1;
                }else if(strcmp(root->in,"L") == 0){
                    temp->priority = 0;
                }
            }
            else if(strcmp(root->in,"cancel mode") == 0){
                root = root->next;
                temp->cancelmode = root->in[0] - '0';
            }
            root = root->next;
        }
        temp->next = NULL;
        addnode_thread(&thread_root,temp);
        
    }
//    while(thread_root){
//        printf("%s\n",thread_root->name);
//        printf("%s\n",thread_root->function);
//        printf("%s\n",thread_root->priority);
//        printf("%s\n",thread_root->cancelmode);
//        printf("\n");
//        thread_root = thread_root->next;
//    }

    return thread_root;
}
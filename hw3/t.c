#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct thread_status{
    char name[20];
    char function[20];
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

Thread*getthreads(){
    FILE*fp=fopen("init_threads.json","r");
    Thread*root = NULL;
    Thread*temp = NULL;
    Thread*thread_root = NULL;
    char input[20];
    char word;
    int flag = 0;
    int counter = 0;
    memset(input,0,sizeof(input));
    while((word = getc(fp)) != EOF){
        if(word == '\"'){
            if(input[0]){
                temp = malloc(sizeof(Thread));
                strcpy(temp->name,input);
                addnode_thread(&root,temp);
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
    temp = root;
    root = root->next;
    free(temp);
    while(root){
        Thread*temp2 = malloc(sizeof(Thread));
        memset(temp2,0,sizeof(Thread));
        for(int i = 0 ; i < 4 ; i++){
            if(strcmp(root->name,"name") == 0){
                temp = root;
                root = root->next;
                free(temp);
                strcpy(temp2->name,root->name);    
            }
            else if(strcmp(root->name,"entry function") == 0){
                temp = root;
                root = root->next;
                free(temp);
                strcpy(temp2->function,root->name);
            }
            else if(strcmp(root->name,"priority") == 0){
                temp = root;
                root = root->next;
                free(temp);
                if(strcmp(root->name,"H") == 0){
                    temp2->priority = 2;
                }else if(strcmp(root->name,"M") == 0){
                    temp2->priority = 1;
                }else if(strcmp(root->name,"L") == 0){
                    temp2->priority = 0;
                }
            }
            else if(strcmp(root->name,"cancel mode") == 0){
                temp = root;
                root = root->next;
                free(temp);
                temp2->cancelmode = root->name[0] - '0';
            }
            temp = root;
            root = root->next;
            free(temp);
        }
        temp2->next = NULL;
        addnode_thread(&thread_root,temp2);        
    }

    return thread_root;
}
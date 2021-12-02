#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct thread_status{
    char name[10];
    char function[10];
    char priority[10];
    char cancelmode[10];
    struct thread_status *next;
}Thread;

Thread *cthread(char*name,char*function,char*priority,char*cancelmode){
    Thread*temp = malloc(sizeof(Thread));
    strcpy(temp->name,name);
    strcpy(temp->function,function);
    strcpy(temp->priority,priority);
    strcpy(temp->cancelmode,cancelmode);
    temp->next = NULL;
    return temp;
}

void link_thread(Thread**inroot,Thread*input){
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

void link(Node**inroot,Node*input){
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
                link(&root,cnode(input));
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
        Thread* temp = malloc(sizeof(Thread));
        for(int i = 0 ; i < 4 ; i++){
            if(strcmp(root->in,"name") == 0){
                
                root = root->next;
        
                strcpy(temp->name,root->in);
            
            }else if(strcmp(root->in,"entry function") == 0){
                
                root = root->next;
        
                strcpy(temp->function,root->in);
            
            }else if(strcmp(root->in,"priority") == 0){
        
                root = root->next;
        
                strcpy(temp->priority,root->in);
            
            }else if(strcmp(root->in,"cancel mode") == 0){
                
                root = root->next;
        
                strcpy(temp->cancelmode,root->in);
            
            }
            root = root->next;
        }
        link_thread(&thread_root,temp);
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node{
    char name[100];
    int frame;
    struct node*next;
}typedef Node;

Node*cnode(char*name,int frame){
    Node*temp = malloc(sizeof(Node));
    memset(temp,0,sizeof(Node));
    strcpy(temp->name,name);
    temp->frame = frame;
    temp->next = NULL;
    return temp;
}
void addnode(Node**root,char*name,int frame){
    Node*temp = *root;
    if(!temp){
        *root = cnode(name,frame);
    }else{
        while(temp->next){
            temp = temp->next;
        }
        temp->next = cnode(name,frame);
    }
}

void pr_info(Node*root){
    while(root){
        printf("%s\n",root->name);
        root = root->next;
    }
}

int main(){
    FILE*trace = fopen("trace.txt", "r");
    char word;
    char input[100];
    int counter = 0;
    Node*root = NULL;
    memset(input, 0, sizeof(input));
    while(word = getc(trace)){
        if(word == "\n" || word == EOF){
            addnode(&root,input,counter);
            input = 0;
            memset(input, 0, sizeof(input));
            if(word == EOF){
                break;
            }
            continue;
        }
        input[counter++] = word;
    }
    pr_info(root);
    return 0;
}
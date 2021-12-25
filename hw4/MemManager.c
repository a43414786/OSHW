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

    char num[] = ",   123456789";
    printf("%d",atoi(num));

    FILE*trace = fopen("trace.txt", "r");
    char word;
    char name[10];
    char fram[10];
    int namecount = 0;
    int framcount = 0;
    Node*root = NULL;
    memset(name, 0, sizeof(name));
    while(word = getc(trace)){
        if(word == '\n' || word == EOF){
            addnode(&root,name,namecount);
            namecount = 0;
            memset(name, 0, sizeof(name));
            if(word == EOF){
                break;
            }
            continue;
        }
        name[namecount++] = word;
    }
    pr_info(root);
    return 0;
}
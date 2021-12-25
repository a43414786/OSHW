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
        printf("%s %d\n",root->name,root->frame);
        root = root->next;
    }
}

int main(){

    FILE*trace = fopen("trace.txt", "r");
    char word;
    char name[10];
    char frame[10];
    int namecount = 0;
    int framecount = 0;
    flag1 = 0;
    flag2 = 0;
    Node*root = NULL;
    memset(name, 0, sizeof(name));
    while(word = getc(trace)){
        if(word == '\n' || word == EOF){
            addnode(&root,name,atoi(frame));
            namecount = 0;
            framecount = 0;
            memset(name, 0, sizeof(name));
            memset(frame, 0, sizeof(frame));
            if(word == EOF){
                break;
            }
            continue;
        }
        if(word == '('){
            flag1 = !flag1;
            continue;
        }
        if(word == ','){
            flag1 = !flag1;
            flag2 = !flag2;
            continue;
        }
        if(word == ')'){
            flag2 = !flag2;
            continue;
        }
        if(flag1){
            name[namecount++] = word;
        }
        if(flag2){
            frame[framecount++] = word;
        }
    }
    pr_info(root);
    return 0;
}
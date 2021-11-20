#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node;

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
    }else{
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
int main(){

    char cmd[10];
    char key[101];
    char value[101];
    scanf("\n%s %s %s",cmd,key,value);
    set(key,value);
    return 0;
}
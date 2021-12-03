#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "t.h"

int main(){
    Thread *thread_root = getthreads();
    while(thread_root){
        printf("%s\n",thread_root->name);
        printf("%s\n",thread_root->function);
        printf("%d\n",thread_root->priority);
        printf("%d\n",thread_root->cancelmode);
        printf("\n");
        thread_root = thread_root->next;
    }
}
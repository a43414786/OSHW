#include "os2021_thread_api.h"
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include "t.h"
void handler(){
    printf("a");
}
int main(int argc,char** argv)
{
    signal(SIGTSTP,handler);
    //StartSchedulingSimulation();
    
    Thread *root = getthreads();
    while(root){
        OS2021_ThreadCreate(root->name,root->function,root->priority,root->cancelmode);
        root = root->next;
    }
    while(1){
        printf("a\n");
        sleep(1);
    }

    return 0;
}

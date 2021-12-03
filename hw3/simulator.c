#include "os2021_thread_api.h"
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include "t.h"

Thread*H_queue = NULL;
Thread*M_queue = NULL;
Thread*L_queue = NULL;


void handler(){
    printf("a");
}
int main(int argc,char** argv)
{
    signal(SIGTSTP,handler);
    //StartSchedulingSimulation();
    
    Thread *root = getthreads();
    while(root){
        puts(root->name);
        //if(root->priority == 0){
        //    addnode_thread(&L_queue,root);
        //}else if(root->priority == 1){
        //    addnode_thread(&M_queue,root);
        //}else if(root->priority == 2){
        //    addnode_thread(&H_queue,root);
        //}
        root = root->next;
    }

    while(1){
        printf("a\n");
        sleep(1);
    }

    return 0;
}

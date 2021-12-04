#include "os2021_thread_api.h"

int counter = 0;

Thread*H_queuef = NULL;
Thread*H_queuer = NULL;
Thread*M_queuef = NULL;
Thread*M_queuer = NULL;
Thread*L_queuef = NULL;
Thread*L_queuer = NULL;

void alarm_handler(){
    printf("%d\n",counter++);
    alarm(1);
}

void handler(){
    printf("a");
}
int main(int argc,char** argv)
{
    signal(SIGTSTP,handler);
    signal(SIGALRM,alarm_handler);
    alarm(1);
    //StartSchedulingSimulation();
    
    Thread *root = getthreads();
    Thread *temp = NULL;
    while(root){
        temp = root;
        root = root->next;
        if(temp->priority == 0){
            enqueue(&L_queuef,&L_queuer,temp);
        }else if(temp->priority == 1){
            enqueue(&M_queuef,&M_queuer,temp);
        }else if(temp->priority == 2){
            enqueue(&H_queuef,&H_queuer,temp);
        }
    }
    puts("H");
    while(H_queuef){
        temp = dequeue(&H_queuef,&H_queuer);
        printf("%s\n",temp->name);
    }
    puts("M");
    while(M_queuef){
        temp = dequeue(&M_queuef,&M_queuer);
        printf("%s\n",temp->name);
    }
    puts("L");
    while(L_queuef){
        temp = dequeue(&L_queuef,&L_queuer);
        printf("%s\n",temp->name);
    }
    

    while(1){
        printf("a\n");
        sleep(1);
    }

    return 0;
}

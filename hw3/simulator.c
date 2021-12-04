#include "os2021_thread_api.h"

void alarm_handler(){
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
    
    show_info();
    

    while(1){
        printf("a\n");
        sleep(1);
    }

    return 0;
}

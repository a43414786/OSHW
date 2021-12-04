#include "os2021_thread_api.h"

void alarm_handler(){
    
    alarm(1);
}

void handler(){
    
    printf("a");
    //show_info();
    
}
int main(int argc,char** argv)
{
    signal(SIGTSTP,handler);
    signal(SIGALRM,alarm_handler);
    alarm(1);
    //StartSchedulingSimulation();
    

    while(1){
        sleep(1);
    }

    return 0;
}

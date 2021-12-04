#include "os2021_thread_api.h"

void alarm_handler(){
    
    alarm(1);
}

void handler(){
    
    show_info();
    
}
int main(int argc,char** argv)
{
    signal(SIGTSTP,handler);
    signal(SIGALRM,alarm_handler);
    Dispatcher();
    //StartSchedulingSimulation();

    while(1){
    }

    return 0;
}

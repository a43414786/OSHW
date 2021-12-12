#include "os2021_thread_api.h"


void zhandler(){
    
    show_info();
    
}
int main(int argc,char** argv)
{
    signal(SIGTSTP,zhandler);
    signal(SIGALRM,handler);
    StartSchedulingSimulation();

    return 0;
}

#include "os2021_thread_api.h"


void zhandler()
{

    show_info();

}
int main(int argc,char** argv)
{
    signal(SIGTSTP,zhandler);
    signal(SIGALRM,handler);
    OS2021_ThreadCreate("random_1","Function2","M",1);
    while(1);
    //StartSchedulingSimulation();

    return 0;
}

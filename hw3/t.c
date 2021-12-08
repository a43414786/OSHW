#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
int count = 0;
void h(){
    count++;
    printf("%d\n",count);
}
int main(){
    struct itimerval Signaltimer;
    signal(SIGVTALRM,h);
    Signaltimer.it_interval.tv_usec = 500000;
    Signaltimer.it_interval.tv_sec = 0;
    Signaltimer.it_value.tv_sec = 0;
    Signaltimer.it_value.tv_usec = 500000;

    setitimer(ITIMER_VIRTUAL,&Signaltimer,NULL);
    while(1);
    return 0;
}
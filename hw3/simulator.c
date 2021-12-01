//#include "os2021_thread_api.h"
#include <string.h>
#include <stdio.h>

typedef struct node{
	char name[10];
	char function[10];
	int priority;
	int cancel_mode;
}Node;

int main(int argc,char** argv)
{
    //StartSchedulingSimulation();
    Node a;
    strcpy(a.name,"123");

    strcpy(a.function,"456");

    a.priority = 1;
    
    a.cancel_mode = 1;

    printf("%s %s %d %d\n",a.name,a.function,a.priority,a.cancel_mode);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


#define STACK_SIZE 8192

int counter = 0;
void CreateContext(ucontext_t *context, ucontext_t *next_context, void *func)
{
    getcontext(context);
    context->uc_stack.ss_sp = malloc(STACK_SIZE);
    context->uc_stack.ss_size = STACK_SIZE;
    context->uc_stack.ss_flags = 0;
    context->uc_link = next_context;
    makecontext(context,(void (*)(void))func,0);
}

void Function2(void)
{
    int the_num;

    int min = 65400;
    int max = 65410;

    while(1)
    {
        srand(time(NULL));
        the_num = rand() % (max - min + 1) + min;
        if(the_num == 65409)
        {
            fprintf(stdout,"I found 65409.\n");
            fflush(stdout);
            min = 0;
            max = 0;
        }
        printf("%d Function2\n",counter%3);
    }
}
ucontext_t test[3];
void h(){
    
    int temp = counter;

    counter++;

    alarm(1);

    swapcontext(&test[temp%3],&test[counter%3]);
    
}

int main(){

    signal(SIGALRM,h);

    alarm(1);

    CreateContext(&test[0],NULL,&Function2);
    CreateContext(&test[1],NULL,&Function2);
    CreateContext(&test[2],NULL,&Function2);
    setcontext(&test[0]);

    return 0;
}
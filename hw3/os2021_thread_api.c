#include "os2021_thread_api.h"
struct itimerval Signaltimer;
ucontext_t dispatch_context;
ucontext_t timer_context;

typedef struct thread_status
{
    char name[20];
    char function[20];
    char priority_init[2];
    char priority_cur[2];
    int cancelmode;
    int cancelsig;
    int pid;
    int queueing_time;
    int waiting_time;
    int qt;
    int time;
    int event;
    char state[20];
    ucontext_t ctx;
    struct thread_status *next;
} Thread;

Thread*ready[3] = {NULL, NULL, NULL};
Thread*time_waiting[3] = {NULL, NULL, NULL};
Thread*event_waiting[3] = {NULL, NULL, NULL};
Thread*running = NULL;
Thread*terminate = NULL;

int pid_counter = 1;


Thread*find_thread(Thread**root,char*name)
{
    Thread*post = *root;
    while(post)
    {
        if(!strcmp(post->name,name))
        {
            return post;
        }
        post = post->next;
    }
    return NULL;
}

Thread*get_thread(Thread**root,char*name)
{
    Thread*pre,*post;
    pre = post = *root;
    while(post)
    {
        if(!strcmp(post->name,name))
        {
            if((post == pre) && !(post->next))
            {
                *root = NULL;
            }
            else if(post == pre)
            {
                *root = post->next;
            }
            else
            {
                pre->next = post->next;
            }
            post->next = NULL;
            return post;
        }
        pre = post;
        post = post->next;
    }
    return NULL;
}

Thread*find_waiting_thread(Thread**root,int id)
{
    Thread*pre,*post;
    pre = post = *root;
    while(post)
    {
        if(post->event == id)
        {
            if((post == pre) && !(post->next))
            {
                *root = NULL;
            }
            else if(post == pre)
            {
                *root = post->next;
            }
            else
            {
                pre->next = post->next;
            }
            post->next = NULL;
            return post;
        }
        pre = post;
        post = post->next;
    }
    return NULL;
}

void enqueue(Thread**root,Thread*input)
{
    Thread*temp = *root;
    input->next = temp;
    *root = input;
}

Thread *dequeue(Thread**root)
{
    Thread*pre,*post;
    pre = post = *root;
    if(post)
    {
        while(post->next)
        {
            pre = post;
            post = post->next;
        }
    }
    if(!pre)
    {
        return NULL;
    }
    else if(post == pre)
    {
        *root = NULL;
        return post;
    }
    else
    {
        pre->next = NULL;
        return post;
    }

}

void init_threads()
{
    FILE*fp=fopen("init_threads.json","r");
    char input[20];
    char inputs[4][20];
    int input_flag[4] = {0,0,0,0};
    char word;
    int flag = 0;
    int counter = 0;
    int input_counter = 0;
    memset(input,0,sizeof(input));
    memset(inputs,0,sizeof(inputs));
    while((word = getc(fp)) != EOF)
    {
        if(word == '\"')
        {
            if(input[0])
            {
                if(!strcmp(input,"name"))
                {
                    input_flag[0] = 1;
                }
                else if(!strcmp(input,"entry function"))
                {
                    input_flag[1] = 1;
                }
                else if(!strcmp(input,"priority"))
                {
                    input_flag[2] = 1;
                }
                else if(!strcmp(input,"cancel mode"))
                {
                    input_flag[3] = 1;
                }
                else
                {
                    if(input_flag[0])
                    {
                        input_counter++;
                        input_flag[0] = 0;
                        strcpy(inputs[0],input);
                    }
                    else if(input_flag[1])
                    {
                        input_counter++;
                        input_flag[1] = 0;
                        strcpy(inputs[1],input);
                    }
                    else if(input_flag[2])
                    {
                        input_counter++;
                        input_flag[2] = 0;
                        strcpy(inputs[2],input);
                    }
                    else if(input_flag[3])
                    {
                        input_counter++;
                        input_flag[3] = 0;
                        strcpy(inputs[3],input);
                    }
                }
            }
            flag = !flag;
            memset(input,0,sizeof(input));
            counter = 0;
            continue;
        }
        if(input_counter == 4)
        {
            input_counter = 0;
            OS2021_ThreadCreate(inputs[0],inputs[1],inputs[2],inputs[3][0] - '0');
            memset(inputs,0,sizeof(inputs));
        }
        if(flag)
        {
            input[counter++] = word;
        }
    }
    fclose(fp);
}

void pr_info(Thread *temp)
{
    while(temp)
    {
        if(strlen(temp->name) > 7)
        {
            printf("*\t%d\t%s\t%s\t%s\t\t%s\t\t%d\t%d\t*\n",temp->pid,temp->name,temp->state,temp->priority_init,temp->priority_cur,temp->queueing_time,temp->waiting_time);
        }
        else
        {
            printf("*\t%d\t%s\t\t%s\t%s\t\t%s\t\t%d\t%d\t*\n",temp->pid,temp->name,temp->state,temp->priority_init,temp->priority_cur,temp->queueing_time,temp->waiting_time);
        }
        temp = temp->next;
    }
}

void show_info()
{
    puts("\n****************************************************************************************");
    puts("*\tTID\tName\t\tState\tB_Priority\tC_Priority\tQ_Time\tW_Time\t*");
    pr_info(running);
    pr_info(ready[0]);
    pr_info(ready[1]);
    pr_info(ready[2]);
    pr_info(time_waiting[0]);
    pr_info(time_waiting[1]);
    pr_info(time_waiting[2]);
    pr_info(event_waiting[0]);
    pr_info(event_waiting[1]);
    pr_info(event_waiting[2]);
    puts("****************************************************************************************");

}

void increase(Thread**root)
{
    Thread*temp = *root;
    switch(temp->priority_cur[0])
    {
    case 'H':
        temp->qt = 100;
        temp->priority_cur[0] = 'H';
        break;
    case 'M':
        temp->qt = 100;
        temp->priority_cur[0] = 'H';
        printf("The priority of thread %s is changed form M to H\n",temp->name);
        break;
    case 'L':
        temp->qt = 200;
        temp->priority_cur[0] = 'M';
        printf("The priority of thread %s is changed form L to M\n",temp->name);
        break;
    default:
        break;
    }
    *root = temp;
}
void decrease(Thread**root)
{
    Thread*temp = *root;
    switch(temp->priority_cur[0])
    {
    case 'H':
        temp->qt = 200;
        strcpy(temp->priority_cur,"M");
        printf("The priority of thread %s is changed form H to M\n",temp->name);
        break;
    case 'M':
        temp->qt = 300;
        strcpy(temp->priority_cur,"L");
        printf("The priority of thread %s is changed form M to L\n",temp->name);
        break;
    case 'L':
        temp->qt = 300;
        strcpy(temp->priority_cur,"L");
        break;
    default:
        break;
    }
    *root = temp;
}

Thread* time_wait(Thread **root)
{
    Thread*pre,*post;
    Thread *result = NULL;
    pre = post = *root;
    while(post)
    {
        post->waiting_time += 10;
        post->time -= 10;
        if(!(post->time))
        {
            if((post == pre) && !(post->next))
            {
                *root = NULL;
            }
            else if(post == pre)
            {
                *root = post->next;
            }
            else
            {
                pre->next = post->next;
            }
            post->next = NULL;
            result = post;
        }
        pre = post;
        post = post->next;
    }
    return result;
}

void time_queueing(Thread **root)
{
    Thread*temp = *root;
    while(temp)
    {
        temp->queueing_time += 10;
        temp = temp->next;
    }
}

void wait_event(Thread **root)
{
    Thread*temp = *root;
    while(temp)
    {
        temp->waiting_time += 10;
        temp = temp->next;
    }
}

void handler()
{
    Thread*temp[3];
    time_queueing(&(ready[0]));
    time_queueing(&(ready[1]));
    time_queueing(&(ready[2]));
    wait_event(&(event_waiting[0]));
    wait_event(&(event_waiting[1]));
    wait_event(&(event_waiting[2]));
    temp[0] = time_wait(&(time_waiting[0]));
    temp[1] = time_wait(&(time_waiting[1]));
    temp[2] = time_wait(&(time_waiting[2]));
    if(temp[0])
    {
        memset(&(temp[0]->state),0,sizeof(temp[0]->state));
        strcpy(temp[0]->state,"READY");
        enqueue(&(ready[0]),temp[0]);
    }
    else if(temp[1])
    {
        memset(&(temp[1]->state),0,sizeof(temp[1]->state));
        strcpy(temp[1]->state,"READY");
        enqueue(&(ready[1]),temp[1]);
    }
    else if(temp[2])
    {
        memset(&(temp[2]->state),0,sizeof(temp[2]->state));
        strcpy(temp[2]->state,"READY");
        enqueue(&(ready[2]),temp[2]);
    }

    if(!running) return;
    running->qt -= 10;
    if(!(running->qt))
    {
        decrease(&running);
        memset(&(running->state),0,sizeof(running->state));
        strcpy(running->state,"READY");
        temp[0] = running;
        running = NULL;
        switch(temp[0]->priority_cur[0])
        {
        case 'H':
            enqueue(&(ready[2]),temp[0]);
            break;
        case 'M':
            enqueue(&(ready[1]),temp[0]);
            break;
        case 'L':
            enqueue(&(ready[0]),temp[0]);
            break;
        }
        swapcontext(&(temp[0]->ctx),&dispatch_context);
    }


}

int OS2021_ThreadCreate(char *job_name, char *p_function, char* priority, int cancel_mode)
{
    if(strcmp(p_function,"Function1") && strcmp(p_function,"Function2") && strcmp(p_function,"Function3") && strcmp(p_function,"Function4") && strcmp(p_function,"Function5") && strcmp(p_function,"ResourceReclaim"))
    {
        return -1;
    }
    Thread *temp = malloc(sizeof(Thread));
    memset(temp,0,sizeof(Thread));
    strcpy(temp->name,job_name);
    strcpy(temp->function,p_function);
    strcpy(temp->priority_init,priority);
    strcpy(temp->priority_cur,priority);
    temp->cancelmode = cancel_mode;
    temp->cancelsig = 0;
    temp->next = NULL;
    temp->pid = pid_counter++;
    temp->queueing_time = 0;
    temp->waiting_time = 0;
    strcpy(temp->state,"READY");
    switch(temp->priority_init[0])
    {
    case 'H':
        temp->qt = 100;
        enqueue(&(ready[2]),temp);
        break;
    case 'M':
        temp->qt = 200;
        enqueue(&(ready[1]),temp);
        break;
    case 'L':
        temp->qt = 300;
        enqueue(&(ready[0]),temp);
        break;
    }
    if(!strcmp(p_function,"Function1"))
    {
        CreateContext(&(temp->ctx),&dispatch_context,&Function1);
    }
    else if(!strcmp(p_function,"Function2"))
    {
        CreateContext(&(temp->ctx),&dispatch_context,&Function2);
    }
    else if(!strcmp(p_function,"Function3"))
    {
        CreateContext(&(temp->ctx),&dispatch_context,&Function3);
    }
    else if(!strcmp(p_function,"Function4"))
    {
        CreateContext(&(temp->ctx),&dispatch_context,&Function4);
    }
    else if(!strcmp(p_function,"Function5"))
    {
        CreateContext(&(temp->ctx),&dispatch_context,&Function5);
    }
    else if(!strcmp(p_function,"ResourceReclaim"))
    {
        CreateContext(&(temp->ctx),&dispatch_context,&ResourceReclaim);
    }
    return pid_counter;
}

void do_cancel(Thread *root,char *job_name)
{
    Thread*result = NULL;
    Thread*temp = root;
    result = find_thread(&temp,job_name);
    if(result)
    {
        if(result->cancelmode)
        {
            result->cancelsig = 1;
        }
        else
        {
            result = get_thread(&temp,job_name);
            memset(&(result->state),0,sizeof(result->state));
            strcpy(result->state,"TERMINATED");
            enqueue(&(terminate),result);
        }
    }
}

void OS2021_ThreadCancel(char *job_name)
{
    do_cancel(ready[2],job_name);
    do_cancel(ready[1],job_name);
    do_cancel(ready[0],job_name);
    do_cancel(time_waiting[2],job_name);
    do_cancel(time_waiting[1],job_name);
    do_cancel(time_waiting[0],job_name);
    do_cancel(event_waiting[2],job_name);
    do_cancel(event_waiting[1],job_name);
    do_cancel(event_waiting[0],job_name);

}

void OS2021_ThreadWaitEvent(int event_id)
{
    Thread*temp = running;
    running = NULL;
    temp->event = event_id;
    printf("%s wants to wait for event %d\n",temp->name,temp->event);
    memset(&(temp->state),0,sizeof(temp->state));
    strcpy(temp->state,"WAITING");
    increase(&temp);
    switch(temp->priority_cur[0])
    {
    case 'H':
        enqueue(&(event_waiting[2]),temp);
        break;
    case 'M':
        enqueue(&(event_waiting[1]),temp);
        break;
    case 'L':
        enqueue(&(event_waiting[0]),temp);
        break;
    }
    ResetTimer();
    swapcontext(&(temp->ctx),&dispatch_context);
}

void OS2021_ThreadSetEvent(int event_id)
{
    Thread*temp = NULL;
    temp = find_waiting_thread(&(event_waiting[2]),event_id);
    if(temp)
    {
        memset(&(temp->state),0,sizeof(temp->state));
        strcpy(temp->state,"READY");
        enqueue(&(ready[2]),temp);
        printf("%s changes the status of %s to READY\n",running->name,temp->name);
        return;
    }
    temp = find_waiting_thread(&(event_waiting[1]),event_id);
    if(temp)
    {
        memset(&(temp->state),0,sizeof(temp->state));
        strcpy(temp->state,"READY");
        enqueue(&(ready[1]),temp);
        printf("%s changes the status of %s to READY\n",running->name,temp->name);
        return;
    }
    temp = find_waiting_thread(&(event_waiting[0]),event_id);
    if(temp)
    {
        memset(&(temp->state),0,sizeof(temp->state));
        strcpy(temp->state,"READY");
        enqueue(&(ready[0]),temp);
        printf("%s changes the status of %s to READY\n",running->name,temp->name);
        return;
    }
    return;

}

void OS2021_ThreadWaitTime(int msec)
{
    Thread*temp = running;
    running = NULL;
    temp->time = msec*10;
    memset(&(temp->state),0,sizeof(temp->state));
    strcpy(temp->state,"WAITING");
    increase(&temp);
    switch(temp->priority_cur[0])
    {
    case 'H':
        enqueue(&(time_waiting[2]),temp);
        break;
    case 'M':
        enqueue(&(time_waiting[1]),temp);
        break;
    case 'L':
        enqueue(&(time_waiting[0]),temp);
        break;
    }
    ResetTimer();
    swapcontext(&(temp->ctx),&dispatch_context);
}

void OS2021_DeallocateThreadResource()
{
    if(!terminate)
    {
        return;
    }
    Thread*pre = terminate;
    Thread*post = pre;
    terminate = NULL;
    while(post)
    {
        pre = post;
        post = post->next;
        free(pre);
    }
}

void OS2021_TestCancel()
{
    Thread *temp = running;
    if(temp->cancelsig)
    {
        running = NULL;
        memset(&(temp->state),0,sizeof(temp->state));
        strcpy(temp->state,"TERMINATED");
        enqueue(&(terminate),temp);
        swapcontext(&(temp->ctx),&(dispatch_context));
    }
}

void CreateContext(ucontext_t *context, ucontext_t *next_context, void *func)
{
    getcontext(context);
    context->uc_stack.ss_sp = malloc(STACK_SIZE);
    context->uc_stack.ss_size = STACK_SIZE;
    context->uc_stack.ss_flags = 0;
    context->uc_link = next_context;
    makecontext(context,(void (*)(void))func,0);
}
void ResetTimer()
{
    Signaltimer.it_value.tv_sec = 0;
    Signaltimer.it_value.tv_usec = 10000;
    if(setitimer(ITIMER_REAL, &Signaltimer, NULL) < 0)
    {
        printf("ERROR SETTING TIME SIGALRM!\n");
    }
}


void Dispatcher()
{
    getcontext(&dispatch_context);

    Signaltimer.it_interval.tv_usec = 10000; //10 ms
    Signaltimer.it_interval.tv_sec = 0;
    ResetTimer();

    Thread*temp;

    OS2021_ThreadCreate("reclaimer","ResourceReclaim","L",1);

    init_threads();

    while(1)
    {
        temp = dequeue(&(ready[2]));
        if(temp)
        {
            running = temp;
            memset(&(temp->state),0,sizeof(temp->state));
            strcpy(temp->state,"RUNNING");
            swapcontext(&dispatch_context,&(temp->ctx));
        }
        else
        {
            temp = dequeue(&(ready[1]));
            if(temp)
            {
                running = temp;
                memset(&(temp->state),0,sizeof(temp->state));
                strcpy(temp->state,"RUNNING");
                swapcontext(&dispatch_context,&(temp->ctx));
            }
            else
            {
                temp = dequeue(&(ready[0]));
                if(temp)
                {
                    running = temp;
                    memset(&(temp->state),0,sizeof(temp->state));
                    strcpy(temp->state,"RUNNING");
                    swapcontext(&dispatch_context,&(temp->ctx));
                }
            }
        }
    }
}

void StartSchedulingSimulation()
{
    /*Set Timer*/
    Signaltimer.it_interval.tv_usec = 10000;
    Signaltimer.it_interval.tv_sec = 0;
    ResetTimer();
    /*Create Context*/
    CreateContext(&dispatch_context, &timer_context, &Dispatcher);
    setcontext(&dispatch_context);
}
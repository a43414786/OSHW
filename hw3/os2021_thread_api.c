#include "os2021_thread_api.h"

struct itimerval Signaltimer;
ucontext_t dispatch_context;
ucontext_t timer_context;
ucontext_t scheduler_context;

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
Thread*next_run = NULL;

int pid_counter = 1;
int event1 = 0;
int event2 = 0;

Thread*get_thread(Thread**root,char*name,int mode)
{
    Thread*pre,*post;
    pre = post = *root;
    while(post)
    {
        if(!strcmp(post->name,name))
        {
            if(!mode){
                return post;
            }else{
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
    if(input){
        input->next =NULL;
    }
    if(temp){
        while(temp->next){
            temp=temp->next;
        }
        temp->next = input;
    }else{
        *root = input;
    }

}

Thread *dequeue(Thread**root)
{
    Thread*temp = *root;
    if(temp){
        *root = temp->next;
        temp->next = NULL;
        return temp;
    }else{
        return NULL;
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
    if(!(*root)) return;
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
    if(!(*root)) return;
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

void time_calculate()
{
    Thread*temp = NULL;
    for(int i = 0 ; i < 3 ; i++){
        temp = ready[i];
        while(temp){
            temp->queueing_time += 10;
            temp = temp->next;
        }
    }
    for(int i = 0 ; i < 3 ; i++){
        temp = event_waiting[i];
        while(temp){
            temp->waiting_time += 10;
            temp = temp->next;
        }
    }
    for(int i = 0 ; i < 3 ; i++){
        temp = time_waiting[i];
        while(temp)
        {
            temp->waiting_time += 10;
            temp->time -= 10;
            if(!(temp->time))
            {
                event2 = 1;
            }
            temp = temp->next;
        }
    }
}

void wait2ready(Thread**root,char priority){
    Thread*temp = *root;
    switch(priority){
        case 'H':
            enqueue(&(ready[2]),temp);
            break;
        case 'M':
            enqueue(&(ready[1]),temp);
            break;
        case 'L':
            enqueue(&(ready[0]),temp);
            break;    
    }
}

void endwait(){ 
    Thread*pre,*post;
    for(int i = 0 ; i < 3 ; i++){
        pre = post = time_waiting[i];
        while(post)
        {
            if(!(post->time))
            {
                if((pre == post) && (!post->next)){
                    time_waiting[i] = NULL;
                    wait2ready(&post,post->priority_cur[0]);
                    break;
                }else if(pre == post){
                    time_waiting[i] = post->next;
                    post->next = NULL;
                    wait2ready(&post,post->priority_cur[0]);
                    pre = post = time_waiting[i];
                    continue;
                }else{
                    pre->next = post->next;
                    post->next = NULL;
                    wait2ready(&post,post->priority_cur[0]);
                    post = pre->next;
                    continue;
                }
            }
            pre = post;
            post = post->next;
        }
    }
}


void handler()
{
    time_calculate();
    
    if(running){
        running->qt -= 10;
        if(!(running->qt))
        {
            event1 = 1;
        }
    }

    ResetTimer();

    if(event1 || event2 || (!running)){
        if(running){
            swapcontext(&(running->ctx),&scheduler_context);
        }else{
            setcontext(&scheduler_context);
        }
    }

}

void Scheduler(){
    Thread *temp = NULL;
    while(1){
        if(event1){
            event1 = 0;
            decrease(&running);
            memset(&(running->state),0,sizeof(running->state));
            strcpy(running->state,"READY");
            temp = dequeue(running);
            switch(temp->priority_cur[0])
            {
                case 'H':
                    enqueue(&(ready[2]),temp);
                    break;
                case 'M':
                    enqueue(&(ready[1]),temp);
                    break;
                case 'L':
                    enqueue(&(ready[0]),temp);
                    break;
            }
        }
        if(event2){
            event2 = 0;
            endwait();
        }

        temp = dequeue(&(ready[2]));
        if(temp)
        {
            enqueue(&next_run,temp);
            swapcontext(&scheduler_context,&dispatch_context);
        }
        else
        {
            temp = dequeue(&(ready[1]));
            if(temp)
            {
                enqueue(&next_run,temp);
                swapcontext(&scheduler_context,&dispatch_context);  
            }
            else
            {
                temp = dequeue(&(ready[0]));
                if(temp)
                {
                    enqueue(&next_run,temp);
                    swapcontext(&scheduler_context,&dispatch_context);
                }
            }
        }
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

void do_cancel(Thread **root,char *job_name)
{
    Thread*result = get_thread(root,job_name,0);
    if(result)
    {
        if(result->cancelmode)
        {
            result->cancelsig = 1;
        }
        else
        {
            result = get_thread(root,job_name,1);
            memset(&(result->state),0,sizeof(result->state));
            strcpy(result->state,"TERMINATED");
            enqueue(&(terminate),result);
        }
    }
}

void OS2021_ThreadCancel(char *job_name)
{
    printf("delete %s\n",job_name);
    for(int i = 0 ; i < 3 ; i++){
        do_cancel(&(ready[i]),job_name);
        do_cancel(&(time_waiting[i]),job_name);
        do_cancel(&(event_waiting[i]),job_name);
    }
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
    swapcontext(&(temp->ctx),&scheduler_context);
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
    Thread*temp = dequeue(&running);
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
    swapcontext(&(temp->ctx),&scheduler_context);
}

void OS2021_DeallocateThreadResource()
{
    Thread*temp = NULL;
    while(terminate){
        temp = dequeue(&terminate);
        free(temp);
    }
}

void OS2021_TestCancel()
{
    Thread *temp = running;
    if(temp->cancelsig == 1)
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
    Thread*temp;

    swapcontext(&dispatch_context,&scheduler_context);
    
    while(1)
    {
        temp = dequeue(&next_run);
        memset(&(temp->state),0,sizeof(temp->state));
        strcpy(temp->state,"RUNNING");
        enqueue(&running,temp);
        swapcontext(&dispatch_context,&(running->ctx));
    }
}

void StartSchedulingSimulation()
{
    /*Parsing initial threads*/
    OS2021_ThreadCreate("reclaimer","ResourceReclaim","L",1);

    init_threads();
    /*Set Timer*/
    Signaltimer.it_interval.tv_usec = 10000;
    Signaltimer.it_interval.tv_sec = 0;
    ResetTimer();
    /*Create scheduler Context*/
    CreateContext(&scheduler_context, &timer_context, &Scheduler);
    /*Create Context*/
    CreateContext(&dispatch_context, &timer_context, &Dispatcher);
    setcontext(&dispatch_context);
}

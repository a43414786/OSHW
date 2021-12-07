#include "os2021_thread_api.h"

struct itimerval Signaltimer;
ucontext_t dispatch_context;
ucontext_t timer_context;

typedef struct thread_status{
    char name[20];
    char function[20];
    int priority_init;
    int priority_cur;
    int cancelmode;
    int pid;
    int queueing_time;
    int waiting_time;
    char state[10];
    ucontext_t ctx;
    struct thread_status *front;
    struct thread_status *next;
}Thread;

Thread*H_queuef = NULL;
Thread*H_queuer = NULL;
Thread*M_queuef = NULL;
Thread*M_queuer = NULL;
Thread*L_queuef = NULL;
Thread*L_queuer = NULL;
Thread*runnning = NULL;

int pid_counter = 1;

void enqueue(Thread**front,Thread**rear,Thread*input){
    Thread *f = *front;
    input->front = input->next = NULL;
    if(!f){
        *front = input;
        *rear = input;
        return;
    }
    input->next = f;
    f->front = input;
    *front = input;
}

Thread *dequeue(Thread**front,Thread**rear){
    Thread *r = *rear;
    if(!r){
        return NULL;
    }
    Thread *temp = r->front;
    r->front = NULL;
    r->next = NULL;
    if(!temp){
        *front = NULL;
        *rear = NULL;
    }else{
        temp->next = NULL;
        *rear = temp;
    }
    return r;
}

void addnode_thread(Thread**inroot,Thread*input){
    Thread *temp = *inroot;
    if(!temp){
        *inroot = input;
        return;
    }
    while(temp->next){
        temp = temp->next;
    }
    input->front = temp;
    temp->next = input;
    return;
}

Thread*getthreads(){
    FILE*fp=fopen("init_threads.json","r");
    Thread*root = NULL;
    Thread*temp = NULL;
    Thread*thread_root = NULL;
    char input[20];
    char word;
    int flag = 0;
    int counter = 0;
    memset(input,0,sizeof(input));
    while((word = getc(fp)) != EOF){
        if(word == '\"'){
            if(input[0]){
                temp = malloc(sizeof(Thread));
                strcpy(temp->name,input);
                addnode_thread(&root,temp);
            }
            flag = !flag;
            memset(input,0,sizeof(input));
            counter = 0;
            continue;
        }
        if(flag){
            input[counter++] = word;
        }
    }
    temp = root;
    root = root->next;
    free(temp);
    while(root){
        Thread*temp2 = malloc(sizeof(Thread));
        temp2->front = NULL;
        memset(temp2,0,sizeof(Thread));
        for(int i = 0 ; i < 4 ; i++){
            if(strcmp(root->name,"name") == 0){
                temp = root;
                root = root->next;
                free(temp);
                strcpy(temp2->name,root->name);    
            }
            else if(strcmp(root->name,"entry function") == 0){
                temp = root;
                root = root->next;
                free(temp);
                strcpy(temp2->function,root->name);
            }
            else if(strcmp(root->name,"priority") == 0){
                temp = root;
                root = root->next;
                free(temp);
                if(strcmp(root->name,"H") == 0){
                    temp2->priority_init = 2;
                }else if(strcmp(root->name,"M") == 0){
                    temp2->priority_init = 1;
                }else if(strcmp(root->name,"L") == 0){
                    temp2->priority_init = 0;
                }
            }
            else if(strcmp(root->name,"cancel mode") == 0){
                temp = root;
                root = root->next;
                free(temp);
                temp2->cancelmode = root->name[0] - '0';
            }
            temp = root;
            root = root->next;
            free(temp);
        }
        temp2->next = NULL;
        addnode_thread(&thread_root,temp2);        
    }

    return thread_root;
}

void pr_info(Thread *temp){
    while(temp){ 
        char b,c;
        switch (temp->priority_cur)
        {
        case 0:
            c = 'L';
            break;
        
        case 1:
            c = 'M';
            break;
        
        case 2:
            c = 'H';
            break;
        default:
            break;
        }
        switch (temp->priority_init)
        {
        case 0:
            b = 'L';
            break;
        
        case 1:
            b = 'M';
            break;
        
        case 2:
            b = 'H';
            break;
        default:
            break;
        }
        printf("*\t%d\t%s\t\t%s\t%c\t\t%c\t\t%d\t%d\t*\n",temp->pid,temp->name,temp->state,b,c,temp->queueing_time,temp->waiting_time);
        temp = temp->next;
    }
}

void show_info(){
    puts("\n****************************************************************************************");
    puts("*\tTID\tName\t\tState\tB_Priority\tC_Priority\tQ_Time\tW_Time\t*");
    pr_info(runnning);
    pr_info(L_queuef);
    pr_info(M_queuef);
    pr_info(H_queuef);   
    puts("****************************************************************************************");
    
}

void handler(){
    if(!runnning) return;
    Thread *temp = runnning;
    runnning = NULL;
    enqueue(&H_queuef,&H_queuer,temp);
    alarm(1);
    swapcontext(&(temp->ctx),&dispatch_context);
}

void fu1(){
    while(1){
        //printf("fun1");
    }
}
void fu2(){
    while(1){
        //printf("fun2");
    }
}
void fu3(){
    while(1){
        //printf("fun3");
    }
}

int OS2021_ThreadCreate(char *job_name, char *p_function, int priority, int cancel_mode)
{   
    if(strcmp(p_function,"Function1") && strcmp(p_function,"Function2") && strcmp(p_function,"Function3") && strcmp(p_function,"Function4") && strcmp(p_function,"Function5"))
    {
        return -1;
    }
    Thread *temp = malloc(sizeof(Thread));
    memset(temp,0,sizeof(Thread));
    strcpy(temp->name,job_name);
    strcpy(temp->function,p_function);
    temp->priority_init = priority;
    temp->priority_cur = priority;
    temp->cancelmode = cancel_mode;
    temp->front = NULL;
    temp->next = NULL;
    temp->pid = pid_counter++;
    temp->queueing_time = 0;
    temp->waiting_time = 0;
    strcpy(temp->state,"READY");
    
    if(priority == 0){
        enqueue(&L_queuef,&L_queuer,temp);
    }else if(priority == 1){
        enqueue(&M_queuef,&M_queuer,temp);
    }else if(priority == 2){
        enqueue(&H_queuef,&H_queuer,temp);
    }
    if(pid_counter%3 == 0){
        CreateContext(&(temp->ctx),&dispatch_context,&fu1);
    }
    else if(pid_counter%3 == 1){
        CreateContext(&(temp->ctx),&dispatch_context,&fu2);
    }
    else if(pid_counter%3 == 2){
        CreateContext(&(temp->ctx),&dispatch_context,&fu3);
    }
    return pid_counter;
}

void OS2021_ThreadCancel(char *job_name)
{

}

void OS2021_ThreadWaitEvent(int event_id)
{

}

void OS2021_ThreadSetEvent(int event_id)
{

}

void OS2021_ThreadWaitTime(int msec)
{

}

void OS2021_DeallocateThreadResource()
{

}

void OS2021_TestCancel()
{

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
    Signaltimer.it_value.tv_usec = 0;
    if(setitimer(ITIMER_REAL, &Signaltimer, NULL) < 0)
    {
        printf("ERROR SETTING TIME SIGALRM!\n");
    }
}

void Dispatcher()
{
    getcontext(&dispatch_context);
    Thread *root = getthreads();
    Thread *temp = NULL;
    while(root){
        OS2021_ThreadCreate(root->name,root->function,root->priority_init,root->cancelmode);
        temp = root;
        root = root->next;
        free(temp);
    }
    //while(1);
    while(1){
        temp = dequeue(&H_queuef,&H_queuer);
        runnning = temp;
        swapcontext(&dispatch_context,&(temp->ctx));
    }
}

void StartSchedulingSimulation()
{
    /*Set Timer*/
    Signaltimer.it_interval.tv_usec = 0;
    Signaltimer.it_interval.tv_sec = 0;
    ResetTimer();
    /*Create Context*/
    CreateContext(&dispatch_context, &timer_context, &Dispatcher);
    setcontext(&dispatch_context);
}

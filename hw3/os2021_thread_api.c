#include "os2021_thread_api.h"

struct itimerval Signaltimer;
ucontext_t dispatch_context;
ucontext_t timer_context;

extern Thread*H_queuef;
extern Thread*H_queuer;
extern Thread*M_queuef;
extern Thread*M_queuer;
extern Thread*L_queuef;
extern Thread*L_queuer;

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
    if(!temp){
        *front = NULL;
        *rear = NULL;
    }else{
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
                    temp2->priority = 2;
                }else if(strcmp(root->name,"M") == 0){
                    temp2->priority = 1;
                }else if(strcmp(root->name,"L") == 0){
                    temp2->priority = 0;
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


int OS2021_ThreadCreate(char *job_name, char *p_function, int priority, int cancel_mode)
{
    printf("%s\n",job_name);
    printf("%s\n",p_function);
    printf("%d\n",priority);
    printf("%d\n",cancel_mode);
    return -1;
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

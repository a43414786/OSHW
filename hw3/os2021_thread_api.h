#ifndef OS2021_API_H
#define OS2021_API_H

#define STACK_SIZE 8192

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "function_libary.h"

typedef struct thread_status{
    char name[20];
    char function[20];
    int priority;
    int cancelmode;
    int pid;
    struct thread_status *front;
    struct thread_status *next;
}Thread;

Thread*H_queuef = NULL;
Thread*H_queuer = NULL;
Thread*M_queuef = NULL;
Thread*M_queuer = NULL;
Thread*L_queuef = NULL;
Thread*L_queuer = NULL;

void enqueue(Thread**front,Thread**rear,Thread*input);
Thread *dequeue(Thread**front,Thread**rear);
void addnode_thread(Thread**inroot,Thread*input);
Thread*getthreads();


int OS2021_ThreadCreate(char *job_name, char *p_function, int priority, int cancel_mode);
void OS2021_ThreadCancel(char *job_name);
void OS2021_ThreadWaitEvent(int event_id);
void OS2021_ThreadSetEvent(int event_id);
void OS2021_ThreadWaitTime(int msec);
void OS2021_DeallocateThreadResource();
void OS2021_TestCancel();


void CreateContext(ucontext_t *, ucontext_t *, void *);
void ResetTimer();
void Dispatcher();
void StartSchedulingSimulation();

#endif

#include <stdio.h>
#include <ucontext.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define st_size 1024*128
ucontext_t ctx[3];

int c0 = 0,c1 = 0,c2 = 0;
void handler(){
	printf("\n%d %d %d\n",c0,c1,c2);
}
void func1(){
	while(1){
		puts("func1");
		sleep(1);
		c1++;
		if(c1%10 == 9){
			swapcontext(&ctx[1],&ctx[0]);
		}
	}
	puts("func1 end");
}
void func2(){
	while(1){
		puts("func2");
		sleep(1);
		c2++;
		if(c2 %10 == 9){
			swapcontext(&ctx[2],&ctx[0]);
		}
	}
}

int main(){
	signal(SIGTSTP,handler);
	getcontext(&ctx[0]);
	getcontext(&ctx[1]);
	getcontext(&ctx[2]);

	ctx[1].uc_link = &ctx[0];
	ctx[1].uc_stack.ss_sp = malloc(st_size);
	ctx[1].uc_stack.ss_size = st_size;
	ctx[1].uc_stack.ss_flags = 0;
	makecontext(&ctx[1],(void*)&func1,0);

	ctx[2].uc_link = &ctx[0];
	ctx[2].uc_stack.ss_sp = malloc(st_size);
	ctx[2].uc_stack.ss_size = st_size;
	ctx[2].uc_stack.ss_flags = 0;
	makecontext(&ctx[2],(void*)&func2,0);
	while(1){
		if(c0 % 2 == 0){
			swapcontext(&ctx[0],&ctx[1]);
		}
		else{
			swapcontext(&ctx[0],&ctx[2]);
		}
		c0++;
	}
	printf("main\n");

	return 0;
}

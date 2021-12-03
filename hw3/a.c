#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int counter = 0;

void handle(int signal){
	counter += 10;
}
int main(){
	signal(SIGTSTP,handle);
	while(1)
	{
		printf("%d\n",counter);
		sleep(1);
		counter++;
	}
	
	return 0;
}

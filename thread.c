#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaphore; // 旗標
int counter = 0;

// 子執行緒函數
void* child() {
  for(int i = 0;i < 5;++i) {
    sem_wait(&semaphore); // 等待工作
    printf("Counter = %d\n", ++counter);
    sleep(1);
  }
  pthread_exit(NULL);
}

// 主程式
int main(void) {

  // 初始化旗標，僅用於本行程，初始值為 0
  sem_init(&semaphore, 0, 0);

  pthread_t t;
  pthread_create(&t, NULL, child, NULL);

  // 送出兩個工作
  printf("Post 2 jobs.\n");
  sem_post(&semaphore);
  sem_post(&semaphore);
  sleep(4);

  // 送出三個工作
  printf("Post 3 jobs.\n");
  sem_post(&semaphore);
  sem_post(&semaphore);
  sem_post(&semaphore);

  pthread_join(t, NULL);

  return 0;
}

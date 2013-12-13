#include "queue.c"
#include <pthread.h>

void spawnThreads(int n, int x);
void *dummy_function(void *arg);

int main(void)
{
  int n = 2;
  int x = 100000;

  srand(time(NULL));
  
  initialize_queue();
  for (int i = 0; i < 100; i++) {
    enqueue(rand());
  }
  
  printf(" spawnThreads(%d, %d);\n", n, x);
  spawnThreads(n, x);
}

void spawnThreads(int n, int x)
{
  pthread_t threadIds[n];
  for (int i = 0; i < n; ++i) {
    int *number = malloc(sizeof(*number));
    *number = x/n;
    pthread_create(&(threadIds[i]), NULL, dummy_function, (void * ) number);
    printf("Threadid: %lu\n", threadIds[i]);
  }

  for (int i = 0; i < n; ++i) {
    pthread_join(threadIds[i], NULL);
  }
}

void *dummy_function(void *arg)
{
  printf("Value: %d\n", *((int *) arg));
  for (int i = 0; i < *((int *) arg); i ++) {
    double coin = ((double) rand() / (RAND_MAX));
    if (coin < 0.8) {
      printf("Enqueue\n");
      enqueue(rand());
    }
    else {
      printf("Dequeue\n");
      int val;
      dequeue(&val);
      printf("Value: %d\n", val);
    }
  }
  return NULL;
}

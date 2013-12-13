#include "concurrent_queue_2locks.c"
/* #include "queue.c" */
#include <pthread.h>

void spawnThreads(int n, int x);
void *dummy_function(void *arg);

#define foo 100000 

int main(int argc, char *argv[])
{
  int n = 6;
  int x = 100000;

  srand(time(NULL));
  initialize_queue();
  for (int i = 0; i < 100; i++) {
    enqueue(rand());
  }

  struct timeval t0;
  struct timeval t1;
  gettimeofday(&t0, NULL);
  spawnThreads(n, x);
  gettimeofday(&t1, NULL);
  long elapsed = (t1.tv_sec - t0.tv_sec) * 1000000 + t1.tv_usec - t0.tv_usec;
  printf("Elapsed time: %ld\n", elapsed);
}

void spawnThreads(int n, int x)
{
  pthread_t threadIds[n];
  for (int i = 0; i < n; ++i) {
    printf("Launching thread: %d\n", i);
    int *number = malloc(sizeof(*number));
    *number = x/n;
    pthread_create(&(threadIds[i]), NULL, dummy_function, (void * ) number);
  }

  for (int i = 0; i < n; ++i) {
    pthread_join(threadIds[i], NULL);
  }
}

void *dummy_function(void *arg)
{
  for (int i = 0; i < *((int *) arg); i ++) {
    double coin = ((double) rand() / (RAND_MAX));
    if (coin < 0.8) {
      enqueue(rand());
    }
    else {
      int val;
      dequeue(&val);
    }
  }
  return NULL;
}

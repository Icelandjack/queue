#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>

void initialize_queue(void);
void enqueue(int val);
int dequeue(int *extractedValue);

struct queue   *global = NULL;

struct list {
  int          val;
  struct list *next;
};

struct queue {
  pthread_mutex_t headMutex;
  pthread_mutex_t tailMutex;
  struct list    *head;
  struct list    *tail;
};

int main()
{
  printf("hi\n");
  initialize_queue();
  return 0;
}

void initialize_queue(void)
{
  global = malloc(sizeof(struct queue));
  pthread_mutex_init(&global->headMutex, NULL);
  pthread_mutex_init(&global->tailMutex, NULL);

  struct list *dummy = malloc(sizeof(struct list));
  dummy->val = 42;
  dummy->next = NULL;

  global->head = dummy;
  global->tail = dummy;

  return;
}

void enqueue(int val)
{
  
  return;
}

int dequeue(int *extractedValue)
{
  /* queue is logically empty */
  if (global->head == NULL) {
    return 1;
  }

  
  return 0;
}

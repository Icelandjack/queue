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
  pthread_mutex_t head_mutex;
  pthread_mutex_t tail_mutex;
  struct list    *head;
  struct list    *tail;
};

/* int main() */
/* { */
/*   printf("hi\n"); */
/*   initialize_queue(); */

/*   int val; */
/*   enqueue(1); */
/*   dequeue(&val); */
/*   dequeue(&val); */

/*   return 0; */
/* } */

void initialize_queue(void)
{
  global = malloc(sizeof(struct queue));
  pthread_mutex_init(&global->head_mutex, NULL);
  pthread_mutex_init(&global->tail_mutex, NULL);

  struct list *dummy = malloc(sizeof(struct list));
  dummy->val = 42;
  dummy->next = NULL;

  global->head = dummy;
  global->tail = dummy;

  return;
}

void enqueue(int val)
{
  pthread_mutex_lock(&global->tail_mutex);
  pthread_mutex_lock(&global->head_mutex);

  struct list *new = malloc(sizeof(struct list));
  new->val = val;
  new->next = NULL;

  global->tail->next = new;
  global->tail = new;
  
  pthread_mutex_unlock(&global->tail_mutex);
  pthread_mutex_unlock(&global->head_mutex);
  return;
}

int dequeue(int *extractedValue)
{
  /* queue is logically empty */
  if (global->head->next == NULL) {
    return 1;
  }
  pthread_mutex_lock(&global->tail_mutex);
  pthread_mutex_lock(&global->head_mutex);

  struct list *old = global->head;
  
  global->head = old->next;
  *extractedValue = global->head->val;
  free(old);
  
  pthread_mutex_unlock(&global->tail_mutex);
  pthread_mutex_unlock(&global->head_mutex);
  
  return 0;
}

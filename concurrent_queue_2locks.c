#include <stdio.h>
#include <stdlib.h>
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

/* int main() */
/* { */
/*   printf("hi\n"); */
/*   initialize_queue(); */

/*   enqueue(5); */
/*   for (int i = 0; i < 100; i++) */
/*     enqueue(i); */


/*   int value; */
/*   while (dequeue(&value) == 0) { */
/*     printf("value: %d\n", value); */
/*   } */

/*   return 0; */
/* } */

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
  pthread_mutex_lock(&global->tailMutex);

  struct list *new = malloc(sizeof(struct list));
  new->val = val;
  new->next = NULL;

  global->tail->next = new;
  global->tail = new;
  
  pthread_mutex_unlock(&global->tailMutex);
  return;
}

int dequeue(int *extractedValue)
{
  /* queue is logically empty */
  pthread_mutex_lock(&global->headMutex);
  if (global->head->next == NULL) {
    return 1;
  }

  struct list *old = global->head;
  
  global->head = old->next;
  *extractedValue = global->head->val;
  free(old);
  
  pthread_mutex_unlock(&global->headMutex);
  
  return 0;
}

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
  pthread_mutex_t mutex;
  struct list    *head;
  struct list    *tail;
};

int main()
{
  printf("hi\n");
  initialize_queue();
  for (int i = 0; i < 10; i++)
    enqueue(i);

  int value;
  for (
  return 0;
}

void initialize_queue(void)
{
  global = malloc(sizeof(struct queue));
  pthread_mutex_init(&global->mutex, NULL);

  struct list *dummy = malloc(sizeof(struct list));
  dummy->val = 42;
  dummy->next = NULL;

  global->head = dummy;
  global->tail = dummy;

  return;
}

void enqueue(int val)
{
  pthread_mutex_lock(&global->mutex);

  struct list *new = malloc(sizeof(struct list));
  new->val = val;
  new->next = NULL;

  global->tail = new;
  
  pthread_mutex_unlock(&global->mutex);
  return;
}

int dequeue(int *extractedValue)
{
  /* queue is logically empty */
  if (global->head == NULL) {
    return 1;
  }

  pthread_mutex_lock(&global->mutex);

  struct list *head = global->head;
  
  *extractedValue = head->next->val;
  global->head = head->next;
  free(head);
  
  pthread_mutex_unlock(&global->mutex);
  
  return 0;
}

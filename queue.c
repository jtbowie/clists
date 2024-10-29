#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define ITEM_SZ 128

struct list {
  struct list *next;
  char buf[ITEM_SZ];
};

typedef struct list List;

// TODO: Move to header
int add_node(const char *);
char *pop_node();

List *head = NULL;

int add_node(const char *str) {
  List *ptr;

  List *new = malloc(sizeof(List));
  if (new < 0) {
    return (-1);
  }

  memset(new, 0, sizeof(List));

  strncpy(new->buf, str, ITEM_SZ - 1);

  if (!head) {
    head = new;
    return (0);
  }

  ptr = head;

  while (ptr) {
    if (!ptr->next) {
      ptr->next = new;
      break;
    }

    ptr = ptr->next;
  }

  return (0);
}

char *pop_node() {
  List *ptr;
  char *elem;

  // If tail is NULL, there are no items in the list.

  if (!head) {
    return (NULL);
  }

  ptr = head;
  // Copy the node's contents to the return buffer.
  elem = (char *)malloc(strlen(ptr->buf) + 1);
  memset(elem, 0, strlen(ptr->buf) + 1);
  strncpy(elem, ptr->buf, strlen(ptr->buf));

  head = ptr->next;
  // Cleanup the popped node
  free(ptr);
  // Return the element we just popped off the queue
  return (elem);
}

int main(int argc, char **argv) {
  char *populate[9] = {"We",    "are", "going", "to",   "add",
                       "these", "to",  "a",     "queue"};
  printf("List size = %lu\n", sizeof(List));

  char *ptr;
  int i = 0;

  for (; i < 9; i++) {
    add_node(populate[i]);
  }

  while ((ptr = pop_node()) != NULL) {
    printf("%s ", ptr);
  }
  printf("\n");
  exit(0);
}

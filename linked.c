#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define ITEM_SZ 128

struct list {
  struct list *next;
  struct list *prev;
  char buf[ITEM_SZ];
};

typedef struct list List;

List *head = NULL;
List *tail = NULL;

List *drop_node(List *node) {
  List *ptr;

  if (!node) {
    return (NULL);
  } else {
    if (node->prev) {
      node->prev->next = node->next;
    }

    if (node->next) {
      node->next->prev = node->prev;
    } else {
      tail = node->prev;
    }

    ptr = node->next;

    free(node);
    // node = NULL;
    return (ptr);
  }
  // Never reached.
  return (NULL);
}

List *new_node(char *str) {
  List *ptr;

  List *new = malloc(sizeof(List));
  memset(new, 0, sizeof(List));

  strncpy(new->buf, str, ITEM_SZ - 1);

  if (!head) {
    new->next = new->prev = NULL;
    head = tail = new;
    return (new);
  }

  ptr = tail;

  ptr->next = new;
  new->prev = ptr;
  new->next = NULL;

  return (new);
}

int main(int argc, char **argv) {
  char *populate[10] = {"\nWe",  "are", "going", "to",     "add",
                        "these", "to",  "a",     "linked", "list"};
  printf("List size = %lu\n", sizeof(List));

  head = tail = new_node("Fuck");
  tail = new_node("the");
  tail = new_node("Yankees!");

  List *ptr;

  for (ptr = head; ptr != NULL; ptr = ptr->next) {
    if (ptr->next != NULL) {
      printf("%s ", ptr->buf);
    } else {
      printf("%s!\n", ptr->buf);
    }
  }

  ptr = tail;

  printf("0x%lx\n", (unsigned long)ptr->prev);

  int i;

  for (i = 0; i < 10; i++) {
    tail = new_node(populate[i]);
  }

  while (ptr != head) {
    ptr = ptr->prev;
  }

  ptr = head;
  while (ptr != NULL) {
    if (ptr->next != NULL) {
      printf("[%s] ", ptr->buf);
      head = ptr->next;
      ptr = drop_node(ptr);
    } else {
      printf("[%s]!\n", ptr->buf);
      ptr = drop_node(ptr);
    }
  }

  exit(0);
}

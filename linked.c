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

// Remove the refuse
List *drop_node(List *node) {
  List *ptr;

  if (!node) {
    // Our work here is done
    return (NULL);
  } else {

    // If we're not the head of the list,
    // link previous element to next

    if (node->prev) {
      node->prev->next = node->next;
    } else

      // If we're a middle element, backlink to previous node.
      // Otherwise, set tail to previous node;

      if (node->next) {
        node->next->prev = node->prev;
      } else {
        tail = node->prev;
      }

    ptr = node->next ? node->next : node->prev;

    free(node);
    // node = NULL;
    return (ptr);
  }
  // Never reached.
  return (NULL);
}

// Genesis!

List *new_node(char *str) {
  List *ptr;

  // List::new()

  List *new = malloc(sizeof(List));
  memset(new, 0, sizeof(List));
  strncpy(new->buf, str, ITEM_SZ - 1);

  // `(' we are born!
  if (!head) {
    new->next = new->prev = NULL;
    head = tail = new;
    return (new);
  }

  // This is the ennnnnnd, beautiful friend.
  ptr = tail;

  // List::add()

  ptr->next = new;
  new->prev = ptr;
  new->next = NULL;

  return (new);
}

int main(int argc, char **argv) {
  char *populate[10] = {"We",    "are", "going", "to",     "add",
                        "these", "to",  "a",     "linked", "list"};
  printf("List size = %lu\n", sizeof(List));

  List *ptr;

  int i;

  head = tail = new_node(populate[0]);
  ptr = head;

  for (i = 1; i < 10; i++) {
    tail = new_node(populate[i]);
  }

  while (ptr != head) {
    ptr = ptr->prev;
  }

  ptr = head;
  while (ptr != NULL) {
    printf("[%s]%c", ptr->buf, ptr->next ? ' ' : '\n');
    head = ptr->next;
    ptr = drop_node(ptr);
  }

  exit(0);
}

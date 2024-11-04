#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define false 0
#define true 1

struct tree {
  struct tree *left;
  struct tree *right;
  struct tree *parent;
  u_int32_t value;
};

int insert_node(struct tree *);
int new_node(u_int32_t);
struct tree *tree_min(struct tree *);
struct tree *right_node(struct tree *);
struct tree *left_node(struct tree *);
struct tree *root;

int new_node(u_int32_t value) {
  struct tree *node = (struct tree *)malloc(sizeof(struct tree));
  int ret;

  memset(node, 0, sizeof(struct tree));
  node->value = value;
  ret = insert_node(node);
  return (ret);
}

int insert_node(struct tree *node) {
  struct tree *ptr;
  struct tree *parent;
				_Bool left = true;

  if (root) {
    ptr = root;
    while (ptr) {
      parent = ptr;
      if (node->value > ptr->value) {
        ptr = right_node(ptr);
				left = false;
      } else if (node->value < ptr->value) {
        ptr = left_node(ptr);
				left = true;
      } else {
        return (-1);
      }
			ptr = parent;
				if ( node->value > ptr-> value ) {
								ptr->right = node;
				} 
    }
  } else {
    root = node;
  }
  return (0);
}

struct tree *tree_min(struct tree *node) {
  if (node->left) {
    tree_min(node->left);
  } else {
    return (node);
  }
}

struct tree *right_node(struct tree *node) { return (node->right); }

struct tree *left_node(struct tree *node) { return (node->left); }

int main() {
  printf("Hello World\n");
  return 0;
}

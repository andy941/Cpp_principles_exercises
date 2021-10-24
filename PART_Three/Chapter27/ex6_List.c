#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 1000

struct Link { /* link for doubly-linked list */
  int pre;
  int suc;
};

struct List {
  int first;
  int last;
  struct Link container[MAX_LIST_SIZE];
};

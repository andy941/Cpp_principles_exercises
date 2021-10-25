#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 1000

// in this implementation there is an array of links on the stack (pool)
// the link is "free" if pre and suc are == -1.
// The exercise says to not change the interface to the list but I don't
// see how that is possible. if you ask for a link form the pool it will not
// contain any information about where it is on the array. I changed the
// interface a bit to simplify the operations and meke them hopefully more
// efficient.

struct Link { /* link for doubly-linked list */
  int pre;
  int suc;
  char *p; // has to be known at compile time to allocate enough space for pool
           // (I think)
};

struct List {
  int first;
  int last;
  struct Link *pool;
};

void init(struct List *lst);    /* initialize lst to empty */
struct List *create();          /* make a new empty list on free store */
void clear(struct List *lst);   /* free all elements of lst */
void destroy(struct List *lst); /* free all elements of lst, then free lst */

int push_back(struct List *lst, char *s); /* add p at end of lst */
/* insert q before p in lst: */
int insert(struct List *lst, char *s, int n);
struct Link *erase(struct List *lst, int n); /* remove p from lst */

// Helper function to get Links from the pool
int get_link(struct List *lst) {
  for (int i = 0; i < MAX_LIST_SIZE; i++) {
    if (lst->pool[i].pre == -1 && lst->pool[i].suc == -1 && lst->pool[i].p == 0)
      return i;
  }
  return -1; // pool is full
};

void init(struct List *lst) /* initialize *lst to the empty list */
{
  assert(lst);
  lst->first = lst->last = -1;
  lst->pool = (struct Link *)malloc(sizeof(struct Link) * MAX_LIST_SIZE);
  for (int i = 0; i < MAX_LIST_SIZE; i++) { // initialize pool elements
    lst->pool[i].pre = -1;
    lst->pool[i].suc = -1;
    lst->pool[i].p = 0;
  }
}

struct List *create() /* make a new empty list */
{
  struct List *lst = (struct List *)malloc(sizeof(struct List));
  init(lst); // like constructor ...
  return lst;
}

void clear(struct List *lst) /* free all elements of lst */
{
  assert(lst);
  {
    int curr = lst->first;
    free(lst->pool);
    lst->first = lst->last = -1;
  }
}

void destroy(struct List *lst) /* free all elements of lst; then free lst */
{
  assert(lst);
  clear(lst);
  free(lst);
}

int push_back(struct List *lst, char *c) /* add p at end of lst */
{
  assert(lst);
  int l = get_link(lst);
  if (l == -1)
    return -1;
  lst->pool[l].p = c;

  {
    int last = lst->last;
    if (last != -1) {
      lst->pool[last].suc = l;
      lst->pool[l].pre = last;
    } else {
      lst->first = l;
      lst->pool[l].pre = -1;
    }
    lst->last = l;
    lst->pool[l].suc = -1;
  }
  return 1;
}

struct Link *erase(struct List *lst, int nn)
/*
          remove p from lst;
         return a pointer to the link after p
*/
{
  assert(lst);
  if (nn < 0)
    return 0;
  if (lst->first == lst->last)
    return 0;

  struct Link *p = &lst->pool[lst->first];

  for (int i = 0; i < nn; i++) {
    p = &lst->pool[p->suc];
  }

  p->p = 0;

  if (p->pre == -1) {
    if (p->suc != -1) {
      lst->first = p->suc;
      lst->pool[p->suc].pre = -1;
      return &(lst->pool[p->suc]);
    } else {
      lst->first = lst->last = -1;
      return 0;
    }
  } else if (p->suc == -1) {
    if (p->pre != -1) {
      lst->last = p->pre;
      lst->pool[p->suc].pre = -1;
    } else {
      lst->first = lst->last = -1;
      return 0;
    }
  }
  // else ...
  lst->pool[p->suc].pre = p->pre;
  lst->pool[p->pre].suc = p->suc;
  return &(lst->pool[p->suc]);
}

int insert(struct List *lst, char *c, int nn) {
  if (c == 0 || nn < 0)
    return -1;

  assert(lst);
  int l = get_link(lst);
  if (l == -1)
    return -1;

  struct Link *p = &lst->pool[lst->first];

  for (int i = 0; i < nn; i++) {
    p = &lst->pool[p->suc];
  }

  printf("%s\n", p->p);
  lst->pool[l].p = c;

  {
    int first = lst->first;
    if (p->pre == -1) {
      lst->pool[first].pre = l;
      lst->pool[l].suc = first;
      lst->first = l;
      lst->pool[l].pre = -1;
    } else {
      lst->pool[l].pre = p->pre;
      lst->pool[l].suc = lst->pool[p->pre].suc;
      lst->pool[p->pre].suc = l;
      p->pre = l;
    };
    return l;
  }
};

// Helper print function ------------------------------------------------------
void print(struct List *names) {
  int count = 0;
  struct Link *curr;
  curr = &(names->pool[names->first]); /* write out all names */
  while (1) {
    printf("element %d pre = %d suc = %d: %s\n", count, curr->pre, curr->suc,
           curr->p);
    if (curr->suc == -1)
      break;
    curr = &(names->pool[curr->suc]);
    count++;
  }
  printf("first: %d\tlast: %d\n", names->first, names->last);
}

int main() {
  int count = 0;
  struct List names; /* make a list */
  struct Link *curr;
  init(&names);
  print(&names);
  printf("---------------------------------------\n");

  /* make a few Names and add them to the list: */
  push_back(&names, "Norah");
  print(&names);
  printf("---------------------------------------\n");
  push_back(&names, "Annemarie");
  print(&names);
  printf("---------------------------------------\n");
  push_back(&names, "Kris");
  print(&names);
  printf("Insert at 1 ---------------------------\n");
  insert(&names, "Inserted 1", 1);
  print(&names);
  //* remove the second name (with index 1): */
  printf("Erase 1 -------------------------------\n");
  erase(&names, 1);
  print(&names);
  printf("---------------------------------------\n");
}

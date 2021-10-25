#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 1000

// in this implementation there is an array of links on the stack (pool)
// the link is "free" if pre and suc are == -1.

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

void push_back(struct List *lst, struct Link *p); /* add p at end of lst */
void push_front(struct List *, struct Link *p);   /* add p at front of lst */
/* insert q before p in lst: */
void insert(struct List *lst, struct Link *p, struct Link *q);
struct Link *erase(struct List *lst, struct Link *p); /* remove p from lst */

// Helper function to get Links from the pool
struct Link *get_link(struct List *lst) {
  for (int i = 0; i < MAX_LIST_SIZE; i++) {
    if (lst->pool[i].pre == -1 && lst->pool[i].suc == -1)
      return &(lst->pool[i]);
  }
  return 0;
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
    // while (curr) {
    //   int next = lst->pool[curr].suc;
    //   free(&(lst->pool[curr].p));
    //   curr = next;
    // }
    lst->first = lst->last = 0;
  }
}

void destroy(struct List *lst) /* free all elements of lst; then free lst */
{
  assert(lst);
  clear(lst);
  free(lst);
}

struct Name {
  struct Link lnk; /* the Link required by List operations */
  char *p;         /* the name string */
};

struct Name *make_name(char *n) {
  struct Name *p = (struct Name *)malloc(sizeof(struct Name));
  p->p = n;
  return p;
}

void push_back(struct List *lst, struct Link *p) /* add p at end of lst */
{
  assert(lst);
  {
    int last = lst->last;
    if (last) {
      last->suc = p;
      p->pre = last;
    } else {
      lst->first = p;
      p->pre = 0;
    }
    lst->last = p;
    p->suc = 0;
  }
}

struct Link *erase(struct List *lst, struct Link *p)
/*
          remove p from lst;
         return a pointer to the link after p
*/
{
  assert(lst);
  if (p == 0)
    return 0; /* OK to erase(0) */

  if (p == lst->first) {
    if (p->suc) {
      lst->first = p->suc;
      p->suc->pre = 0;
      return p->suc;
    } else {
      lst->first = lst->last = 0;
      return 0;
    }
  } else if (p == lst->last) {
    if (p->pre) {
      lst->last = p->pre;
      p->pre->suc = 0;
    } else {
      lst->first = lst->last = 0;
      return 0;
    }
  }
  // else ...
  p->suc->pre = p->pre;
  p->pre->suc = p->suc;
  return p->suc;
}

int main() {
  int count = 0;
  struct List names; /* make a list */
  struct Link *curr;
  init(&names);

  ///* make a few Names and add them to the list: */
  // push_back(&names, (struct Link *)make_name("Norah"));
  // push_back(&names, (struct Link *)make_name("Annemarie"));
  // push_back(&names, (struct Link *)make_name("Kris"));
  // push_front(&names, (struct Link *)make_name("Three"));
  // push_front(&names, (struct Link *)make_name("Two"));
  // push_front(&names, (struct Link *)make_name("One"));
  // printf("first: %s\tlast: %s\n", ((struct Name *)names.first)->p,
  //        ((struct Name *)names.last)->p);
  // insert(&names, names.first, (struct Link *)make_name("NEW_FIRST"));
  // printf("first: %s\tlast: %s\n", ((struct Name *)names.first)->p,
  //        ((struct Name *)names.last)->p);
  // insert(&names, names.last, (struct Link *)make_name("SECOND_TO_LAST"));
  // printf("first: %s\tlast: %s\n", ((struct Name *)names.first)->p,
  //        ((struct Name *)names.last)->p);

  /////* remove the second name (with index 1): */
  // erase(&names, advance(names.first, 2));

  // curr = names.first; /* write out all names */
  // for (; curr != 0; curr = curr->suc) {
  //   count++;
  //   printf("element %d: %s\n", count, ((struct Name *)curr)->p);
  // }
}

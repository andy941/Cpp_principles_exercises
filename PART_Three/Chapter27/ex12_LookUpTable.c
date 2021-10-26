
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLE_ENTRIES 10000

/*
 * This could be done with an hash table but it's a bit over my head at the
 * moment
 */

struct pair {
  int value;
  char *key;
};

struct table {
  int sz;
  struct pair pairs[10000];
};

void print(struct table *tb) {
  for (int i = 0; i < MAX_TABLE_ENTRIES; i++) {
    if (tb->pairs[i].key) {
      printf("%d:\tkey=%s\tvalue=%d\n", i, tb->pairs[i].key,
             tb->pairs[i].value);
    }
  }
}

void init(struct table *tb) {
  tb->sz = 0;
  for (int i = 0; i < MAX_TABLE_ENTRIES; i++) {
    tb->pairs[i].key = 0; // initialize to empty
  }
}

struct pair *get_pair(struct table *tb) { // get first empty slot
  for (int i = 0; i < MAX_TABLE_ENTRIES; i++) {
    if (!tb->pairs[i].key) {
      return &(tb->pairs[i]);
    }
  }
  return 0;
}

struct pair *insert(struct table *tb, const char *key, int value) {
  if (tb->sz >= MAX_TABLE_ENTRIES)
    return 0;
  struct pair *kv = get_pair(tb);

  kv->key = (char *)malloc(sizeof(char) * strlen(key));
  strcpy(kv->key, key);
  kv->value = value;
  tb->sz++;
  return kv;
}

struct pair *find(struct table *tb, const char *key) {
  for (int i = 0; i < MAX_TABLE_ENTRIES; i++) {
    if (strcmp(tb->pairs[i].key, key) == 0)
      return &(tb->pairs[i]);
  }
  return 0;
}

int erase(struct table *tb, const char *key) {
  struct pair *p = find(tb, key);
  if (!p)
    return 0;
  free(p->key);
  p->key = 0;
  return 1;
}

int main() {
  struct table tb;
  init(&tb);
  insert(&tb, "first", 1);
  insert(&tb, "second", 2);
  insert(&tb, "third", 3);
  print(&tb);
  printf("--------------------------\n");
  int n = erase(&tb, "second");
  print(&tb);
  printf("--------------------------\n");
  insert(&tb, "second", 2);
  print(&tb);
}

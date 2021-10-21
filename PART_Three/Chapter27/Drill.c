#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void myprint(char *p, int x) { printf("p is \"%s\" and x is %d\n", p, x); }

int main() {
  printf("Hello world\n");
  char *h = "Hello";
  char *w = "world";

  int sz = strlen(h) + strlen(w) + 2;
  char *s = (char *)malloc(sz);
  strcpy(s, h);
  s[strlen(h)] = ' ';
  strcpy(s + strlen(h) + 1, w);
  s[sz - 1] = 0;
  printf("%s\n", s);

  myprint("foo", 7);
}

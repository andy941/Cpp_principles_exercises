#include <stdio.h>
#include <stdlib.h>

void myprint(char *p, int x) { printf("p is \"%s\" and x is %d\n", p, x); }

size_t Strlen(char *s) {
  char *tmp = s;
  int n = 0;
  while (*tmp++) {
    n++;
  }
  return n;
}

int Strcmp(char *a, char *b) {

  while (*a == *b) {
    if (!*a && !*b) // Perfect match
      return 0;
    a++;
    b++;
  };

  if (*a < *b)
    return -1;
  return 1;
}

char *Strcpy(char *p, const char *q) {

  while ((*p++ = *q++))
    ;
  return p;
}

int main() {
  char *h = "hello";
  char *w = "world";
  int len = Strlen(h);
  printf("The length of %s is %d.\n", h, len);
  printf("The lexical order of %s and %s is %d.\n", h, w, Strcmp(h, w));
  printf("The lexical order of %s and %s is %d.\n", w, h, Strcmp(w, h));
  printf("The lexical order of %s and %s is %d.\n", h, h, Strcmp(h, h));

  int sz = Strlen(h) + Strlen(w) + 2;
  char *s = (char *)malloc(sz);
  Strcpy(s, h);
  s[Strlen(h)] = ' ';
  Strcpy(s + Strlen(h) + 1, w);
  s[sz - 1] = 0;
  printf("%s\n", s);

  myprint("foo", 7);
}

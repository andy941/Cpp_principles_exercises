#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(char **w, int n) {
  for (int i = 0; i <= n; i++) {
    printf("%d:\t%s\n", i, w[i]);
  }
  return;
}

char *read_word(int bmax) {
  char str[bmax];
  int n = 0;
  char ch;

  while ((ch = getchar()) && n < bmax - 1) {
    if (ch == ' ' || ch == '\n') {
      str[n] = 0;
      break;
    }
    str[n] = ch;
    ++n;
  }

  char *word = (char *)malloc(n + 1);
  word[n] = 0;
  strcpy(word, str);
  return word;
}

int comp(const void *e1, const void *e2) {
  return strcmp(*(const char **)e1, *(const char **)e2);
}

int main() {
  char *words[10000];
  int buffer_max = 100;
  int w = 0;
  char ch;

  while (w < 10000) {
    while ((ch = getchar()) == ' ')
      ;
    ungetc(ch, stdin);
    words[w] = read_word(buffer_max);
    qsort(words, w + 1, sizeof(char *), comp);
    system("clear");
    print(words, w);
    w++;
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(char **w, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d:\t%s\n", i, w[i]);
  }
  return;
}

char *read_word(int bmax) {
  char str[bmax];
  int ch, n = 0;

  while ((ch = getchar()) != EOF && n < bmax) {
    if (ch == ' ' || ch == '\n') {
      str[n + 1] = 0;
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

int main() {
  char *words[10000];
  int buffer_max = 100;
  int w = 0;
  char ch;

  while (w++ < 10000) {
    while ((ch = getchar()) == ' ')
      ;
    words[w] = read_word(buffer_max);
    print(words, w);
  }
}

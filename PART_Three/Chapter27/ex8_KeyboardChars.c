
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  int start = 33;
  int end = 126;
  char letters[end - start];

  for (int i = start; i < end; i++) {
    letters[i - start] = i;
    printf("%d:\t%c\n", i, i);
  }
}

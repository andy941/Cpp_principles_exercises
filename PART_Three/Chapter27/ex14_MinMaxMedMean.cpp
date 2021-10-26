
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Print(int *arr, int sz) {
  for (size_t i = 0; i < sz; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int Min(int *arr, int sz) {
  int res = arr[0];
  for (size_t i = 1; i < sz; i++) {
    if (arr[i] < res)
      res = arr[i];
  }
  return res;
}

int Max(int *arr, int sz) {
  int res = arr[0];
  for (size_t i = 1; i < sz; i++) {
    if (arr[i] > res)
      res = arr[i];
  }
  return res;
}

double Mean(int *arr, int sz) {
  int tot = 0;
  for (size_t i = 0; i < sz; i++) {
    tot += arr[i];
  }
  return (double)tot / sz;
}
int cmp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

double Median(int *array, int sz) {
  if (sz == 0)
    return 0;

  int *arr = (int *)malloc(sizeof(int) * sz);
  memccpy(arr, array, sz, sizeof(int) * sz);
  qsort(arr, sz, sizeof(int), cmp);

  if (sz % 2 == 0) {
    double res = arr[(int)(sz / 2 - 1)] +
                 (double)(arr[(int)(sz / 2)] - arr[(int)(sz / 2 - 1)]) / 2;
    free(arr);
    return res;
  }
  double res = arr[(int)floor(sz / 2)];
  free(arr);
  return res;
}

struct result {
  int min;
  int max;
  double mean;
  double median;
};

void get_stats(int *arr, int sz, struct result *res) {
  res->min = Min(arr, sz);
  res->max = Max(arr, sz);
  res->mean = Mean(arr, sz);
  res->median = Median(arr, sz);
}

int main() {
  int sz = 4;
  int arr[] = {10, 0, 5, 2};
  Print(arr, sz);
  result res;
  get_stats(arr, sz, &res);

  printf("MIN = %d\n", res.min);
  printf("MAX = %d\n", res.max);
  printf("MEAN = %f\n", res.mean);
  printf("MEDIAN = %f\n", res.median);
}

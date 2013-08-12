#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*******************************************************************************
 * heap
 ******************************************************************************/

int swap (int *x, int *y) {
  *x = *x ^ *y;
  *y = *x ^ *y;
  *x = *x ^ *y;
  return 0;
}

size_t arr_parent (size_t ind) {
  return (ind - 1) / 2; // floor is taken care of by integer truncation
}

int maintain_heap (int *head, size_t ind) {
  size_t par = arr_parent(ind);
  while (ind != 0 && head[ind] < head[par]) {
    swap(head + ind, head + par);
    ind = par;
    par = arr_parent(ind);
  }
  return 0;
}

size_t heap_arr_insert (int *head, int x, size_t heap_size, size_t arr_size) {
  if (heap_size == arr_size) {
    arr_size *= 2;
    realloc(head, sizeof(int) * arr_size);
  }
  size_t adj_heap_size = heap_size++;
  head[adj_heap_size] = x;
  maintain_heap(head, adj_heap_size);
  return arr_size;
}

/*******************************************************************************
 * test helper functions
 ******************************************************************************/

void print_heap_arr (int *head, size_t arr_size) {
  size_t lev_len = 1;
  size_t c = 0;
  for (size_t c = 0, lev_len = 1; c < arr_size; c += lev_len, lev_len *= 2) {
    for (size_t i = 0; i < lev_len; ++i) {
      printf("%d ", head[c + i]);
    }
    printf("\n");
  }
}

bool arrs_equal (int *h1, int *h2, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    if (h1[i] != h2[i])
      return false;
  }
  return true;
}

/*******************************************************************************
 * test helper functions
 ******************************************************************************/


bool test_heap_arr_1 () {
  size_t arr_len = 10;
  int *arr = malloc(arr_len * sizeof(int));
  heap_arr_insert(arr, 7, 0, 10);
  heap_arr_insert(arr, 7, 1, 10);
  heap_arr_insert(arr, 2, 2, 10);
  int expected[] = {2, 7, 7};
  bool ret = arrs_equal(arr, expected, 3);
  free(arr);
  if (!ret) printf("failure in test_heap_arr1");
  return ret;
}



int main () {
  int i = 0;
  i += test_heap_arr_1();
  printf("%d of %d tests passed.\n", i, 1);
  return 0;
}

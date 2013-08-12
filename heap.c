#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

/*******************************************************************************
 * heap
 ******************************************************************************/

int swap (int *x, int *y) {
  *x = *x ^ *y;
  *y = *x ^ *y;
  *x = *x ^ *y;
  return 0;
}

void fill_arr (int *head, size_t m, size_t n) {
  for (size_t i = m; i < n; ++i)
    head[i] = INT_MAX;
}

int *init_heap (size_t len) {
  int *ret = malloc(len * sizeof(int));
  fill_arr(ret, 0, len);
  return ret;
}

size_t arr_parent (size_t ind) {
  return (ind - 1) / 2; // floor is taken care of by integer truncation
}

size_t arr_youngest_child (int *head, size_t ind) {
  size_t l = 2 * ind + 1;
  size_t r = 2 * ind + 2;
  if (head[l] != INT_MAX && head[r] !=INT_MAX)
    return head[l] < head[r] ? l : r;
  else if (head[l] != INT_MAX)
    return r;
  else
    return l;
}

int bubble_up (int *head, size_t ind) {
  size_t par = arr_parent(ind);
  while (ind != 0 && head[ind] < head[par]) {
    swap(head + ind, head + par);
    ind = par;
    par = arr_parent(ind);
  }
  return 0;
}

int bubble_down (int *head, size_t ind) {
  size_t child = arr_youngest_child(head, ind);
  while (head[child] != INT_MAX && head[child] < head[ind]) {
    swap(head + child, head + ind);
    ind = child;
    child = arr_youngest_child(head, ind);
  }
  return 0;
}

void heap_arr_insert (int *head, int x, size_t *heap_size, size_t *arr_size) {
  if (*heap_size == *arr_size) {
    *arr_size *= 2;
    realloc(head, sizeof(int) * (*arr_size));
    fill_arr(head, *heap_size, *arr_size);
  }
  size_t adj_heap_size = (*heap_size)++;
  head[adj_heap_size] = x;
  bubble_up(head, adj_heap_size);
  return;
}

int pop_min (int *head, size_t *heap_size) {
  int ret = head[0];
  head[0] = head[*heap_size];
  head[*heap_size] = INT_MAX;
  (*heap_size)--;
  bubble_down(head, 0);
  return ret;
}

/*******************************************************************************
 * test helper functions
 ******************************************************************************/

void print_heap_arr (int *head, size_t arr_size) {
  size_t lev_len = 1;
  size_t c = 0;
  for (size_t c = 0, lev_len = 1; c < arr_size; c += lev_len, lev_len *= 2) {
    for (size_t i = 0; i < lev_len; ++i) {
      if (c + i < arr_size)
        head[c + i] == INT_MAX ? printf("- ") : printf("%d ", head[c + i]);
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
 * tests
 ******************************************************************************/

bool test_heap_arr_insert () {
  size_t arr_len = 10;
  size_t heap_size = 0;
  int *arr = init_heap(arr_len);
  heap_arr_insert(arr, 7, &heap_size, &arr_len);
  heap_arr_insert(arr, 7, &heap_size, &arr_len);
  heap_arr_insert(arr, 2, &heap_size, &arr_len);
  int expected[] = {2, 7, 7};
  bool ret = arrs_equal(arr, expected, heap_size);
  free(arr);
  if (!ret) printf("failure in test_heap_arr1");
  return ret;
}

int test_heap_arr_pop_min () {
  size_t arr_len = 10;
  size_t heap_size = 0;
  int *arr = init_heap(arr_len);
  heap_arr_insert(arr, 7, &heap_size, &arr_len);
  heap_arr_insert(arr, 7, &heap_size, &arr_len);
  heap_arr_insert(arr, 2, &heap_size, &arr_len);
  print_heap_arr(arr, arr_len);
  int popped = pop_min(arr, &heap_size);
  print_heap_arr(arr, arr_len);
  printf("popped: %d\n", popped);
  int expected[] = {7, 7};
  int ret = 0;
  ret += arrs_equal(arr, expected, heap_size);
  free(arr);
  ret += popped == 2 ? 1 : 0;
  return ret;
}

/*******************************************************************************
 * main
 ******************************************************************************/

int main () {
  int i = 0;
  i += test_heap_arr_insert();
  i += test_heap_arr_pop_min();
  printf("%d of %d tests passed.\n", i, 3);
  return 0;
}

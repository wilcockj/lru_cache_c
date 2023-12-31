#include "hashmap.h"
#include "lru.h"
#include <assert.h>
#include <stdio.h>
#include <sys/resource.h>
#include <time.h>
#define ASSERT(condition)                                                      \
  do {                                                                         \
    if (!(condition)) {                                                        \
      fprintf(stderr, "Assertion failed: (%s), file %s, line %d\n",            \
              #condition, __FILE__, __LINE__);                                 \
      abort();                                                                 \
    }                                                                          \
  } while (0)

/* Add some nice logging that can be toggled
 * Work on the lru part, now that hashmap is functional
 */

int fib(int n) {
  if (n < 2)
    return n;
  return fib(n - 1) + fib(n - 2);
}

unsigned long long lru_fib(lru *cache, int n) {

  // check cache
  void *cached_val = get_data(cache, n);
  if (cached_val != NULL) {
    return *(int *)cached_val;
  }
  if (n < 2)
    return n;
  unsigned long long *fib_res = malloc(sizeof(unsigned long long));
  *fib_res = lru_fib(cache, n - 1) + lru_fib(cache, n - 2);
  add_data(cache, n, (void *)fib_res);
  return *fib_res;
}

int main() {
  const rlim_t kStackSize = 1024 * 1024 * 1024; // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0) {
    if (rl.rlim_cur < kStackSize) {
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0) {
        fprintf(stderr, "setrlimit returned result = %d\n", result);
      }
    }
  }
  int fib_num = 1000000;
  printf("Getting %dth fibonacci number\n", fib_num);
  lru *cache = create_lru(64);
  clock_t begin = clock();
  unsigned long long lru_result = 0;
  for (int i = 0; i < fib_num; i++) {
    lru_result = lru_fib(cache, i);
    //printf("%llu", lru_result);
  }
  clock_t end = clock();
  double lru_time_spent = (double)(end - begin);
  printf("\nlruified took %0.fμs\n", lru_time_spent);
  printf("%dth fib num = %llu\n", fib_num, lru_result);

  /*
  begin = clock();
  int reg_result = fib(fib_num);
  end = clock();
  double time_spent = (double)(end-begin);
  printf("non cached took %0.fμs\n",time_spent);

  printf("lru is %f times faster than non cached\n",time_spent/lru_time_spent);
  */

  return 0;
}

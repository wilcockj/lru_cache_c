#include "hashmap.h"
#include "lru.h"
#include <assert.h>
#include <stdio.h>
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

int lru_fib(lru * cache, int n){
      
    // check cache 
    void * cached_val = get_data(cache,n);
    if(cached_val != NULL){
        return *(int *)cached_val;
    }
    if(n < 2)
      return n;
    int *fib_res = malloc(sizeof(int));
    *fib_res = lru_fib(cache,n-1) + lru_fib(cache,n-2); 
    add_data(cache,n,(void *)fib_res);
    return *fib_res;
}

int main() {

  lru *cache = create_lru(100);
  clock_t begin = clock();
  int result = lru_fib(cache,60);
  clock_t end = clock();
  double time_spent = (double)(end-begin);
  printf("lruified took %f\n",time_spent);
  
  begin = clock();
  int reg_result = fib(60);
  end = clock();
  time_spent = (double)(end-begin);
  printf("non cached took %f\n",time_spent);

  printf("entries in cache is %d\n",cache->node_map->entry_count);
  printf("%d %d\n", result,reg_result);
  char *test = "asdasdasdasdasdas";
  //  create_lru(128, 2, 3, 34123123, 123, 123, 123, 12, 312, 312, 312, 3, 13,
  //  1, 2,
  //            3, 4, 5);
  return 0;
}

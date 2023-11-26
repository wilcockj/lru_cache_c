#include "hashmap.h"
#include "lru.h"
#include <assert.h>
#include <stdio.h>
#define ASSERT(condition)                                                      \
  do {                                                                         \
    if (!(condition)) {                                                        \
      fprintf(stderr, "Assertion failed: (%s), file %s, line %d\n",            \
              #condition, __FILE__, __LINE__);                                 \
      abort();                                                                 \
    }                                                                          \
  } while (0)

int fib(int n) {
  if (n < 2)
    return n;
  return fib(n - 1) + fib(n - 2);
}

int main() {

  char *test = "asdasdasdasdasdas";
  //  create_lru(128, 2, 3, 34123123, 123, 123, 123, 12, 312, 312, 312, 3, 13,
  //  1, 2,
  //            3, 4, 5);
  ht *table = create_table(100);
  int yes = 1000;
  int yes1 = 132;
  int yes2 = 1000;
  int yes3 = 1000;
  int yes4 = 1002;
  add_entry(table, (void *)&yes, 1);
  add_entry(table, (void *)&yes1, 100);
  add_entry(table, (void *)&yes2, 20);
  add_entry(table, (void *)&yes3, 50);
  add_entry(table, (void *)&yes4, 60);

  for (int i = 100; i < 200; i++) {
    //  printf("putting data in at hash %d\n", i);
    int err = add_entry(table, (void *)&yes3, i);
    if (err != 0) {
      printf("Some error allocating for hash_key %d\n", i);
    }
  }
  printf("after populating the hash map capacity is %d and entry_count = %d\n",
         table->capacity, table->entry_count);

  hte *entry = get_entry(table, 100);
  assert(*((int *)entry->data) == 132);

  yes4 += 1;
  entry = get_entry(table, 60);
  ASSERT(*((int *)entry->data) == 1003);

  printf("got corrrect entry key = %lu, data = %d\n", entry->hash_key,
         *((int *)entry->data));
  for (int i = 0; i < 12000; i++) {
    hte *entry = get_entry(table, i);
    if (entry != NULL) {
      printf("entry at hash %d = %d\n", entry->hash_key, *((int *)entry->data));
      printf("took %d accesses\n", entry->accesses_to_find);
    }
  }
  return 0;
}

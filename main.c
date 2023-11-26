#include "hashmap.h"
#include "lru.h"
#include <assert.h>
#include <stdio.h>
int fib(int n) {
  if (n < 2)
    return n;
  return fib(n - 1) + fib(n - 2);
}

int main() {

  char *test = "asdasdasdasdasdas";
  create_lru(128, 2, 3, 34123123, 123, 123, 123, 12, 312, 312, 312, 3, 13, 1, 2,
             3, 4, 5);
  ht *table = create_table(100);
  int yes = 1000;
  int yes1 = 132;
  int yes2 = 1000;
  int yes3 = 1000;
  add_entry(table, (void *)&yes, 1);
  add_entry(table, (void *)&yes1, 100);
  add_entry(table, (void *)&yes2, 20);
  add_entry(table, (void *)&yes3, 50);
  for (int i = 10000; i < 10100; i++) {
    printf("putting data in at hash %d\n", i);
    add_entry(table, (void *)&yes3, i);
  }
  hte *entry = get_entry(table, 100);
  assert(*((int *)entry->data) == 132);
  printf("got corrrect entry key = %lu, data = %d\n", entry->hash_key,
         *((int *)entry->data));
  for (int i = 10000; i < 10100; i++) {
    get_entry(table, i);
  }
  return 0;
}

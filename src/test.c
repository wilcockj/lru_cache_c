#include "test.h"
#include "assert.h"
#include "hashmap.h"
#include <stdio.h>

int test_get() {
  ht *table = create_table(100);
  int num = 132;
  add_entry(table, (void *)&num, 100);

  hte *entry = get_entry(table, 100);
  ASSERT(*((int *)entry->data) == 132);
  printf("Passed get test\n");
  return 0;
}

int test_pointer_fresh() {
  ht *table = create_table(100);

  int will_inc = 1002;
  will_inc += 1;
  add_entry(table, (void *)&will_inc, 60);
  hte *entry = get_entry(table, 60);
  ASSERT(*((int *)entry->data) == 1003);
  ASSERT(table->capacity == 100);
  printf("Passed get data after increment test\n");
  return 0;
}

int main() {
  test_get();
  test_pointer_fresh();
  return EXIT_SUCCESS;
}

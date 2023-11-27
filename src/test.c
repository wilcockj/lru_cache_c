#include "test.h"
#include "assert.h"
#include "dll.h"
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

int test_capacity_expansion() {
  ht *table = create_table(10);
  int num = 100;
  for (int i = 0; i < 100; i++) {
    add_entry(table, (void *)&num, i);
  }
  ASSERT(table->capacity == 160);
  hte *entry = get_entry(table, 0);
  ASSERT(*((int *)entry->data) == 100);
  printf("Passed capacity expansion test\n");
  return 0;
}

int test_update_entry() {
  ht *table = create_table(10);
  int num = 100;
  add_entry(table, (void *)&num, 1);
  int alt_num = 400;
  add_entry(table, (void *)&alt_num, 1);
  hte *entry = get_entry(table, 1);
  ASSERT(*((int *)entry->data) == 400);
  printf("Passed update entry test\n");
  return 0;
}

int test_dll_creation() {
  dll list = create_dll();
  int x = 4;
  int y = 5;
  prepend_data(&list, (void *)&x);
  ASSERT(*((int *)list.head->data) == 4);
  ASSERT(*((int *)list.tail->data) == 4);

  // test where the tail is as well
  printf("Passed dll creation test\n");
  prepend_data(&list, (void *)&x);
  prepend_data(&list, (void *)&x);
  prepend_data(&list, (void *)&x);
  dll_node *y_node = prepend_data(&list, (void *)&y);
  prepend_data(&list, (void *)&x);
  ASSERT(list.length == 6);

  move_node_to_front(&list,y_node);
  ASSERT(list.length == 6);
  ASSERT(list.head->data == &y);

  // what about moving the last item to front,
  // or removing the last item. will tail be appropriately set
  return 0;
}

int main() {
  test_get();
  test_pointer_fresh();
  test_capacity_expansion();
  test_update_entry();
  test_dll_creation();
  return EXIT_SUCCESS;
}

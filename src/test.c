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
  free_table(table);
  return 0;
}

int test_remove_key() {
	ht *table = create_table(100);
	int num = 103;
	int num2 = 104;
	add_entry(table, (void *)&num,1);
	add_entry(table, (void *)&num,2);
	ASSERT(table->entry_count == 2);             
	remove_entry(table,2);
	ASSERT(table->entry_count == 1);             
	hte *entry = get_entry(table,2);
	ASSERT(entry == NULL);
	printf("Passed remove key test\n");
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
  free_table(table);
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
  free_table(table);
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
  free_table(table);
  return 0;
}

int test_dll_creation() {
  dll list = create_dll();
  int x = 4;
  int y = 5;
  int head_sentinel = 54;
  dll_node *tail_node = prepend_data(&list, (void *)&x);
  ASSERT(*((int *)list.head->data) == 4);
  ASSERT(list.length == 1);

  // test where the tail is as well
  prepend_data(&list, (void *)&x);
  prepend_data(&list, (void *)&x);
  prepend_data(&list, (void *)&x);
  dll_node *y_node = prepend_data(&list, (void *)&y);
  dll_node *head_node = prepend_data(&list, (void *)&head_sentinel);
  ASSERT(list.length == 6);

  // move tail to front and check that tail is updated along with head
  move_node_to_front(&list, y_node);
  ASSERT(list.length == 6);
  ASSERT(*(int *)(list.head->data) == y);
  ASSERT(list.head->data == &y);
  ASSERT(*(int *)(list.head->next->data) == head_sentinel);
  ASSERT(list.head = y_node);

  // move that new node to front
  move_node_to_front(&list, y_node);
  ASSERT(list.length == 6);
  ASSERT(list.head->data == &y);
  ASSERT(list.head->next == head_node);

  // remove that node, should change the head
  remove_node(&list, y_node);
  ASSERT(list.length == 5);
  ASSERT(list.head == head_node);

  // check that the tail is the first node still
  ASSERT(list.tail == tail_node);
  dll_node *tail_prev = list.tail->prev;
  move_node_to_front(&list, tail_node);
  ASSERT(list.head == tail_node);
  ASSERT(list.tail == tail_prev);
  ASSERT(list.length == 5);

  printf("Passed dll creation test\n");
  free_dll(&list);
  return 0;
}

int test_dll_prepend() {
  dll list = create_dll();
  int x = 4;
  int y = 5;
  int head_sentinel = 54;
  dll_node *tail_node = prepend_data(&list, (void *)&x);
  // test where the tail is as well
  prepend_data(&list, (void *)&x);
  prepend_data(&list, (void *)&x);
  prepend_data(&list, (void *)&x);
  dll_node *y_node = prepend_data(&list, (void *)&y);
  dll_node *head_node = prepend_data(&list, (void *)&head_sentinel);
  ASSERT(list.length == 6);
  printf("Passed dll prepend test\n");
  free_dll(&list);
  return 0;
}

int test_dll_move_to_front() {
  dll list = create_dll();

  int x = 4;
  int y = 5;
  int head_sentinel = 54;
  dll_node *tail_node = prepend_data(&list, (void *)&x);
  // test where the tail is as well
  prepend_data(&list, (void *)&x);
  prepend_data(&list, (void *)&x);
  prepend_data(&list, (void *)&x);
  dll_node *y_node = prepend_data(&list, (void *)&y);
  dll_node *head_node = prepend_data(&list, (void *)&head_sentinel);
  // move tail to front and check that tail is updated along with head
  move_node_to_front(&list, y_node);
  ASSERT(list.length == 6);
  ASSERT(*(int *)(list.head->data) == y);
  ASSERT(list.head->data == &y);
  ASSERT(*(int *)(list.head->next->data) == head_sentinel);
  ASSERT(list.head = y_node);

  // move that new node to front
  move_node_to_front(&list, y_node);
  ASSERT(list.length == 6);
  ASSERT(list.head->data == &y);
  ASSERT(list.head->next == head_node);

  // remove that node, should change the head
  remove_node(&list, y_node);
  ASSERT(list.length == 5);
  ASSERT(list.head == head_node);

  // check that the tail is the first node still
  ASSERT(list.tail == tail_node);
  dll_node *tail_prev = list.tail->prev;
  move_node_to_front(&list, tail_node);
  ASSERT(list.head == tail_node);
  ASSERT(list.tail == tail_prev);
  ASSERT(list.length == 5);

  printf("Passed move node to front of DLL\n");
  free_dll(&list);
  return 0;
}

int main() {
  test_get();
  test_remove_key();
  test_pointer_fresh();
  test_capacity_expansion();
  test_update_entry();
  test_dll_creation();
  test_dll_prepend();
  test_dll_move_to_front();
  return EXIT_SUCCESS;
}

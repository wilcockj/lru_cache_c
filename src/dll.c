#include "dll.h"

dll create_dll() {
  dll new_dll;
  new_dll.head = NULL;
  new_dll.tail = NULL;
  new_dll.length = 0;
  return new_dll;
}

int prepend_data(dll *linked_list, void *data) {

  dll_node *head = linked_list->head;
  dll_node *new_node = malloc(sizeof(dll_node));
  new_node->data = data;
  new_node->prev = NULL;
  new_node->next = head;

  if (head != NULL) {
    head->prev = new_node;
  }
  linked_list->length++;
  linked_list->head = new_node;
  if (linked_list->length == 1) {
    linked_list->tail = new_node;
  }
  // successful prepend
  return 0;
}

int remove_node(dll *linked_list, dll_node *node) {
  if (node == NULL) {
    return -1;
  }
  dll_node *old_prev = node->prev;
  dll_node *old_next = node->next;
  old_prev = old_next;
  old_next->prev = old_prev;
  free(node);
  return 0;
}

int move_node_to_front(dll *linked_list, dll_node *node) {
  // close the gap left by moving node
  dll_node *old_prev = node->prev;
  dll_node *old_next = node->next;
  old_prev = old_next;
  old_next->prev = old_prev;

  linked_list->length--;
  // prepend the data
  prepend_data(linked_list, node->data);

  return 0;
}

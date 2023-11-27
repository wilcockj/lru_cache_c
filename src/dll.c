#include "dll.h"
#include <stdbool.h>

dll create_dll() {
  dll new_dll;
  new_dll.head = NULL;
  new_dll.tail = NULL;
  new_dll.length = 0;
  return new_dll;
}

dll_node* prepend_data(dll *linked_list, void *data) {
  // create node
  dll_node *new_node = malloc(sizeof(dll_node));
  new_node->data = data;
  prepend_node(linked_list,new_node);
  return new_node;
}

int prepend_node(dll *linked_list, dll_node * node){
  dll_node *head = linked_list->head;

  node->prev = NULL;
  node->next = head;

  if (head != NULL) {
    head->prev = node;
  }

  linked_list->length++;
  linked_list->head = node;
  if (linked_list->length == 1) {
    linked_list->tail = node;
  }
  return 0;
}

int remove_node(dll *linked_list, dll_node *node) {
  if (node == NULL) {
    return -1;
  }
  bool is_head = linked_list->head == node;
  bool is_tail = linked_list->tail == node;

  dll_node *old_prev = node->prev;
  dll_node *old_next = node->next;
  old_prev = old_next;
  old_next->prev = old_prev;
  if(is_head){
     linked_list->head = node->next;
  }
  else if(is_tail){
      linked_list->tail = node->prev;
  }
  linked_list->length--;
  free(node);
  return 0;
}

int move_node_to_front(dll *linked_list, dll_node *node) {
  // close the gap left by moving node
  if(linked_list->head == node){
      // node is already at head
      return 0;
  }
  dll_node *old_prev = node->prev;
  dll_node *old_next = node->next;
  old_prev->next = old_next;
  if(old_next != NULL){
      old_next->prev = old_prev;
  }


  linked_list->length--;
  // prepend the data
  prepend_node(linked_list, node);

  if(node == linked_list->tail){
    linked_list->tail = old_prev;
  } 

  return 0;
}

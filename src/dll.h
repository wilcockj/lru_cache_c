#include <stdlib.h>
#ifndef DLL_H
#define DLL_H

struct Dll_node {
  void *data;
  struct Dll_node *prev;
  struct Dll_node *next;
};
typedef struct Dll_node dll_node;

typedef struct {
  dll_node *head;
  dll_node *tail;
  size_t length;
} dll;

dll create_dll();
dll_node *prepend_data(dll *linked_list, void *data);
int remove_node(dll *linked_list, dll_node *node);
int move_node_to_front(dll *linked_list, dll_node *node);
#endif

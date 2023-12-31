#include "lru.h"
#include "hashmap.h"
#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// add functionality for lru
// using the hashmap in hashmap.c/h to
// point to nodes in doubly linked list

// want to hash as function if possible, not sure if it is, other than macro
// magic
unsigned long hash_args(size_t *list, size_t list_len) {
  unsigned long hash = 0;
  // get first arg
  // which is just number of args
  for (size_t i = 0; i < list_len; i++) {
    hash = list[i] + (hash << 6) + (hash << 16) - hash;
  }
  return hash;
}

void *get_data(lru *cache, unsigned long hash) {

  // need to lookup hash in hashmap
  // that will point to node
  // get data from that node if exists and move to front
  // otherwise need to add new node to front
  // and remove from back if capacity is filled up
  hte *entry = get_entry(cache->node_map, hash);
  if (entry != NULL) {
    dll_node *node = (dll_node *)entry->data; // pointer to dll
    move_node_to_front(cache->dyn_ll, (dll_node *)entry->data);
    return node->data;
  }
  return NULL;
}

int add_data(lru *cache, unsigned long hash, void *data_ptr) {
  // check if the cache is full
  // if it is need to remove the last element
  hte *entry = get_entry(cache->node_map, hash);
  if (cache->node_map->entry_count == cache->capacity && entry == NULL) {
    // EVICTION TIME
    dll_node *tail = cache->dyn_ll->tail;

    assert(tail != NULL);

    int rmv_node_err = remove_node(cache->dyn_ll, tail);
    if (rmv_node_err != 0) {
      printf("SOME ERROR IN REMOVE NODE\n");
    }
    // remove the tail from dyn_ll
    ht *table = cache->node_map;
    // remove tail from hashmap
    // need to remove tail from hashmap
    int err = remove_entry_from_ptr(table, tail);
    if (err != 0) {
      printf("SOME ERROR IN REMOVE ENTRY\n");
    }
    cache->length--;
  }
  if (entry != NULL) {
    // data is already in linked list and needs
    // to be moved to the front
    move_node_to_front(cache->dyn_ll, (dll_node *)entry->data);
  } else {
    // do i need to put hash in dyn ll? dont think so
    dll_node *entry = prepend_data(cache->dyn_ll, data_ptr);
    // add node to hashtable
    add_entry(cache->node_map, (void *)entry, hash);
    cache->length++;
  }
  return 0;
}

lru *create_lru(size_t capacity) {
  if (capacity == 0) {
    // can't have no capacity
    return NULL;
  }
  assert(capacity != 0);
  lru *cache = malloc(sizeof(lru));
  cache->node_map = create_table(capacity);
  dll ll = create_dll();
  cache->dyn_ll = malloc(sizeof(dll));
  cache->dyn_ll->head = ll.head;
  cache->dyn_ll->tail = ll.tail;
  cache->dyn_ll->length = ll.length;
  cache->length = 0;
  cache->capacity = capacity;
  return cache;
}

int free_lru(lru *cache) {
  free_dll(cache->dyn_ll);
  free(cache->dyn_ll);
  free_table(cache->node_map);
  free(cache);
  return 0;
}

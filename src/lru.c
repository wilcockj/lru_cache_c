#include "lru.h"
#include "hashmap.h"
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

void * get_data(lru *cache,unsigned long hash){       

    // need to lookup hash in hashmap
    // that will point to node
    // get data from that node if exists and move to front
    // otherwise need to add new node to front
    // and remove from back if capacity is filled up
}


int add_data(lru *cache, unsigned long hash,void* data_ptr){
    // check if the cache is full
    // if it is need to remove the last element
    if(cache->length == cache->capacity){
        dll_node *tail = cache->dyn_ll->tail;
        remove_node(cache->dyn_ll,tail);
        // remove the tail from dyn_ll
        ht * table = cache->node_map; 
        // remove tail from hashmap
        int err = remove_entry(table, hash);
        if(err != 0){
            printf("SOME ERROR IN REMOVE ENTRY\n");
        }

    }
    // do i need to put hash in dyn ll? dont think so
    prepend_data(cache->dyn_ll, data_ptr);
    return 0;
}
/*

lru *_create_lru(size_t max_len, size_t Arg, ...) {
  lru *new_lru = malloc(sizeof(lru));
  new_lru->max_len = max_len;
  new_lru->len = 0;
  new_lru->head = NULL;
  new_lru->tail = NULL;
  printf("max len = %d\n", new_lru->max_len);
  va_list sArg;
  printf("number of args = %ld\n", Arg);
  int num_args = Arg;

  size_t all_args[MAX_ARGS];
  size_t all_args_len = 0;
  va_start(sArg, Arg);
  while (--Arg) {
    all_args[all_args_len++] = va_arg(sArg, size_t);
  }

  unsigned long hash = 0;
  hash = hash_args(all_args, all_args_len);

  printf("hash = %lu\n", hash);
  hash = 0;
  // get first arg
  // which is just number of args
  Arg = num_args;
  va_start(sArg, Arg);
  while (--Arg) {
    hash = va_arg(sArg, size_t) + (hash << 6) + (hash << 16) - hash;
  }
  // make a hash table and use the hash we made as the key

  // hash is hash unique to these args
  printf("hash = %lu\n", hash);

  Arg = num_args;
  va_start(sArg, Arg);
  while (--Arg) {
    printf("%ld = %ld\n", num_args - Arg - 1, va_arg(sArg, size_t));
  }
  return new_lru;
}*/


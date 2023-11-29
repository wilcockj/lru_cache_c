#ifndef HASHMAP_H
#define HASHMAP_H
#include <stdint.h>
#include <stdlib.h>

// take the has mod by size of hash map
// if there is an entry at that index already
// simply increment untl finding a free spot
// if map is full need to make a new one double the size

typedef struct {
  void *data;
  unsigned long hash_key;
  uint16_t accesses_to_find;
} hte;

typedef struct {
  hte *entries;
  size_t capacity;
  size_t entry_count;
} ht;

// make get function , used to check if in hash map as well
hte *get_entry(ht *table, unsigned long hash_key);
int add_entry(ht *table, void *data, unsigned long hash_key);
ht *create_table(size_t capacity);
int free_table(ht *table);
#endif

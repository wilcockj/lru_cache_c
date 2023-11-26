// for some reason when inserting not at the index of
// hash does not get it
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
hte *get_entry(ht *table, long unsigned hash_key) {
  size_t access_count = 1;
  size_t index = hash_key % table->capacity;
  hte *entry = &table->entries[index];
  if (entry->hash_key == hash_key) {
    printf("took %d accesses to find data\n", access_count);
    return entry;
  }
  // may not be present
  for (int i = index + 1; i < index + table->capacity; i++) {
    access_count++;
    if (table->entries[i % table->capacity].hash_key == hash_key) {
      printf("took %d accesses to find data\n", access_count);
      return &table->entries[i % table->capacity];
    }
  }
  printf("found nothing for hash key %d\n", hash_key);
  return NULL;
}

void add_entry(ht *table, void *data, long unsigned hash_key) {
  size_t index = hash_key % table->capacity;
  if (table->entries[index].data == NULL) {
    printf("inserting data at %d\n", index);
    table->entries[index].data = data;
    table->entries[index].hash_key = hash_key;
    table->entry_count++;
  } else {
    // linearly look for a free entry after index
    if (table->capacity == table->entry_count) {
      printf("TABLE WAS FULL ON KEY %lu\n", hash_key);
      return;
    }
    for (int i = index + 1; i < index + table->capacity; i++) {
      if (table->entries[i % table->capacity].data == NULL) {
        printf("linear probe inserting data at %d\n", i % table->capacity);
        table->entries[i % table->capacity].data = data;
        table->entries[i % table->capacity].hash_key = hash_key;
        table->entry_count++;
        return;
      }
    }
  }
}

ht *create_table(size_t capacity) {
  ht *table = malloc(sizeof(ht));
  table->entries = calloc(capacity, sizeof(hte));
  for (int i = 0; i < capacity; i++) {
    table->entries[i].data = NULL;
  }
  table->capacity = capacity;
  table->entry_count = 0;
  return table;
}

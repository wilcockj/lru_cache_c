#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

hte *get_entry(ht *table, long unsigned hash_key) {
  size_t access_count = 1;
  size_t index = hash_key % table->capacity;
  hte *entry = &table->entries[index];
  if (entry->hash_key == hash_key && entry->data != NULL) {
    entry->accesses_to_find = access_count;
    return entry;
  }
  // may not be present
  for (int i = index + 1; i < index + table->capacity; i++) {
    access_count++;
    hte *entry = &table->entries[i % table->capacity];
    if (entry->hash_key == hash_key) {
      entry->accesses_to_find = access_count;
      if (entry->data != NULL) {
        entry->accesses_to_find = access_count;
        return entry;
      } else {
        return NULL;
      }
    }
  }
  return NULL;
}

static hte *get_entry_index(ht *table, size_t index) {
  if (index > table->capacity) {
    return NULL;
  }
  hte *entry = &table->entries[index];
  return entry;
}

// TODO make this int return and add some errors
int add_entry(ht *table, void *data, long unsigned hash_key) {
  size_t index = hash_key % table->capacity;
  if (table->entries[index].data == NULL || table->entries[index].hash_key == hash_key) {
    // printf("inserting data at %d\n", index);
    table->entries[index].data = data;
    table->entries[index].hash_key = hash_key;
    table->entry_count++;
  } else {
    // linearly look for a free entry after index
    if (table->capacity == table->entry_count) {
      // TODO need to make new hash table double the capacity
#ifdef LOG
      printf("TABLE WAS FULL ON KEY %lu\n", hash_key);
      printf("capacity = %zu, entry_count = %ld\n", table->capacity,
             table->entry_count);
#endif
      ht *new_ht = create_table(table->capacity * 2);
      if (new_ht == NULL) {
        // some error allocating
        return -1;
      }

#ifdef LOG
      printf("allocated and populated new hash table, new capacity = %zu\n",
             new_ht->capacity);
#endif
      // put the old data in the new_ht
      for (int i = 0; i < table->capacity; i++) {
        hte *old_entry = get_entry_index(table, i);
        if (add_entry(new_ht, old_entry->data, old_entry->hash_key) != 0) {
          // error adding entry
        }
      }
      // free old table
      free(table->entries);
      table->entries = new_ht->entries;
      table->capacity = new_ht->capacity;
      table->entry_count = new_ht->entry_count;
      int err = add_entry(table, data, hash_key);
      if (err != 0) {
        // some error adding
        return -1;
      }
      return 0;
    }
    for (int i = index + 1; i < index + table->capacity; i++) {
      if (table->entries[i % table->capacity].data == NULL || table->entries[i % table->capacity].hash_key == hash_key) {
        // printf("linear probe inserting data at %d, num of entries = %d\n",
        //       i % table->capacity, table->entry_count);
        table->entries[i % table->capacity].data = data;
        table->entries[i % table->capacity].hash_key = hash_key;
        table->entry_count++;
        return 0;
      }
    }
  }
  return 0;
}

ht *create_table(size_t capacity) {
  ht *table = malloc(sizeof(ht));
  if (table == NULL) {
    return NULL;
  }
  table->entries = calloc(capacity, sizeof(hte));
  if (table->entries == NULL) {
    return NULL;
  }
  for (int i = 0; i < capacity; i++) {
    table->entries[i].data = NULL;
    table->entries[i].hash_key = 0;
  }
  table->capacity = capacity;
  table->entry_count = 0;
  return table;
}

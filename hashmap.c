#include <stdlib.h>
#include <stdio.h>
#include "hashmap.h"
hte* get_entry(ht * table,long unsigned hash_key){
	size_t index = hash_key % table->capacity;
	hte * entry = &table->entries[index];
	if(entry->hash_key == hash_key){
		return entry;
	}
	//may not be present
	for(int i = index; i < index + table->capacity;i++){
		if(table->entries[i].hash_key == hash_key){
			return &table->entries[i];
		}
	}
	return NULL;
}

void add_entry(ht *table, void *data, long unsigned hash_key){
	size_t index = hash_key % table->capacity;
	if(table->entries[index].hash_key == 0){
		table->entries[index].data = data;
		table->entries[index].hash_key = hash_key;
		table->entry_count++;
	}
	else{
		//linearly look for a free entry after index
		if(table->capacity == table->entry_count){
			printf("TABLE WAS FULL ON KEY %lu\n",hash_key);
			return;
		}
		for(int i = index+1; i < index + table->capacity; i++){
			if(table->entries[i].hash_key == 0){
				table->entries[i].data = data;
				table->entries[i].hash_key = hash_key;
				table->entry_count++;
			}
		}

	}
}

ht *create_table(size_t capacity){
	ht * table = malloc(sizeof(ht));
	table->entries = calloc(capacity,sizeof(hte));
	table->capacity = capacity;
	table->entry_count = 0;
	return table;
}
#include <stdint.h>

// take the has mod by size of hash map
// if there is an entry at that index already 
// simply increment untl finding a free spot
// if map is full need to make a new one double the size

typedef struct {
	void * data;
	long unsigned hash_key;
}hte;

typedef struct{ 
	hte *entries;
	size_t capacity;
	size_t entry_count;
}ht;


// make get function , used to check if in hash map as well
hte *get_entry(ht * table,long unsigned hash_key);
void add_entry(ht *table, void *data, long unsigned hash_key);
ht* create_table(size_t capacity);

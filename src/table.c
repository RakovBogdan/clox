#include "table.h"
#include "memory.h"
#include "value.h"
#include "memory.h"
#include "value.h"

#define TABLE_MAX_LOAD 0.75

void initTable(Table* table) {
	table->count = 0;
	table->capacity = 0;
	table->entries = NULL;
}

void freeTable(Table* table) {
	FREE_ARRAY(Entry, table->entries, table->capacity);
	initTable(table);
}

uint32_t getHash(Value* value) {
	if (IS_BOOL(*value)) {
		return AS_BOOL(*value) == true ? 1231 : 1237;
	} else if (IS_NIL(*value)) {
		return 0;
	} else if (IS_NUMBER(*value)) {
		double number = AS_NUMBER(*value);
		union { double full_number;
				struct { 
					uint32_t first_bits;
					uint32_t last_bits; 
				}; 
		} bits = { .full_number = number };

		return bits.first_bits^bits.last_bits;
	} else {
		ObjString* string = AS_STRING(*value);
		return string->hash;
	}
}

bool compareKeys(Value* key1, Value* key2) {
	switch (key1->type) {
		case VAL_NIL: return true;
		case VAL_BOOL: return AS_BOOL(*key1) == AS_BOOL(*key2);
		case VAL_NUMBER: return AS_NUMBER(*key1) == AS_NUMBER(*key2);
		case VAL_OBJ: return key1 == key2;
	default:
		break;
	}
}

static Entry* findEntry(Entry* entries, int capacity, Value* key) {
	uint32_t index = getHash(key) % capacity;
	Entry* tombstone = NULL;
	for (;;) {
		Entry* entry = &entries[index];
		if (entry->key == NULL) {
			if (IS_NIL(entry->value)) {
				return tombstone != NULL ? tombstone : entry;
			} else { 
				if (tombstone == NULL) tombstone = entry;
			}
		} else if (entry->key->type == key->type && compareKeys(entry->key, key)) {
			return entry;
		} 

		index = (index + 1) % capacity;
	}
}


static void adjustCapacity(Table* table, int capacity) {
	Entry* entries = ALLOCATE(Entry, capacity);

	for (int i = 0; i < capacity; i++) {
		entries[i].key = NULL;
		entries[i].value = NIL_VAL;
	}
	
	table->count = 0;
	for (int i = 0; i < table->capacity; i++) {
		Entry* entry = (table->entries + i);
		if (entry->key == NULL) continue;
		
		Entry* new_entry = findEntry(entries, capacity, entry->key);
		new_entry->key = entry->key;
		new_entry->value = entry->value;
		table->count++;
	}

	FREE_ARRAY(Entry, table->entries, table->capacity);

	table->entries = entries;
	table->capacity = capacity;
}

bool tableGet(Table* table, Value* key, Value* value) {
	if (table->count == 0) return false;

	Entry* entry = findEntry(table->entries, table->capacity, key);
	if (entry->key == NULL) return false;

	*value = entry->value;
	return true;
}

bool tableSet(Table* table, Value* key, Value value) {
	if (table->count + 1 > table->capacity * TABLE_MAX_LOAD) {
		int newCapacity = GROW_CAPACITY(table->capacity);
		adjustCapacity(table, newCapacity);
	}

	Entry* entry = findEntry(table->entries, table->capacity, key);
	bool isNewKey = entry->key == NULL;
	if (isNewKey && IS_NIL(entry->value)) table->count++;

	entry->key = key;
	entry->value = value;

	return isNewKey;
}

bool tableDelete(Table* table, Value* key) {
	if (table->count == 0) return false;

	Entry* entry = findEntry(table->entries, table->capacity, (Value*)key);
	if (entry->key = NULL) return false;

	entry->key = NULL;
	entry->value = BOOL_VAL(true);
	return true;
}

void tableAddAll(Table* from, Table* to) {
	for (int i = 0; i < from->capacity; i++) {
		Entry* entry = from->entries + i;
		if (entry->key != NULL) tableSet(to, entry->key, entry->value);
	}
}




#include <stdio.h>
#include <string.h>

#include "object.h"
#include "memory.h"
#include "value.h"
#include "vm.h"
#include "table.h"

#define ALLOCATE_OBJ(type, objectType) \
	(type*)allocateObject(sizeof(type), objectType)

Obj* allocateObject(size_t size, ObjType type) {
	Obj* object = (Obj*)reallocate(NULL, 0, size);
	object->type = type;

	object->next = vm.objects;
	vm.objects = object;
	return object;
}

ObjFunction* newFunction() {
	ObjFunction* function = ALLOCATE_OBJ(ObjFunction, OBJ_FUNCTION);
	function->arity = 0;
	function->name = NULL;
	initChunk(&function->chunk);
	return function;
}

ObjString* allocateString(char* chars, int length, uint32_t hash) {
	ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
	string->chars = chars;
	string->length = length;
	string->hash = hash;
	tableSet(&vm.strings, string, NIL_VAL);
	return string;
}

ObjString* tableFindString(Table* table, const char* start, int length, uint32_t hash) {
	if (table->count == 0) return NULL;

	uint32_t index = hash % table->capacity;
	for (;;) {
		Entry* entry = table->entries + index;
		if (entry->key == NULL) {
			if (IS_NIL(entry->value)) return NULL;
		} else if (length == entry->key->length &&
			    hash == entry->key->hash &&
				memcmp(entry->key->chars, start, length) == 0) {
			return entry->key;
		}
		index = (index + 1) % table->capacity;
	}

}

ObjString* copyString(const char* start, int length) {
	uint32_t hash = hashString(start, length);
	ObjString* interned = tableFindString(&vm.strings, start, length, hash);
	if (interned != NULL) return interned;

	char* heapChars = ALLOCATE(char, length + 1);
    memcpy(heapChars, start, length);
	heapChars[length] = '\0';
	return allocateString(heapChars, length, hash);
}

static void printFunction(ObjFunction* function) {
	if (function->name == NULL) {
		printf("<script>");
		return;
	}
	printf("<fn %s>", function->name->chars);
}

ObjString* takeString(char* start, int length) {
	uint32_t hash = hashString(start, length);
	ObjString* interned = tableFindString(&vm.strings, start, length, hash);
	if (interned != NULL) {
		FREE_ARRAY(char, start, length + 1);
		return interned;
	}
	return allocateString(start, length, hash);
}

uint32_t hashString(char* key, int length) {
	uint32_t hash = 2166136261u;
	for (int i = 0; i < length; i++) {
		hash ^= (uint8_t)key[i];
		hash *= 16777619;
	}
	return hash;
}

void printObject(Value value) {
    switch ((AS_OBJ(value))->type) {
        case(OBJ_FUNCTION): 
			printFunction(AS_FUNCTION(value));
			break;
        case(OBJ_STRING): printf("%s", AS_CSTRING(value)); break;
    }
}

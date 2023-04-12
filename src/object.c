#include <stdio.h>
#include <string.h>

#include "object.h"
#include "memory.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, objectType) \
	(type*)allocateObject(sizeof(type), objectType)

Obj* allocateObject(size_t size, ObjType type) {
	Obj* object = (Obj*)reallocate(NULL, 0, size);
	object->type = type;

	object->next = vm.objects;
	vm.objects = object;
	return object;
}

ObjString* allocateString(char* chars, int length, uint32_t hash) {
	ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
	string->chars = chars;
	string->length = length;
	string->hash = hash;
	return string;
}

ObjString* copyString(const char* start, int length) {
	uint32_t hash = hashString(start, length);
	char* heapChars = ALLOCATE(char, length + 1);
    memcpy(heapChars, start, length);
	heapChars[length] = '\0';
	return allocateString(heapChars, length, hash);
}

ObjString* takeString(char* start, int length) {
	uint32_t hash = hashString(start, length);
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
        case(OBJ_STRING): printf("%s", AS_CSTRING(value)); break;
    }
}

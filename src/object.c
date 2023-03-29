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

ObjString* allocateString(char* chars, int length) {
	ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
	string->chars = chars;
	string->length = length;
	return string;
}

ObjString* copyString(char* start, int length) {
	char* heapChars = ALLOCATE(char, length + 1);
    memcpy(heapChars, start, length);
	heapChars[length] = '\0';
	return allocateString(heapChars, length);
}

ObjString* takeString(char* start, int length) {
	return allocateString(start, length);
}

void printObject(Value value) {
    switch ((AS_OBJ(value))->type) {
        case(OBJ_STRING): printf("%s", AS_CSTRING(value)); break;
    }
}

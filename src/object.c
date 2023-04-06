#include <stdio.h>
#include <string.h>

#include "object.h"
#include "memory.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, flexible_size, objectType) \
	(type*)allocateObject(sizeof(type) + flexible_size, objectType)

Obj* allocateObject(size_t size, ObjType type) {
	Obj* object = (Obj*)reallocate(NULL, 0, size);
	object->type = type;

	object->next = vm.objects;
	vm.objects = object;
	return object;
}

ObjString* allocateString(const char* start, int length) {
	ObjString* string = ALLOCATE_OBJ(ObjString, length + 1, OBJ_STRING);
    memcpy(string->chars, start, length);
	string->chars[length] = '\0';
	string->length = length;
	return string;
}

void printObject(Value value) {
    switch ((AS_OBJ(value))->type) {
        case(OBJ_STRING): printf("%s", AS_CSTRING(value)); break;
    }
}

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

ObjString* allocateString(char* chars, int length, bool isOwner) {
	ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
	string->chars = chars;
	string->length = length;
	string->isOwner = isOwner;
	return string;
}

ObjString* takeString(char* start, int length) {
	return allocateString(start, length, false);
}

ObjString* takeStringAsOwner(char* start, int length) {
	return allocateString(start, length, true);
}

void printObject(Value value) {
    switch ((AS_OBJ(value))->type) {
        case(OBJ_STRING): printf("%.*s", AS_STRING(value)->length, AS_CSTRING(value)); break;
    }
}

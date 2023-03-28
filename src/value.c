#include <stdio.h>
#include <string.h>

#include "value.h"
#include "memory.h"
#include "object.h"

void initValueArray(ValueArray* valueArray) {
    valueArray->values = NULL;
    valueArray->capacity = 0;
    valueArray->count = 0;
}

void writeValueArray(ValueArray* valueArray, Value value) {
    if (valueArray->capacity < valueArray->count + 1) {
        int oldCapacity = valueArray->capacity;
        valueArray->capacity = GROW_CAPACITY(oldCapacity);
        valueArray->values = GROW_ARRAY(Value, valueArray->values, oldCapacity, valueArray->capacity);
    }
    valueArray->values[valueArray->count] = value;
    valueArray->count++;
}

void freeValueArray(ValueArray* valueArray) {
    FREE_ARRAY(Value, valueArray->values, valueArray->capacity);
    initValueArray(valueArray);
}

void printValue(Value value) {
    switch (value.type) {
        case VAL_BOOL:
            printf(AS_BOOL(value) ? "true" : "false");
            break;
        case VAL_NIL: printf("nil"); break;
        case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
        case VAL_OBJ: printObject(value); break;
    }
}

bool valuesEqual(Value firstValue, Value secondValue) {
    if (firstValue.type != secondValue.type) return false;
    switch (firstValue.type) {
        case VAL_BOOL: return AS_BOOL(firstValue) == AS_BOOL(secondValue);
        case VAL_NIL: return true;
        case VAL_NUMBER: return AS_NUMBER(firstValue) == AS_NUMBER(secondValue);
        case VAL_OBJ: {
            ObjString* firstString = AS_STRING(firstValue);
            ObjString* secondString = AS_STRING(secondValue);
            return firstString->length == secondString->length &&
                memcmp(firstString->chars, secondString->chars, firstString->length) == 0;
        }
        default: return false;
    }
}

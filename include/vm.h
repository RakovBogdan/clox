#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 4

typedef struct {
    Chunk *chunk;
    uint8_t *ip;
    Value* stack;
    int capacity;
    Value* stack_top;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

InterpretResult interpret(Chunk *chunk);
void push(Value value);
Value pop();

void initVM();
void freeVM();

#endif

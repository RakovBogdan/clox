#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"
#include "memory.h"

VM vm;

void push(Value value) {
    int count = vm.stack_top - vm.stack;
    if (vm.capacity < count + 1) {
        vm.capacity = GROW_CAPACITY(vm.capacity);
        vm.stack = GROW_ARRAY(Value, vm.stack, count, vm.capacity);
        vm.stack_top = vm.stack + count;
    }
    *vm.stack_top = value;
    vm.stack_top++;
}

Value pop() {
    vm.stack_top--;
    return *vm.stack_top;
}

static void resetStack() {
    vm.stack_top = vm.stack;
}

void initVM() {
    vm.capacity = STACK_MAX;
    vm.stack = GROW_ARRAY(Value, vm.stack, 0, vm.capacity);
    resetStack();
}


void freeVM() {
    FREE_ARRAY(Value, vm.stack, vm.capacity);
    vm.stack = NULL;
    vm.stack_top = NULL;
    vm.capacity = 0;
}


static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
    do { \
        double second = pop(); \
        double first = pop(); \
        push(first op second); \
    } while (false)

    for(;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("         ");
        for (Value* slot = vm.stack; slot < vm.stack_top; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_ADD:
                BINARY_OP(+);
                break;
            case OP_SUBSTRACT:
                BINARY_OP(-);
                break;
            case OP_MULTIPLY:
                BINARY_OP(*);
                break;
            case OP_DIVIDE:
                BINARY_OP(/);
                break;
            case OP_NEGATE:
                push(-pop());
                break;
            case OP_RETURN:
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
        }
    }
#undef BINARY_OP
#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult interpret(Chunk *chunk) {
    vm.chunk = chunk;
    vm.ip = chunk->code;
    return run();
}

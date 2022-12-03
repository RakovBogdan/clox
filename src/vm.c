#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

void push(Value value) {
    *vm.stack_top = value;
    vm.stack_top++;
}

Value pop() {
    vm.stack_top--;
    return *vm.stack_top;;
}

static void resetStack() {
    vm.stack_top = vm.stack;
}

void initVM() {
    resetStack();
}


void freeVM() {

}


static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    for(;;) {
#ifdef DEBUG_TRACE_EXECUTION
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_RETURN:
                return INTERPRET_OK;
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            }
        }
    }
#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult interpret(Chunk *chunk) {
    vm.chunk = chunk;
    vm.ip = chunk->code;
    return run();
}

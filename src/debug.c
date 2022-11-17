#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);
    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
        printf("   | ");
    }
    else {
        printf("%4d ", chunk->lines[offset]);
    }
    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_CONSTANT_LONG:
            return constantLongInstruction("OP_CONSTANT_LONG", chunk, offset);
        default:
            printf("Uknown opcode %d \n", instruction);
            return offset + 1;
    }
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constantAddress = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constantAddress);
    printValue(chunk->constants.values[constantAddress]);
    printf("'\n");
    return offset + 2;
}

static int constantLongInstruction(const char* name, Chunk* chunk, int offset) {
    int constantAddress = chunk->code[offset + 3];
    constantAddress = (constantAddress << 8) + chunk->code[offset + 2];
    constantAddress = (constantAddress << 16) + chunk->code[offset + 1];
    printf("%-16s %8d '", name, constantAddress);
    printValue(chunk->constants.values[constantAddress]);
    printf("'\n");
    return offset + 4;
}

#include "line.h"
#include "memory.h"

void initLineArray(LineArray* lineArray) {
    lineArray->count = 0;
    lineArray->capacity = 0;
    lineArray->values = NULL;
}

void freeLineArray(LineArray* lineArray) {
    FREE_ARRAY(int, lineArray->values, lineArray->count);
    initLineArray(lineArray);
}

void writeLineArray(LineArray* lineArray, int line) {
    bool isSameLine = lineArray->count > 0 && lineArray->values[lineArray->count - 1] == line;
    if (lineArray->capacity == 0 || (!isSameLine && lineArray->capacity < lineArray->count + 2)) {
        int oldCapacity = lineArray->capacity;
        lineArray->capacity = GROW_CAPACITY(lineArray->capacity);
        lineArray->values = GROW_ARRAY(int, lineArray->values, oldCapacity, lineArray->capacity);
    }
    if (isSameLine) {
        lineArray->values[lineArray->count - 2]++;
    } else {
        lineArray->values[lineArray->count] = 1;
        lineArray->values[lineArray->count + 1] = line;
        lineArray->count += 2;
    }
}

int getLine(LineArray* lineArray, int offset) {
    for (int i = 1, sum = 0; i < lineArray->count; i += 2) {
        sum += lineArray->values[i-1];
        if (sum > offset) {
            return lineArray->values[i];
        }
    }
}


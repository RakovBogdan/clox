#include "stdlib.h"
#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
	chunk->lines = NULL;
	initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
	if (chunk->capacity < chunk->count + 1) {
		int oldCapacity = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(oldCapacity);
		chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
		chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
	}
	chunk->code[chunk->count] = byte;
	chunk->lines[chunk->count] = line;
	chunk->count++;
}

void writeConstant(Chunk* chunk, Value value, int line) {
	writeValueArray(&chunk->constants, value);
    int constantAddress = chunk->constants.count - 1;
	writeChunk(chunk, OP_CONSTANT_LONG, line);
    
	if (chunk->capacity < chunk->count + 3) {
		int oldCapacity = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(oldCapacity);
		chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
		chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
	}
	chunk->code[chunk->count] = constantAddress >> 0;
	chunk->code[chunk->count+1] = constantAddress >> 8;
	chunk->code[chunk->count+2] = constantAddress >> 16;
	chunk->lines[chunk->count] = line;
	chunk->lines[chunk->count+1] = line;
	chunk->lines[chunk->count+2] = line;
	chunk->count+=3;
}


int addConstant(Chunk* chunk, Value value) {
	writeValueArray(&chunk->constants, value);
	return chunk->constants.count - 1;
}

void freeChunk(Chunk* chunk) {
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	FREE_ARRAY(int, chunk->lines, chunk->capacity);
	freeValueArray(&chunk->constants);
	initChunk(chunk);
}

#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
	OP_CONSTANT,
	OP_NIL,
	OP_NEGATE,
	OP_NOT,
	OP_TRUE,
	OP_FALSE,
	OP_ADD,
	OP_SUBSTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_POP,
	OP_SET_GLOBAL,
	OP_GET_GLOBAL,
	OP_SET_LOCAL,
	OP_GET_LOCAL,
	OP_DEFINE_GLOBAL,
	OP_EQUAL,
	OP_GREATER,
	OP_LESS,
	OP_PRINT,
	OP_RETURN,
} OpCode;

typedef struct {
	Value name;
	bool isFinal;
	bool isReassigned;
} Global;

typedef struct {
	int count;
	int capacity;
	uint8_t* code;
	int* lines;
	ValueArray constants;
	Global globals[UINT8_COUNT];
	int globalsCount;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);
void freeChunk(Chunk* chunk);

#endif
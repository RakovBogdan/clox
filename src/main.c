#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
	Chunk chunk;
	initChunk(&chunk);

	int constant = addConstant(&chunk, 1.2);
	writeChunk(&chunk, OP_CONSTANT, 123);
	writeChunk(&chunk, constant, 123);
	
	writeChunk(&chunk, OP_RETURN, 123);
	writeChunk(&chunk, OP_RETURN, 124);
	writeChunk(&chunk, OP_RETURN, 124);
	writeChunk(&chunk, OP_RETURN, 125);
	writeChunk(&chunk, OP_RETURN, 126);

	int constant2 = addConstant(&chunk, 3.7);
	writeChunk(&chunk, OP_CONSTANT, 127);
	writeChunk(&chunk, constant2, 127);
	writeChunk(&chunk, OP_RETURN, 129);
	writeChunk(&chunk, OP_RETURN, 129);
	disassembleChunk(&chunk, "test chunk");
	freeChunk(&chunk);
	return 0;
}
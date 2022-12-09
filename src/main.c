#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
    initVM();
	Chunk chunk;
	initChunk(&chunk);

	int constantAddress = addConstant(&chunk, 1.2);
	writeChunk(&chunk, OP_CONSTANT, 123);
	writeChunk(&chunk, constantAddress, 123);
	
	constantAddress = addConstant(&chunk, 3.4);
	writeChunk(&chunk, OP_CONSTANT, 123);
	writeChunk(&chunk, constantAddress, 123);
	
	writeChunk(&chunk, OP_ADD, 123);
	
	constantAddress = addConstant(&chunk, 5.6);
	writeChunk(&chunk, OP_CONSTANT, 123);
	writeChunk(&chunk, constantAddress, 123);

	writeChunk(&chunk, OP_DIVIDE, 123);
	writeChunk(&chunk, OP_NEGATE, 123);

	for (int i = 0; i < 70; i++) {
	    constantAddress = addConstant(&chunk, (double)i);
		writeChunk(&chunk, OP_CONSTANT, 123);
		writeChunk(&chunk, constantAddress, 123);
	}
	
	writeChunk(&chunk, OP_RETURN, 123);
    interpret(&chunk);
    freeVM();
	freeChunk(&chunk);
	return 0;
}
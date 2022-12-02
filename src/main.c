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
	
	writeChunk(&chunk, OP_RETURN, 123);
    interpret(&chunk);
    freeVM();
	freeChunk(&chunk);
	return 0;
}
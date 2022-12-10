#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"
#include <time.h>
#include <stdio.h>

int main(int argc, const char* argv[]) {
    initVM();
	Chunk chunk;
	initChunk(&chunk);

	int constantAddress = addConstant(&chunk, 1.2);
	writeChunk(&chunk, OP_CONSTANT, 123);
	writeChunk(&chunk, constantAddress, 123);
	
	for (int i = 0; i < 1000000001; i++) {
		writeChunk(&chunk, OP_NEGATE, 123);
	}
	
	writeChunk(&chunk, OP_RETURN, 123);
	clock_t start = clock();
    interpret(&chunk);
	clock_t end = clock();
	double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    freeVM();
	freeChunk(&chunk);
	printf("Time: %.3f seconds\n", elapsed);
	return 0;
}
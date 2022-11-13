#ifndef clox_line_h
#define clox_line_h

typedef struct {
	int count;
	int capacity;
	int* values;
} LineArray;

void initLineArray(LineArray* lineArray);
void freeLineArray(LineArray* lineArray);
void writeLineArray(LineArray* lineArray, int line);
int getLine(LineArray* lineArray, int offset);

#endif
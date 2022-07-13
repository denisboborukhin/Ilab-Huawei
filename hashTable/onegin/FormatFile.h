#ifndef FORMATFILE
#define FORMATFILE

#include <stdio.h>
#include <assert.h>

int FormFile(const char* nameIn, const char* nameOut);
bool CheckCorrect(int c);
int OutputSymbol(FILE* file, FILE* formFile, bool* outOfStr, int c);
int ElemOut(FILE* file, FILE* formFile, bool* outOfStr, int c);
int ElemIn(FILE* file, FILE* formFile, bool* outOfStr, int c);

#endif // FORMATFILE

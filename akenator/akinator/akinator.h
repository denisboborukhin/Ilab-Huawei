#ifndef AKINATOR
#define AKINATOR

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../tree/tree.h"
#include "../stack/MyStack.h"
#include "onegin/SortText.h"

enum answer
{
    YES     =   1,
    NO           ,
    NOTANSW
};

const int   ENDGAME             =       5934;

extern const int   MAXANSWSIZE;

int         Akinator            (item* node);
int         WhileForTheGame     (item* node, char* str);
int         AkinatorStartGame   (item* node, char* str);
int         AddNewItm           (item* node);
int         AddItmInTree        (item* node, char* str, char* ability);

char*       ScanAnswer          (char* str);
answer      CheckAnswer         (char* str);
void        CleanBuf            ();

int         CtorTreeListing     (FILE* file, struct item* root, int* count = nullptr);

CTree       CtorTreeFromFile    (const char* fileName);
item*       CtorItmFromFile     (item* node, char* buffer, int* index, int sizeBuf);

#endif

#ifndef MYLIST
#define MYLIST

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "../graphviz/graphviz.h"

#define INFOCHECK __FILE__, __LINE__, __PRETTY_FUNCTION__

#define LISTS_CHECK if (ListOk (*lst) ==   MISTAKE)                                         \
                    {                                                                       \
                        printf("IN the program: %s\nIN the line: %d\nIN the function: %s\n" \
                                , INFOCHECK);                                               \
                        assert (!"ERROR");                                                  \
                    }
                    


typedef     int     elemType;

const int       STARTNUMELEM    =     10;
const int       FIRSTELEM       =      1;

const int       LIANERIZED      =      1;
const int       NOTLIANERIZED   =      0;
const int       ORIGCAPACITY    =   -121;

const int       DESTROYED       =   -213;

const int       NOMISTAKE       =      0;       
const int       MISTAKE         =   1332;

const double    RESIZEUPCOEF    =    1.4; 
const double    RESIZEDOWNCOEF  =    1.5;



struct item
{
    elemType    data            =      0;
    int         next            =      0;
    int         prev            =      0;
};


struct lists
{
    struct item*    lists       =     {};
    int             capacity    =      0;
    int             size        =      0;
    int             free        =      0;
    int             statLin     =      0; 
};



int ListCtor            (struct lists* lst, int capacity);
int ListDtor            (struct lists* lst);
int ListDtorData        (struct lists* lst);
int ListLinearize       (struct lists* lst, int capacity = ORIGCAPACITY);
int ListOk              (struct lists lst);

int ListDelete          (struct lists* lst, int num);
int ListDeleteHead      (struct lists* lst);
int ListDeleteTail      (struct lists* lst);

int ListInsert          (struct lists* lst, int num, elemType value);
int ListInsertHead      (struct lists* lst, elemType value);
int ListInsertTail      (struct lists* lst, elemType value);
int LogNumToPhys        (struct lists  lst, int* num);

int ListInsertWarg      (int statLin, int num);
int ListDeleteWarg      (struct lists* lst);

int ListSizeCheck       (struct lists* lst);
int ListResizeUp        (struct lists* lst);
int ListResizeDown      (struct lists* lst);

int ListDump            (struct lists* lst);
int ListDumpCtorElem    (struct lists* lst);
int ListDumpCtorEdge    (struct lists* lst);
int ListDumpCtorFrEdge  (struct lists* lst);
int ListDumpCtorEdgeInv (struct lists* lst); 



#endif 

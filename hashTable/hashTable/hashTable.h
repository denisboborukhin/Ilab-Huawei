#ifndef HASHTABLE
#define HASHTABLE

#include <stdio.h>
#include "../cppLists/cppLists.h"

//typedef int ElemType;

class CHashTbl
{
private:
    CLists*         lists_      = NULL;
    int             size_       =    0;
  
    int             Hash_       (const char* key, unsigned int len);
    int             HashOk_     ();

public:
    explicit        CHashTbl    (int size);
                    ~CHashTbl   ();  

    int             insert      (ElemType data);
    int             del         (ElemType data);
    int             dump        (); 
    int             countElem   (ElemType data); 
};

#endif

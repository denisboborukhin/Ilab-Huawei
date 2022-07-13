#include <stdio.h>

#include "lists/myList.h"

int main ()
{
    struct lists lst = {};

    ListCtor (&lst, 5);

    ListInsert (&lst, 1, 5);
    ListInsert (&lst, 2, 100);    
    ListInsert (&lst, 3, 15);
    ListInsert (&lst, 6, 10);
    ListInsertHead (&lst, 33);

    ListLinearize (&lst);

    ListDeleteTail (&lst);


    ListDump (&lst);

    ListDtor (&lst);

    return 0;
}

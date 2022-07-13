// Features 
// The next element number is negative in the next element's next element array for free elements

#include "myList.h"

int ListCtor (struct lists* lst, int capacity)
{
    assert (lst != NULL);

    lst->lists  = (struct item*) calloc (capacity + 1, sizeof (struct item));
    lst->capacity = capacity;

    int i = FIRSTELEM;
    for (; i < capacity; i++)
    {
        lst->lists[i].next = - i - 1;
        lst->lists[i].prev = - 1;
    }
    lst->lists[i].prev = - 1;

    lst->free       = - 1;
    lst->size       =   0;
    lst->statLin    = LIANERIZED;

    LISTS_CHECK

    return NOMISTAKE;  
}

int ListDtor (struct lists* lst)
{
    LISTS_CHECK

    ListDtorData (lst);

    free (lst->lists);
    
    lst->capacity   = DESTROYED;
    lst->size       = DESTROYED;
    lst->free       = DESTROYED;
    lst->statLin    = DESTROYED;

    return NOMISTAKE;
}

int ListDtorData (struct lists* lst)
{
    for (int index = 0; index < lst->capacity + 1; index++)
    {
        lst->lists[index].data = DESTROYED;
        lst->lists[index].next = DESTROYED;
        lst->lists[index].prev = DESTROYED;
    }

    return NOMISTAKE;
}

//=========================LIST_INSERT===========================
//----insert-an-item-into-a-lianerized-list-by-logical-number----
//===============================================================

int ListInsert (struct lists* lst, int num, elemType value)
{
    LISTS_CHECK 

    if (ListInsertWarg (lst->statLin, num) == MISTAKE)
        return MISTAKE;

    LogNumToPhys (*lst, &num);                             
    assert (num >= 0);

    if (num != lst->lists[0].prev)                 
        lst->statLin = NOTLIANERIZED;

    int free = abs (lst->free);
    
    struct item* workElem   = &(lst->lists)[free];  
    struct item* insertElem = &(lst->lists)[num];

    lst->free = workElem->next;
    
    workElem->data = value; 
    workElem->next = insertElem->next;
    workElem->prev = num;

    insertElem->next = free;
    (lst->lists)[workElem->next].prev = free;
    
    lst->size++;

    ListSizeCheck (lst);
    
    LISTS_CHECK

    return NOMISTAKE;
}

//===============================================================
//---------------log-num-to-phys-for-lianerized------------------
//===============================================================

int LogNumToPhys (struct lists lst, int* num)
{
    int logNum =  *num;
    int phNum  =     0;

    if (logNum == FIRSTELEM)                                                    //for add to the top
        phNum = logNum - 1;
    else if (logNum > lst.size)                                                 //for add to the end
        phNum = lst.lists[0].prev;
    else                                                                
        phNum = phNum + lst.lists[0].next - 2;

    *num = phNum;

    return NOMISTAKE;
}

int ListInsertHead (struct lists* lst, elemType value)
{
    return ListInsert (lst, FIRSTELEM, value);
}

int ListInsertTail (struct lists* lst, elemType value)
{
    return ListInsert (lst, lst->lists[0].prev + 1, value);
}

int ListDelete (struct lists* lst, int num)
{
    LISTS_CHECK
    assert (num > 0);

    if (ListDeleteWarg (lst) == MISTAKE)
        return MISTAKE;

    if ((num != lst->lists[0].prev) && (num != lst->lists[0].next))
        lst->statLin = NOTLIANERIZED;
    
    struct item* workElem = &(lst->lists)[num];
    
    (lst->lists)[workElem->prev].next = workElem->next;
    (lst->lists)[workElem->next].prev = workElem->prev;

    workElem->next = - 1;
    workElem->prev = - 1;
    workElem->data =   0;

    lst->size--;

    ListSizeCheck (lst);

    LISTS_CHECK

    return NOMISTAKE;
} 

int ListDeleteHead (struct lists* lst)
{
    return ListDelete (lst, FIRSTELEM);
}

int ListDeleteTail (struct lists* lst)
{
    return ListDelete (lst, lst->lists[0].prev);
}

//======================List_Lianerized==========================
//----------------list-linearization-function--------------------
//===============================================================

int ListLinearize (struct lists* lst, int capacity)                //you can increase the size of the lianerized list   
{    
    LISTS_CHECK
       
//checking the list for linearity, taking into account the fact that the beginning contains deleted items
    if ((lst->statLin == LIANERIZED) && (lst->lists[0].next < STARTNUMELEM))       
        return NOMISTAKE;

    if ((capacity == ORIGCAPACITY) || (capacity <= lst->capacity))
        capacity = lst->capacity;

    struct item* newLists  = (struct item*) calloc (capacity + 1, sizeof (struct item));

    newLists[0].next = FIRSTELEM;
    newLists[0].prev = lst->size;

    int nextElem = lst->lists[0].next;
    int count = FIRSTELEM;

    for (; count <= lst->size; count++)                                         //Linearized data item
    {
        newLists[count].data = lst->lists[nextElem].data;
        newLists[count].next = count + 1;
        newLists[count].prev = count - 1;

        nextElem = lst->lists[nextElem].next;   
    }
    newLists[count - 1].next = 0;

    lst->free = count;

    while (count < capacity)                                                    //Linearized free item
    {
        newLists[count].next = - count - 1;
        newLists[count].prev = - 1;
    
        count++;
    }
    newLists[count].next =   0; 
    newLists[count].prev = - 1;

    free (lst->lists);

    lst->lists      = newLists;
    lst->capacity   = capacity;
    lst->statLin    = LIANERIZED;
    
    LISTS_CHECK

    return NOMISTAKE;      
}

//======================LIST_SIZE_CHECK==========================
//-------------if-used-with-a-non-lianerized-list----------------
//-----------there may be inefficient memory usage---------------
//===============================================================

int ListSizeCheck (struct lists* lst)
{
    LISTS_CHECK

    if (lst->capacity - abs (lst->free) < 2)
        return ListResizeUp (lst);
    else if ((lst->size > RESIZEDOWNCOEF * STARTNUMELEM) && (lst->free < lst->capacity / 2))
        return ListResizeDown (lst);
    else
        return NOMISTAKE; 
}

int ListResizeDown (struct lists* lst)
{
    LISTS_CHECK

    int newCapacity = (int) (lst->capacity / RESIZEDOWNCOEF);
    
    lst->lists = (struct item*) realloc (lst->lists, size_t ((newCapacity + 1) * sizeof (struct item)));

    lst->capacity = newCapacity;

    LISTS_CHECK
    
    return NOMISTAKE;
}

int ListResizeUp (struct lists* lst)
{
    LISTS_CHECK
    
    int num = lst->capacity;
    int newCapacity = (int) (lst->capacity * RESIZEUPCOEF);

    lst->lists = (struct item*) realloc (lst->lists, size_t ((newCapacity + 1) * sizeof (struct item)));

    for (; num < newCapacity; num++)
    {
        lst->lists[num].data =  0;
        lst->lists[num].next = - num - 1;
        lst->lists[num].prev = - 1;
    }
    lst->lists[num].data =   0;
    lst->lists[num].next =   0;
    lst->lists[num].prev = - 1;

    lst->capacity = newCapacity;

    LISTS_CHECK
    
    return NOMISTAKE;
}

int ListOk (struct lists lst)
{
    int ERROR = NOMISTAKE;

    if (lst.capacity == DESTROYED)
    {
        printf ("ERROR!!! LISTS DESTROYED\n");
        ERROR = MISTAKE;
    }
    if ((lst.size > lst.capacity) || (lst.size < 0))
    {
        printf ("ERROR!!! LISTS SIZE\n");
        ERROR = MISTAKE;
    }
    if (lst.capacity < 0)
    {
        printf ("ERROR!!! CAPACITY\n");
        ERROR = MISTAKE;
    }    

    return ERROR;
}

int ListInsertWarg (int statLin, int num)
{
    if (statLin == 0)
        printf ("WARNING!!! Insert into a non-lianerized list (an undesirable result is possible)\n");
 
    if (num < FIRSTELEM)
    {
        printf ("ERROR!!! Invalid position in the list\n");
        return MISTAKE;
    }

    return NOMISTAKE;
}

int ListDeleteWarg (struct lists* lst)
{
    if (lst->statLin == 0)
        printf ("WARNING!!! Delete from a non-lianerized list (an undesirable result is possible)\n");

    if (lst->size == 0)
    {
        printf ("ERROR!!! Remove from empty list\n");
        return MISTAKE;
    }
    
    return NOMISTAKE;
}

//==========================LIST_DUMP============================
//-------------------functions-for-debugging---------------------
//===============================================================

int ListDump (struct lists* lst)
{
    LISTS_CHECK
    
    DotCtor ("LR", "darkkhaki");

    ListDumpCtorElem (lst);
    
    ListDumpCtorEdgeInv (lst);
    ListDumpCtorEdge    (lst); 

    ListDumpCtorFrEdge  (lst);

    DotEnd ();

    LISTS_CHECK
    
    return NOMISTAKE;
}

int ListDumpCtorElem (struct lists* lst)
{
    assert (lst != NULL);

    int data = lst->lists[0].data;
    int next = lst->lists[0].next;                          //head
    int prev = lst->lists[0].prev;                          //tail

    DotInfoElemCtor (lst->capacity, lst->size, next, prev, abs (lst->free), lst->statLin);


    DotElemCtor (0, data, next, prev, "record", "pink");

    for (int i = 1; i < lst->capacity + 1; i++)
    {
        data = lst->lists[i].data;
        next = lst->lists[i].next;
        prev = lst->lists[i].prev;

        DotElemCtor (i, data, next, prev);
    }

    return NOMISTAKE;
}

int ListDumpCtorEdgeInv (struct lists* lst)
{
    assert (lst != NULL);

    DotPrintf ("\tinfo->elem0[style=invisible, color = \"none\"];\n"); 
    
    for (int i = 0; i < lst->capacity; i++)
        DotEdgeCtor (i, i + 1, "invisible");

    return NOMISTAKE;
}

int ListDumpCtorEdge (struct lists* lst)
{
    assert (lst != NULL);

    int count = 0;
    int point = 0;

    while (count != lst->size + 1)
    {
        DotEdgeCtor (point, lst->lists[point].next, "none", "dodgerblue");
        DotEdgeCtor (point, lst->lists[point].prev, "dotted", "darkorange3");

        point = lst->lists[point].next;
        
        count++;
    }

    return NOMISTAKE;
}

int ListDumpCtorFrEdge (struct lists* lst)
{
    LISTS_CHECK 
    
    int point1 = abs (lst->free);
    int point2 = abs (lst->lists[point1].next);

    while (point2 != 0)
    {
        DotEdgeCtor (point1, point2, "none", "cyan3");
        
        point1 = point2;
        point2 = abs (lst->lists[point1].next);
    }

    LISTS_CHECK 
    
    return NOMISTAKE;
}


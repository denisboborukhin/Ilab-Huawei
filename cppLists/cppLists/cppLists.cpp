#include "cppLists.h"

#ifdef STR
    typedef const char* ElemType;

    const char*     INITIAL     =     "fict";
    const char*     DESTROYED   =     "dest";
#endif

#ifdef INT
    typedef int ElemType;

    const int       INITIAL     =     111111;
    const int       DESTROYED   =      -4942;
#endif

#ifdef DOUBLE
    typedef double ElemType;

    double          INITIAL     =     111111;
    double          DESTROYED   =      -7234;
#endif


CLists::CLists () :
    fictElem_ (new item),
    size_ (0)
    {
        //Type_ = CheckType (type);

        fictElem_->data = INITIAL;

       	fictElem_->next = fictElem_;
		fictElem_->prev = fictElem_;

        this->ListOk_();        
	}
/*
NumType CheckType (const char* type)
{
    if (strcmp (type, "INT"))
        return INT;
    if (strcmp (type, "DOUBLE"))
        return DOUBLE;

    return MIS;
}*/

CLists::~CLists ()
{
    this->ListOk_();        

    item* workItem = fictElem_->next;
	item* nextItem = NULL;

	for (int i = 0; i < size_; i++)
	{
		nextItem = workItem->next;

		workItem->data =   DESTROYED;
		workItem->next =        NULL;
		workItem->prev =        NULL;

		delete[] workItem;

		workItem = nextItem;
	}

	delete[] workItem;

	size_ = DESTROYSZ;
}

int CLists::ListInsert (ElemType data, int num)
{
    this->ListOk_();        

    assert (this);
	assert (num > 0);

	if (num > size_ + 1)
		num = size_ + 1;

	item* nextElem = fictElem_->next;

	for (int index = 1; index < num; index++)
		nextElem = nextElem->next;

	item* newElem = new item;
	
	newElem->next = nextElem;
	newElem->prev = nextElem->prev;
	nextElem->prev->next = newElem;
	nextElem->prev = newElem;

	newElem->data = data;

	size_++;

	return this->ListOk_ ();
}

int CLists::ListInsertHead (ElemType data)
{
    return CLists::ListInsert (data, 1);
}

int CLists::ListInsertTail (ElemType data)
{
    return CLists::ListInsert (data, size_ + 1);
}

int CLists::ListDelete (int num)
{
    this->ListOk_ ();

	assert (this);
	assert (num > 0);
    
    if (size_ == 0)
    {
        printf ("WARNING!!! Delete from void lists\n");
        return this->ListOk_ ();
    }

	if (num > size_)
		num = size_;

	item* workElem = fictElem_->next;

	for (int index = 1; index < num; index++)
		workElem = workElem->next;

	item* nextElem = workElem->next;
	item* prevElem = workElem->prev;

	workElem->data = DESTROYED;
	workElem->next = NULL;
	workElem->prev = NULL;

	delete[] workElem;

	nextElem->prev = prevElem;
	prevElem->next = nextElem;

    size_--;

	return this->ListOk_ ();
}

int CLists::ListDeleteTail ()
{
    return CLists::ListDelete (size_);
}

int CLists::ListDeleteHead ()
{
    return CLists::ListDelete (1);
}

int CLists::FoundElem (ElemType data)
{
    this->ListOk_ ();

    struct item* nextElem = fictElem_->next;

    for (int index = 0; index < size_; index++)
    {
        #ifdef STR
        if (!strcmp (nextElem->data, data))
            return ++index;
        #endif

        #ifndef STR
        if (nextElem->data == data)                 
            return ++index;
        #endif

        nextElem = nextElem->next;
    }
    
    this->ListOk_ ();

    return NOTFOUND;
}

struct item* CLists::FoundPtrElem (ElemType data)
{
    this->ListOk_ ();

    struct item* nextElem = fictElem_->next;

    for (int index = 0; index < size_; index++)
    {
        #ifdef STR
        if (!strcmp (nextElem->data, data))
            return nextElem;
        #endif

        #ifndef STR
        if (nextElem->data == data)                 
            return nextElem;
        #endif

        nextElem = nextElem->next;
    }
    
    this->ListOk_ ();

    return nullptr;
}

int CLists::ListOk_ ()
{
    int ERROR = 0;

    if (size_ < 0)
    {
        printf ("ERROR!!! Incorrect size\n");
        ERROR = MISTAKE;
    }

    assert (!ERROR);

    return NOMISTAKE;
}

int CLists::ListDump ()
{
    item* nextElem = fictElem_->next;
   
    DotElemCtor (fictElem_, fictElem_->data, fictElem_->next, fictElem_->prev, "record", "grey");

    for (int i = 0; i < size_; i++)
    {
        DotElemCtor (nextElem, nextElem->data, nextElem->next, nextElem->prev);

        nextElem = nextElem->next;
    }

    nextElem = nextElem->next;

    DotEdgeCtor (fictElem_, fictElem_->next);

    for (int j = 0; j < size_ - 1; j++)
    {
        DotEdgeCtor (nextElem, nextElem->next);

        nextElem = nextElem->next;
    }    

	return NOMISTAKE;
}

#include "hashTable.h"

CHashTbl::CHashTbl (int size) :
    lists_ (new CLists[size]),
    size_ (size)
{}

CHashTbl::~CHashTbl ()
{
    delete[] lists_;
    size_ = DESTROYSZ;
}

int CHashTbl::dump ()
{
    HashOk_ ();

    DotCtor ();

    for (int i = 0; i < size_; i++)
        lists_[i].ListDump (); 

    DotEnd ();

    return HashOk_ ();
}

int CHashTbl::insert (ElemType data)
{
    HashOk_ ();

    #ifdef STR
    int index = Hash_ ((const char*) data, (int) strlen (data));
    
    #else
    int index = Hash_ ((const char*) &data, sizeof (data));
    
    #endif

    struct item* elem = lists_[index].FoundPtrElem (data);

    if (elem != nullptr)
    {   
        elem->counter++; 

        return NOMISTAKE;                       
    }

    lists_[index].ListInsertHead (data);

    elem = lists_[index].FoundPtrElem (data);
    elem->counter = 1;

    return HashOk_ ();
}

int CHashTbl::del (ElemType data)
{
    HashOk_ ();

    #ifdef STR
    int index = Hash_ ((const char*) data, (int) strlen (data));
    
    #else
    int index = Hash_ ((const char*) &data, sizeof (data));
    
    #endif

    int position = lists_[index].FoundElem (data);
    
    if (position == NOTFOUND)
    {
        printf ("Element ");
        printf (ELEM_FMT, data);
        printf ("not found\n");

        return NOMISTAKE;
    }
    
    lists_[index].ListDelete (position); 

    return HashOk_ ();
}

int CHashTbl::countElem (ElemType data)
{
    HashOk_ ();

    #ifdef STR
    int index = Hash_ ((const char*) data, (int) strlen (data));
    
    #else
    int index = Hash_ ((const char*) &data, sizeof (data));
    
    #endif

    struct item* elem = lists_[index].FoundPtrElem (data);

    if (elem != nullptr)
        return elem->counter;                       
    
    HashOk_ ();

    return 0;
}

int CHashTbl::HashOk_ ()
{
    int ERRORS = NOMISTAKE;

    if (size_ < 0)
    {
        printf ("ERROR!!! Incorrect size\n");

        ERRORS |= MISTAKE;
    }

    assert (ERRORS == NOMISTAKE);

    return ERRORS;
}

int CHashTbl::Hash_ (const char* key, unsigned int len)
{
  const unsigned int m      = 0x5bd1e995;
  const unsigned int seed   = 0;
  const int r = 24;

  unsigned int h = seed ^ len;

  const unsigned char* data = (const unsigned char*) key;
  unsigned int k = 0;

  while (len >= 4)
  {
      k  = data[0];
      k |= data[1] << 8;
      k |= data[2] << 16;
      k |= data[3] << 24;

      k *= m;
      k ^= k >> r;
      k *= m;

      h *= m;
      h ^= k;

      data += 4;
      len  -= 4;
  }

  switch (len)
  {
    case 3:
      h ^= data[2] << 16;
      break;

    case 2:
      h ^= data[1] << 8;
      break;

    case 1:
      h ^= data[0];
      h *= m;
      break;

    case 0:
      break;

    default:
      printf ("HASH ERROR!!!\n");
      break;
  };

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h % size_;
}

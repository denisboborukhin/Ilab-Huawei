#include <stdio.h>
#include "cppLists/cppLists.h"

//--------------------------------------------------------------------------------
//-----------------------Example-for-string---------------------------------------
#ifdef STR
int main ()
{
	DotCtor ();

	CLists l1;

	l1.ListInsertHead ("first");
	l1.ListInsert ("second", 2);
	l1.ListInsert ("third", 4);
	l1.ListInsertHead ("first first");
	l1.ListInsertTail ("last last last");

	l1.ListDelete (2);
	
	printf ("second on the position: %d\n", l1.FoundElem ("second"));

	l1.ListDump ();

	CLists l2;

	l2.ListInsertTail ("a");
	l2.ListInsertHead ("b");
	l2.ListInsert ("c", 12);

	l2.ListDump ();

	DotEnd ();
}
#endif
//--------------------------------------------------------------------------------
//-----------------------Example-for-string---------------------------------------
#ifdef INT
int main ()
{
	DotCtor ();

	CLists l1;

	l1.ListInsert (10, 1);
	l1.ListInsertHead (15);
	l1.ListInsert (20, 4);
	l1.ListInsert (25, 2);
	l1.ListInsert (30, 3);
	l1.ListInsert (35, 5);
	l1.ListInsertHead (40);
	l1.ListInsertTail (45);
	
	l1.ListDelete (6);
	l1.ListDeleteTail ();

	printf ("20 on the position: %d\n", l1.FoundElem (20));
	printf ("adress: %p\n", l1.FoundPtrElem (20));

	l1.ListDump ();

	CLists l2;

	l2.ListInsert (12, 1);
	l2.ListInsertTail (48);

	l2.ListDump ();

	DotEnd ();
 
	return 0;
}
#endif

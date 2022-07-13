#include <stdio.h>

#include "akinator/akinator.h"

int main ()
{
//    printf ("started\n");
/*
    CTree t1;

    t1.addItm (nullptr, "Животное?");

    //t1.addItm (t1.findItm ("Животное?"), "кот");
    t1.addItm (t1.findItm ("Животное?"), "Ффффффачитт?");
    t1.addItm (t1.findItm ("Ффффффачитт?"), "Ммммммлад?");

    t1.addItm (t1.findItm ("Ммммммлад?"), "U          ");
    t1.addItm (t1.findItm ("Ммммммлад?"), "T           ");
   
    t1.addItm (t1.findItm ("Ффффффачитт?"), "P                ");

*/
    //FILE* file = fopen ("dump/treeListing.txt", "w");

   // CtorTreeListing (file, t1.findItm ("Животное?"));

    CTree t1 = CtorTreeFromFile ("dump/treeListing.txt");

    //t1.graphDump ();

    Akinator (t1.root ());

    FILE* file = fopen ("dump/treeListing.txt", "w");

    CtorTreeListing (file, t1.root ());

    fclose (file);

    t1.graphDump ();

    return 0;
}

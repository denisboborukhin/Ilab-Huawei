#ifndef GRAPHVIZ
#define GRAPHVIZ

#include <stdio.h>
#include <stdlib.h>

void    DotCtor         (const char* rankdir, const char *color);

void    DotElemCtor     (int i, int data = 0, int next = 0, int prev = 0, 
        const char* shape = "record", const char* color = "darkslategray1",
        const char* label = "elem", const char* style = "filled");
void    DotInfoElemCtor (int capacity, int size, int head, int tail, 
        int free, int statLin, const char* shape = "record", 
        const char* color = "darksalmon", const char* style = "filled");

void    DotEdgeCtor     (int num1, int num2, const char* style = "none", const char* color = "none");   
void    DotPrintf       (const char* text, int num = -1);
void    DotEnd          (void);   
#endif

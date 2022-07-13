#include "graphviz.h"

static FILE* dotFile = fopen ("dump/dot.dot", "w");

void DotCtor (const char* rankdir, const char* color)
{
    fprintf (dotFile, "digraph\n{\n");
    
    fprintf (dotFile, "\trankdir=%s;\n", rankdir);
    
    fprintf (dotFile, "\tgraph[bgcolor=darkseagreen2];\n");

    fprintf (dotFile, "\tnode[color=%s, fontsize = 8];\n", color);
}

void DotElemCtor (int index, int data, int next, int prev, const char* shape, 
        const char* color, const char* label, const char* style)
{
    fprintf (dotFile, "\t%s%d[shape=%s, ", label, index, shape); 
    fprintf (dotFile, "label=\"addres\\n%4d|<data> data\\n%4d|{<next>next:%4d|<prev>prev:%4d}\", ", 
            index, data, next, prev);
    fprintf (dotFile, "fillcolor=\"%s\", style=%s];\n", color, style);
}

void DotInfoElemCtor (int capacity, int size, int head, int tail, int free, int statLin, 
        const char* shape, const char* color, const char* style)
{
    fprintf (dotFile, "\t%s[shape=%s, ", "info", shape); 
    fprintf (dotFile, "label=\"Lists info|capacity:%4d|size:%4d|head:%4d|tail:%4d|free:%4d|statLin:%4d\", ", 
        capacity, size, head, tail, free, statLin);
    fprintf (dotFile, "fillcolor=\"%s\", style=%s];\n", color, style);
}

void DotEdgeCtor (int index1, int index2, const char* style, const char* color)
{
    fprintf (dotFile, "\telem%d-> elem%d[style=%s, color=\"%s\"];\n", 
            index1, index2, style, color);
}

void DotPrintf (const char* text, int num)
{
    fprintf (dotFile, "%s", text);

    if (num != -1)
        fprintf (dotFile, "%d", num);
}

void DotEnd (void)
{   
    fprintf (dotFile, "}\n\n");

    fclose (dotFile);

    system ("dot dump/dot.dot  -q -Tpng -o dump/dump.png");
    system ("rm  dump/dot.dot");
}

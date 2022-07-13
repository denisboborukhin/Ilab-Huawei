#include "FormatFile.h"


int FormFile(const char* nameIn, const char* nameOut)
{
    FILE* file = fopen(nameIn, "r");
    assert (file != NULL);

    FILE* formFile = fopen(nameOut, "w");
    assert (formFile != NULL);

    int c = fgetc(file);
    bool outOfStr = false;

    while (c != EOF)
    {
        if (CheckCorrect(c))
            c = OutputSymbol(file, formFile, &outOfStr, c);
        else
            c = fgetc(file);
    }

    assert (fclose(formFile) == 0);
    assert (fclose(file) == 0);

    return 0;
}

bool CheckCorrect(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '\n') || (c == ' ') || (c == '\t'))
        return true;
    else
        return false;
}

int OutputSymbol(FILE* file, FILE* formFile, bool* outOfStr, int c)
{
    if (*outOfStr)
        return ElemOut(file, formFile, outOfStr, c);

    else
        return ElemIn(file, formFile, outOfStr, c);
}

int ElemOut(FILE* file, FILE* formFile, bool* outOfStr, int c)
{
    if ((c != ' ') && (c != '\n'))
    {
        fputc(c, formFile);
        *outOfStr = false;

        return fgetc(file);
    }

    else
        return fgetc(file);
}

int ElemIn(FILE* file, FILE* formFile, bool* outOfStr, int c)
{
    if (c == '\n')
    {
        fputc(c, formFile);
        *outOfStr = true;

        return fgetc(file);
    }

    else if (c == ' ')
    {
        int t = fgetc(file);

        if ((t != '\n') && (t != ' '))
            fputc(c, formFile);

        return t;
    }

    else
    {
        fputc(c, formFile);

        return fgetc(file);
    }
}

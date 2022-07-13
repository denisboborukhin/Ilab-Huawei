#include "akinator.h"

int Akinator (item* node)
{
    printf ("Загадайте вид растения, а я попробую отгадать\n");
    printf ("Для ответов на мои вопросы используйте (y / n)\n");
    printf ("Загадали?\n");

    char* str = new char[MAXANSWSIZE];
    
    int gameStatus = WhileForTheGame (node, str);

    while (gameStatus != ENDGAME)
    {
        printf ("Хотите сыграть ещё раз?\n");
        gameStatus = WhileForTheGame (node, str);
    }
     
    return NOMISTAKE;
}

int WhileForTheGame (item* node, char* str)
{
    int STARTFLAG = 0;

    while (true)                        //пока не начнем игру
    {  
        ScanAnswer (str);

        switch (CheckAnswer (str))
        {
            case YES:
            {
                printf ("Давайте начнём\n");
                
                STARTFLAG = 1;
                break;
            }

            case NO:
            {
                printf ("Хорошо, давайте в другой раз...\n");
                printf ("До встречи!\n");

                delete[] str;
                return ENDGAME;
            }

            case NOTANSW:
            {
                printf ("\"%s\" это не ответ\n", str);
                printf ("Попробуйте еще раз\n");
                
                break;
            }

            default:
            {
                printf ("ERROR!!!\n");
                
                assert (!"ERROR GAME START");
            }
        }  

        if (STARTFLAG)
            break;
    }

    return AkinatorStartGame (node, str);
}

int AkinatorStartGame (item* node, char* str)
{
    printf ("Это %s?\n", node->data);

    while (true)
    {  
        ScanAnswer (str);

        switch (CheckAnswer (str))
        {
            case YES:
            {   
                if (node->right) 
                    return AkinatorStartGame (node->right, str);           
                    
                else
                {
                    printf ("Ура!!!\nЯ угадал\n");
                    return NOMISTAKE;
                }
            }    

            case NO:
            {
                if (node->left) 
                    return AkinatorStartGame (node->left, str);   

                else
                {
                    printf ("Ехххх, не получилось...\n");
                    printf ("Расскажите, что это?\n");
                    AddNewItm (node);

                    return NOMISTAKE;   
                }     
            }        

            case NOTANSW:
            {
                printf ("\"%s\" это не ответ\n", str);
                printf ("Попробуйте еще раз\n");
                
                break;
            }

            default:
            {
                printf ("ERROR!!!\n");
                
                return MISTAKE;
            }
        }  
    }
}

int AddNewItm (item* node)
{
    char* name = new char[MAXANSWSIZE];
    
    ScanAnswer (name);

    printf ("Чем %s отличается от %s? Он..\n", name, node->data);

    char* ability = new char[MAXANSWSIZE];
    ScanAnswer (ability);
    
    printf ("ability: %s\n", ability);

    printf ("Хотите добавить %s в игру?\n", name);

    char* answer = new char[MAXANSWSIZE];
   
    while (true)
    {  
        ScanAnswer (answer);

        switch (CheckAnswer (answer))
        {
            case YES:
            {
                AddItmInTree (node, name, ability);

                delete[] answer;
                return NOMISTAKE;
            }    

            case NO:
            {
                printf ("Хорошо. Спасибо за игру!\n");

                delete[] name;
                delete[] ability;
                delete[] answer;
                return NOMISTAKE;
            }        

            case NOTANSW:
            {
                printf ("\"%s\" это не ответ\n", answer);
                printf ("Попробуйте еще раз\n");
                
                break;
            }

            default:
            {
                printf ("ERROR!!!\n");
                
                assert (!"ERROR!!!");
            }
        }  
    }
}

int AddItmInTree (item* node, char* str, char* ability)
{
    assert (node);   
    
    item* abilItm = new item;
    abilItm->data = ability;

    item* nameItm = new item;
    nameItm->data = str;

    item* parent = node->parent;

    if (!parent)
    {
        printf ("К сожалению сюда добавить нельзя\n");
        return NOMISTAKE;
    }
    else if (node == parent->left)
        parent->left = abilItm;
    else if (node == parent->right)
        parent->right = abilItm;
    else
    {
        printf ("Ошибка добавления\n");
        return MISTAKE;
    }

    abilItm->right  = nameItm;
    abilItm->left   = node;
    node->parent    = abilItm;
    nameItm->parent = abilItm;

    printf ("Уже добавил! Спасибо за игру!\n");

    return NOMISTAKE;
}

answer CheckAnswer (char* str)
{
    if      (!strcasecmp (str, "y")   || !strcasecmp (str, "yes") || !strcasecmp (str, "д")   ||
             !strcasecmp (str, "да")  || !strcasecmp (str, "Y")   || !strcasecmp (str, "Yes") || 
             !strcasecmp (str, "Д")   || !strcasecmp (str, "Да")) 
        return YES;
    
    else if (!strcasecmp (str, "n")   || !strcasecmp (str, "no")  || !strcasecmp (str, "н")   ||
             !strcasecmp (str, "нет") || !strcasecmp (str, "N")   || !strcasecmp (str, "No") || 
             !strcasecmp (str, "Н")   || !strcasecmp (str, "Нет")) 
        return NO;
    
    else
        return NOTANSW;
}

char* ScanAnswer (char* str)
{
    int symb = getc (stdin);
    int len  = 0;

    while ((symb != '\n') && (len < MAXANSWSIZE - 1))
    {
        if (symb == '\b')
        {
            printf ("забил..\n");
            len--;
            symb = getc (stdin);

            continue;
        }

        *(str + len) = (char) symb;
        len++;
        symb = getc (stdin);
    }

    if (len == MAXANSWSIZE - 1)
    {
        CleanBuf ();
        printf ("Ошибка ввода\n");
        printf ("Попробуйте еще раз\n");
        
        ScanAnswer (str);
    }

    str[len] = '\0';
    //printf ("считал: %s\n", str);
    
/*
    if (!fgets (str, MAXANSWSIZE, stdin))
    {
        printf ("Ошибка ввода\n");
        printf ("Попробуйте еще раз\n");

        ScanAnswer (str);
    }

    char* pos = strchr (str, '\n');

    if (!pos)
    {
        printf ("Ошибка ввода\n");
        printf ("Слишком длинный ответ\n");
        printf ("Попробуйте еще раз\n");
        
        CleanBuf ();
        
        ScanAnswer (str);
    }
    else
        *pos = '\0';
*/
    return str;
}

void CleanBuf ()
{
    int symb = 0;

    symb = getchar ();

    while (symb != '\n')
        symb = getchar ();
}

CTree CtorTreeFromFile (const char* fileName)
{
    assert (fileName); 

    int sizeBuf = (int) GetSizeBuf (fileName);
    char* buffer = CreateBuf (&sizeBuf, fileName);

    CTree tree;
    int index = 0;
    struct item* node = nullptr;


    while ((index < sizeBuf) && (*(buffer + index) != '\0'))
    {
        if (*(buffer + index) == '{')
        { 
            node = tree.addItm (nullptr, buffer + index + 1);
            node->data = buffer + index + 1;
            tree.addBuffer (buffer);            
        }

        if (*(buffer + index) == '}')
            return tree; 

        index++;
    }
    index++;

    if (!node)
    {
        printf ("Empty tree\n");
        return tree;
    }

    node->left  = CtorItmFromFile (node, buffer, &index, sizeBuf);
    node->right = CtorItmFromFile (node, buffer, &index, sizeBuf);

    return tree;
}

item* CtorItmFromFile (item* node, char* buffer, int* index, int sizeBuf)
{ 
    assert (buffer);
    assert (index);
    assert (*index  >= 0);
    assert (sizeBuf >= 0);

    item* newNode = nullptr;

    while ((*index < sizeBuf) && (*(buffer + *index) != '\0'))
    {
        if ((*(buffer + *index) == '{'))
        {
            if (*(buffer + *index + 1) != '}')
            {
                newNode = new item;
                
                newNode->parent = node;
                newNode->data = buffer + *index + 1;
            }
            else
            {
                *index += 2;
                return newNode;
            }
        }

        if (*(buffer + *index) == '}')
        {
            *(buffer + *index) = '\0';
            *index += 2;

            return newNode; 
        }
        
        (*index)++;
    }
    (*index)++;

    if (newNode)
    {
        newNode->left  = CtorItmFromFile (newNode, buffer, index, sizeBuf);       
        newNode->right = CtorItmFromFile (newNode, buffer, index, sizeBuf);
    }
    
    while (*(buffer + *index) != '}')
        (*index)++;
    *index += 2;

    return newNode;
}

int CtorTreeListing (FILE* file, struct item* root, int* count)
{
    assert (file);
    assert (root);

    if (!count)
    {
        count = new int;
        *count = 0;
    }

    fprintf (file, "%*s", *count * 4 + 1, "{");
    (*count)++;
    fprintf (file, "%s", root->data);
    //printf ("%s\n", root->data);

    if ((root->left) || (root->right))
    {
        fprintf (file, "\n");

        if (root->left)
        {   
            CtorTreeListing (file, root->left, count);

            if (!(root->right))
                fprintf (file, "%*s", *count * 4 + 3, "{}\n"); 
        }
        
        if (root->right)
        {
            if (!(root->left))
                fprintf (file, "%*s", *count * 4 + 3, "{}\n"); 
            
            CtorTreeListing (file, root->right, count);
        }
    } 
    
    if (!(root->left) && !(root->right))
        fprintf (file, "}\n");

    else
        fprintf (file, "%*s\n", (*count - 1) * 4 + 1, "}");
    
    (*count)--;

    return NOMISTAKE;
}

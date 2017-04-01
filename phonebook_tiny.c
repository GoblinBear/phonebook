#include <stdlib.h>
#include <string.h>

#include "phonebook_tiny.h"

Tiny* create_Tiny()
{
    Tiny* tiny = (Tiny*)malloc(sizeof(Tiny));
    if (tiny == NULL) {
        return NULL;
    }

    tiny->findName = Tiny_findName;
    tiny->append = Tiny_append;
    strcpy(tiny->output, "tiny.txt");

    return tiny;
}

void delete_Tiny(Tiny* tiny)
{
    free(tiny);
    tiny = NULL;
}

void *Tiny_findName(char lastName[], void *pHead)
{ 
    tiny_entry* sHead = (tiny_entry*)pHead;

    while (sHead) {
        if (strcasecmp(lastName, sHead->lastName) == 0)
            return sHead;
        sHead = sHead->pNext;
    }
    return NULL;
}

void *Tiny_append(char lastName[], void *e)
{
    tiny_entry* se = (tiny_entry*)e;

    se->pNext = (tiny_entry *) malloc(sizeof(tiny_entry));
    se = se->pNext;
    strcpy(se->lastName, lastName);
    se->pNext = NULL;

    return se;
}

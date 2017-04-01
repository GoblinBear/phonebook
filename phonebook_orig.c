#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_orig.h"

Orig* create_Orig()
{
    Orig* orig = (Orig*)malloc(sizeof(Orig));
    if (orig == NULL) {
        return NULL;
    }

    orig->findName = Orig_findName;
    orig->append = Orig_append;
    strcpy(orig->output, "orig.txt");

    return orig;
}

void delete_Orig(Orig* orig)
{
    free(orig);
    orig = NULL;
}

void *Orig_findName(char lastName[], void *pHead)
{
    entry* sHead = (entry*)pHead;

    while (sHead) {
        if (strcasecmp(lastName, sHead->lastName) == 0)
            return sHead;
        sHead = sHead->pNext;
    }
    return NULL;
}

void *Orig_append(char lastName[], void *e)
{
    entry* se = (entry*)e;

    se->pNext = (entry *) malloc(sizeof(entry));
    se = se->pNext;
    strcpy(se->lastName, lastName);
    se->pNext = NULL;

    return se;
}

#ifndef _PHONEBOOK_ORIG_H
#define _PHONEBOOK_ORIG_H

#include "module.h"

typedef struct _Orig {
    ModuleMembers();
} Orig;

Orig* create_Orig();
void delete_Orig(Orig* orig);

void *Orig_findName(char lastName[], void *pHead);
void *Orig_append(char lastName[], void *e);

#endif

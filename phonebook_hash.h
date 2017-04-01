#ifndef _PHONEBOOK_HASH_H
#define _PHONEBOOK_HASH_H

#include "module.h"

typedef struct _Hash {
    ModuleMembers();
} Hash;

Hash* create_Hash();
void delete_Hash(Hash* hash);

void *Hash_findName(char lastName[], void *pHead);
void *Hash_append(char lastName[], void *e);

#endif

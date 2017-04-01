#ifndef _PHONEBOOK_TINY_H
#define _PHONEBOOK_TINY_H

#include "module.h"

typedef struct __PHONE_BOOK_DETAIL {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detail;

typedef struct __PHONE_BOOK_TINY_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    detail *d;
    struct __PHONE_BOOK_TINY_ENTRY *pNext;
} tiny_entry;

typedef struct _Tiny {
    ModuleMembers();
} Tiny;

Tiny* create_Tiny();
void delete_Tiny(Tiny* tiny);

void *Tiny_findName(char lastName[], void *pHead);
void *Tiny_append(char lastName[], void *e);

#endif

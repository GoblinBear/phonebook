#ifndef _MODULE_H
#define _MODULE_H

#define MAX_LAST_NAME_SIZE 16

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

#define ModuleMembers() \
            void *(*findName)(char lastName[], void *pHead); \
            void *(*append)(char lastName[], void *e); \
            char output[16];

typedef struct _Module {
    ModuleMembers();
} Module;


#endif
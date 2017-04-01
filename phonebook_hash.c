#include <stdlib.h>
#include <string.h>

#include "phonebook_hash.h"

typedef struct hashtable_s {
    int size;
    struct __PHONE_BOOK_ENTRY** table;
} hashtable_t;

static hashtable_t* ht_create(int size)
{
    hashtable_t* hashtable = NULL;
    int i;

    if (size < 1) {
        return NULL;
    }

    if ((hashtable = malloc(sizeof(hashtable_t))) == NULL) {
        return NULL;
    }

    if ((hashtable->table = malloc(sizeof(entry*)*size)) == NULL) {
        return NULL;
    }

    for (i = 0; i < size; i++) {
        hashtable->table[i] = NULL;
    }

    hashtable->size = size;
    return hashtable;
}

static unsigned long int ht_hash(hashtable_t* hashtable, char* key)
{
    unsigned long int hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % hashtable->size;
}

static entry* ht_newpair(char* key)
{
    entry* newpair;

    if ((newpair = malloc(sizeof(entry))) == NULL) {
        return NULL;
    }

    if (strcpy(newpair->lastName, key) == NULL) {
        return NULL;
    }

    newpair->pNext = NULL;
    return newpair;
}

static void ht_set(hashtable_t* hashtable, char* key)
{
    int bin = 0;
    entry* newpair = NULL;
    entry* next = NULL;
    entry* last = NULL;

    bin = ht_hash(hashtable, key);
    next = hashtable->table[bin];

    while (next && next->lastName && strcmp(key, next->lastName) > 0) {
        last = next;
        next = next->pNext;
    }

    if (next && next->lastName && !strcmp(key, next->lastName)) {
        strcpy(next->lastName, key);
    }
    else {
        newpair = ht_newpair(key);

        if (next == hashtable->table[bin]) {
            newpair->pNext = next;
            hashtable->table[bin] = newpair;
        }
        else if (next == NULL) {
            last->pNext = newpair;
        }
        else {
            newpair->pNext = next;
            last->pNext = newpair;
        }
    }
}

static char* ht_get(hashtable_t* hashtable, char* key)
{
    int bin = 0;
    entry* pair;

    bin = ht_hash(hashtable,key);

    pair = hashtable->table[bin];
    while (pair && pair->lastName && strcmp(key, pair->lastName) > 0) {
        pair = pair->pNext;
    }

    if (pair == NULL || pair->lastName == NULL || strcmp(key, pair->lastName)) {
        return NULL;
    }
    else {
        return pair->lastName;
    }
}


hashtable_t *hashtable;

Hash* create_Hash()
{
    Hash* hash = (Hash*)malloc(sizeof(Hash));
    if (hash == NULL) {
        return NULL;
    }

    hash->findName = Hash_findName;
    hash->append = Hash_append;
    strcpy(hash->output, "hash.txt");

    hashtable = ht_create( 42737 );

    return hash;
}

void delete_Hash(Hash* hash)
{
    free(hash);
    hash = NULL;
}

void *Hash_findName(char lastName[], void *pHead)
{
    return ht_get(hashtable, lastName);
}

void *Hash_append(char lastName[], void *e)
{
    ht_set(hashtable, lastName);

    return NULL;
}

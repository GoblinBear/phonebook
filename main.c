#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "phonebook_orig.h"
#include "phonebook_tiny.h"
#include "phonebook_hash.h"

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    int num;
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* Choose version */
    Orig* orig = create_Orig();
    Tiny* tiny = create_Tiny();
    Hash* hash = create_Hash();
    Module *list[] = { (Module*)orig, (Module*)tiny, (Module*)hash };

    num = atoi(argv[1]);
    Module *module = list[num];
    
    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    /* build the entry */
    void *pHead, *e;
    if (num == 1) {
        pHead = (tiny_entry *) malloc(sizeof(tiny_entry));
        printf("size of tiny_entry : %lu bytes\n", sizeof(tiny_entry));
        e = pHead;
        ((tiny_entry*)e)->pNext = NULL;
    }
    else {
        pHead = (entry *) malloc(sizeof(entry));
        printf("size of entry : %lu bytes\n", sizeof(entry));
        e = pHead;
        ((entry*)e)->pNext = NULL;
    }

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif

    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        e = module->append(line, e);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);

    e = pHead;

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
    e = pHead;
    
    assert(module->findName(input, e));
    if (num == 1) {
        assert(0 == strcmp(((tiny_entry*)module->findName(input, e))->lastName, "zyxel"));
    }
    else {
        assert(0 == strcmp(((entry*)module->findName(input, e))->lastName, "zyxel"));
    }

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif

    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    module->findName(input, e);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    FILE *output;
    output = fopen(module->output, "a");

    fprintf(output, "append() findName() %.9lf %.9lf\n", cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %.9lf sec\n", cpu_time1);
    printf("execution time of findName() : %.9lf sec\n", cpu_time2);

    free(pHead);

    return 0;
}

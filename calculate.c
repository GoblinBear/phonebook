#include <stdio.h>
#include <stdlib.h>

char append[50];
char find[50];

typedef struct _Sum{
    double sum_a;
    double sum_f;
} Sum;

Sum* calculate(char* filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("ERROR opening input file orig.txt\n");
        exit(0);
    }
    int i = 0;
    double orig_sum_a = 0.0, orig_sum_f = 0.0, orig_a, orig_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find, &orig_a, &orig_f);
        orig_sum_a += orig_a;
        orig_sum_f += orig_f;
    }
    fclose(fp);

    Sum* sum = (Sum*)malloc(sizeof(Sum));
    sum->sum_a = orig_sum_a;
    sum->sum_f = orig_sum_f;

    return sum;
}

int main(int argc, char *argv[])
{
    int i;

    Sum* sum = (Sum*)malloc(sizeof(Sum) * (argc-1));
    for (i = 0; i < argc-1; i++) {
        sum[i] = *calculate(argv[i+1]);
    }

    FILE *output = fopen("output.txt", "w");

    fprintf(output, "append() ");
    for (i = 0; i < argc-1; i++) {
        fprintf(output, "%.9lf ", sum[i].sum_a / 100.0);
    }
    fprintf(output, "\n");

    fprintf(output, "findName() ");
    for (i = 0; i < argc-1; i++) {
        fprintf(output, "%.9lf ", sum[i].sum_f / 100.0);
    }
    fprintf(output, "\n");

    fclose(output);
    return 0;
}

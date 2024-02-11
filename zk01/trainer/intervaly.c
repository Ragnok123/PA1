#include <stdio.h>
#include <stdlib.h>

typedef struct interval {
    int dolni;
    int horni;
} interval_t;

typedef struct array {
    int size;
    int capacity;
    interval_t * data;
} array_t;

int cmpInterval (const void * a, const void * b) {
    interval_t lhs = *(interval_t*)a;
    interval_t rhs = *(interval_t*)b;
    
    if (lhs.dolni < rhs.dolni) return -1;
    if (lhs.dolni > rhs.dolni) return 1;
    return 0;
}

void arrayInit(array_t * array) {
    array->size = 0;
    array->capacity = 5;
    array->data = (interval_t*) malloc(array->capacity * sizeof(interval_t));
}

void freeArray (array_t * array) {
    free(array->data);
}

void arrayAppend (array_t * array, interval_t dat) {
    if (array->size + 1 == array->capacity) {
        array->capacity *= 2;
        array->data = (interval_t*) realloc(array->data, array->capacity * sizeof(interval_t));
    }
    array->data[array->size] = dat;
    array->size++;
}

void loadInterval (int lower, int upper, interval_t * interval) {
    interval->dolni = lower;
    interval->horni = upper;
}

int loadData(array_t * array) {
    printf("Zadejte intervaly:\n");
    int lo, hi;
    char tester;
    interval_t inter;
    while (1) {
        int scan = scanf (" [ %d, %d %c", &lo, &hi, &tester);
        if (scan == EOF) 
            return 2;
        if (tester != ']') {
            printf("12Nespravny vstup.\n");
            return 0;
        }
        if (scan != 3) {
            printf ("%d\n", scan);
            printf ("%d%d%c\n", lo, hi, tester);
            printf("3Nespravny vstup.\n");
            return 0;
        }
        if (lo > hi) {
            //printf("Nespravny vstup;\n");
            return 0;
        }
        loadInterval (lo, hi, &inter);
        arrayAppend(array, inter);
    }
}

int countIntervals (array_t * array) {
    int count = 0;
    int highest = array->data[0].horni;
    for (int i = 0; i <= array->size; i++) {
        if (array->data[i].dolni < highest) {
            if (array->data[i].horni < highest)
                continue;
            if (i == 0) {
                count = array->data[i].horni - array->data[i].dolni;
                continue;
            }
            count = count + array->data[i].horni - highest;
            highest = array->data[i].horni;
        }
        else {
            count = count + array->data[i].horni - array->data[i].dolni;
            highest = array->data[i].horni;
        }
        //printf("c: %d\n", count);

    }
    return count;
}

int main () {
    array_t arr;
    arrayInit(&arr);
    if (!loadData(&arr)) {
        printf("Nespravny vstup\n");
        freeArray(&arr);
        return 1;
    }

   /* for (int i = 0; i < 6; i++) {
        printf("%d %d\n", arr.data[i].dolni, arr.data[i].horni);
    }*/
    qsort(arr.data, arr.size, sizeof(interval_t), cmpInterval);
    /*for (int i = 0; i < 5; i++) {
        printf("%d %d\n", arr.data[i].dolni, arr.data[i].horni);
    }*/

    int cnt = countIntervals(&arr);
    freeArray(&arr);

    printf ("Celkova delka intervalu: %d\n", cnt);
    return 0;
}

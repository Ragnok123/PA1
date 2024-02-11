#include <stdio.h>
#include <stdlib.h>

typedef struct kostka {
    int lower;
    int higher;
    int count;
} kostka_t;

typedef struct array {
    int size;
    int capacity;
    kostka_t * data;
} array_t;

int cmpKostka (const void* a, const void* b) {
    kostka_t lhs = *(kostka_t*)a;
    kostka_t rhs = *(kostka_t*)b;

    if (lhs.lower < rhs.lower) return -1;
    if (lhs.lower > rhs.lower) return 1;
    return 0;
}

void arrayInit (array_t * array) {
    array->size = 0;
    array->capacity = 5;
    array->data = (kostka_t*) malloc(array->capacity * sizeof(kostka_t));
}

void freeArray (array_t * array) {
    free(array->data);
}

void loadKostka (int low, int high, kostka_t * kostka) {
    kostka->lower = low;
    kostka->higher = high;
    kostka->count = 1;
}

void appendArray (array_t * array, kostka_t dat) {
    if (array->size + 1 == array->capacity) {
        array->capacity *= 2;
        array->data = (kostka_t*) realloc(array->data, array->capacity * sizeof(kostka_t));
    }
    array->data[array->size] = dat;
    array->size++;
}

int loadData(array_t * array) {
    char tester;
    kostka_t kostka;
    int lo, hi;
    printf("Zadejte kostky:\n");

    while (1) { 
        int scan = scanf(" [ %d | %d %c", &lo, &hi, &tester);

        if (scan == EOF)
            return 2;
        if (tester != ']') 
            return 0;
        if (scan != 3)
            return 0;

        if (lo > hi) {
            loadKostka(hi, lo, &kostka);
        }
        else {
            loadKostka (lo, hi, &kostka);
        }
        appendArray(array, kostka);
        
    }
    return 1;
}

void counting (array_t * array) {
    for (int i = 0; i <= array->size; i++) {
        if (array->data[i].count > 0) {
            for (int j = i + 1; j <= array->size; j++) {
                if (    array->data[j].lower == array->data[i].lower && 
                        array->data[j].higher == array->data[i].higher &&
                        array->data[j].count == 1) {
                    array->data[j].count = 0;
                    array->data[i].count++;
                }
            }
        }
    }
}

void printResults (array_t * array) {
    for (int i = 0; i <= array->size; i++) {
        if (array->data[i].count == 0)
            continue;
        printf("[%d|%d] %dx\n", array->data[i].lower,
                              array->data[i].higher,
                              array->data[i].count);
    }
}

int main () {

    array_t arr;
    arrayInit(&arr);

    if (!loadData(&arr)) {
        printf("Nespravny vstup.\n");
        freeArray(&arr);
        return 1;
    }

    // Test vstupu ok
    /*for (int i = 0; i < 3; i++) {
        printf("%d %d\n", arr.data[i].lower, arr.data[i].higher);
    }*/

    qsort(arr.data, arr.size, sizeof(kostka_t), cmpKostka);

    // Sort ok
    /*for (int i = 0; i < 6; i++) {
        printf("%d %d\n", arr.data[i].lower, arr.data[i].higher);
    }*/

    counting (&arr);

    printResults(&arr);

    freeArray(&arr);
    return 0;
}

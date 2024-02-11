#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char region[11];
}Region;

typedef struct{
    int hodnota;
    int pocet;
    Region * regions;
    size_t rCapacity;
    size_t rSize;
} Plat;

typedef struct{
    size_t aCapacity, aSize;
    Plat * data;
}Array;



int main(){

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char code[101];
    int cetnost;
    int length;
    int firstVyskyt;
} EAN;

typedef struct{
    size_t size, capacity;
    EAN * data;
} Array;


/**
 * chyba to je pokud:
 *  EAN < 5
 *  EAN > 100
*/

Array array_init(){
    Array arr;
    arr.capacity = 16;
    arr.size = 0;
    arr.data = (EAN*)malloc(arr.capacity * sizeof(EAN));
    return arr;
}

void array_free(Array arr){
    free(arr.data);
}

int inArray(Array *arr, EAN ean){
    if(arr->size == 0) return 0;
    for(size_t i = 0; i < arr->size; i++){
        EAN ean2 = arr->data[i];
        if(strcmp(ean.code, ean2.code) == 0){
            return 1;
        }
    }
    return 0;
}

EAN *searchByCode(Array *arr, char pole[]){
    for(size_t i = 0; i < arr->size; i++){
        if(strcmp(arr->data[i].code, pole) == 0){
            return &(arr->data[i]);
        }
    }
    return NULL;
}

void array_push(Array *arr, EAN ean){
    if(arr->size == arr->capacity){
        arr->capacity *= 2;
        arr->data = (EAN*)realloc(arr->data, arr->capacity * sizeof(EAN));
    }
    if(!inArray(arr, ean)){
        arr->data[arr->size++] = ean;
    } else {
        EAN *search = searchByCode(arr, ean.code);
        search->cetnost++;
    }
}

int readEAN(Array *arr){
    int totalVyskyt = 0;
    char *line = NULL;
    size_t capacity = 0;
    int length;
    while((length = getline(&line, &capacity, stdin)) != -1){
        //if(length > 0 && line[length-1] == '\n'){line[length-1]='\0';}
        int wordIndex = 0;
        char pole[101];
        if(length <= 5 || length >= 100) return 0;
        while(line[wordIndex] != '\0'){
            if((line[wordIndex] >= '0' && line[wordIndex] <= '9')){
                pole[wordIndex] = line[wordIndex];
                wordIndex++;
                //printf("Fine\n");
            } else if(line[wordIndex] != '\n'){
                //printf("Err\n");
                //printf("Character id: %i\n", (int)line[wordIndex]);
                return 0;
            } else {
                break;
            }
        }
        pole[wordIndex] = '\0';
        totalVyskyt++;
        EAN ean;
        ean.length = length;
        for(int i = 0; i < wordIndex; i++){
            ean.code[i] = pole[i];
        }
        ean.firstVyskyt = totalVyskyt;
        ean.cetnost = 1;
        array_push(arr, ean);
        wordIndex = 0;
    }
    free(line);
    return 1;
}

void printEAN(Array *arr){
    for(size_t i = 0; i < arr->size; i++){
        EAN ean = arr->data[i];
        printf("EAN: %s\n Cetnost: %i\n, Prvni vyskyt: %i\n", ean.code, ean.cetnost, ean.firstVyskyt);
    }
}

int eCmp(const void* a, const void* b){
    EAN ean1 = *(const EAN*)a;
    EAN ean2 = *(const EAN*)b;

    if(ean1.cetnost > ean2.cetnost){
        return -1;
    } else if(ean1.cetnost < ean2.cetnost){
        return 1;
    } else {
        if(ean1.firstVyskyt < ean2.firstVyskyt){
            return -1;
        } else if(ean1.firstVyskyt > ean2.firstVyskyt){
            return 1;
        }
    }
    return 0;
}

void writeEAN(Array *arr){
    qsort(arr->data, arr->size, sizeof(EAN), eCmp);
    size_t num = 0;
    if(arr->size > 10){
        num = 10;
    } else {
        num = arr->size;
    }
    for(size_t i = 0; i < num; i++){
        printf("%s %ix\n", arr->data[i].code, arr->data[i].cetnost);
    }
}


int main(){
    Array arr = array_init();
    if(!readEAN(&arr)){
        printf("Nespravny vstup.\n");
        array_free(arr);
        return 1;
    }
    writeEAN(&arr);
    array_free(arr);
    return 0;
}
#include <stdio.h>

typedef struct{
    int size, capacity;
    int* data;
} Array;

Array array_init(){
    Array arr;
    arr.size = 0;
    arr.capacity = 1000;
    arr.data = (int*)malloc(arr.capacity * sizeof(int));
}

void array_push(Array *arr, int number){
    if(arr->size >+ arr->capacity){
        arr->capacity *= 4;
        arr->data = (int*)realloc(arr->data, arr->capacity * sizeof(int));
    }
    arr->data[arr->size] = number;
    arr->size++;
}

void array_free(Array array){
    free(array.data);
}

int solveAllPluses(int array[], int index, int length){     //returns number of
    int plusCharacters = length - 2;
    int equalCharacter = length - 1;
}

int solveEquation(int array[], int index, int length){      // returns number of solved equations
    if(index >= length){
        return array[index];
    }
    
    return 0;
}

int main(){
    Array array = array_init();
    int num;
    while(scanf(" %i ", &num) != EOF){
        array_push(&array, num);
    }

    // 1 2 3

    // 1 + 2 = 3
    // celkem: 1

    array_free(array);
    return 0;
}
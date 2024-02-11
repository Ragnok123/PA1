#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *word;
    int length;
    int capacity;
} Word;

typedef struct {
    size_t size, capacity;
    Word* data;
} Array;

void array_init(Array *arr) {
    arr->size = 0;
    arr->capacity = 16;
    arr->data = (Word *)malloc(arr->capacity * sizeof(Word));
}

void array_push(Array *arr, Word word) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = (Word *)realloc(arr->data, arr->capacity * sizeof(Word ));
    }
    arr->data[arr->size] = word;
    arr->size++;
}

void array_free(Array *arr) {
    for (int i = 0; i < arr->size; i++) {
        free(arr->data[i].word);
    }
    free(arr->data);
}

int main(){
    Array array;
    array_init(&array);

    int length;
    int capacity = 16;
    char *buffer = (char*)malloc(sizeof(char));

    int inLoop = 1;
    while(inLoop){
        printf("Zadej vstup:\n");
        length = getline(&buffer, &capacity, stdin);

        for(int i = 0; i < length; i++){
            
        }
    }
    return 0;
}
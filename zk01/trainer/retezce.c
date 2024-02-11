#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int length;
    int order;
    int capacity;
} Word;

typedef struct {
    int size, capacity;
    Word *data;
} Array;

Array ARRAY;

void array_init() {
    ARRAY.size = 0;
    ARRAY.capacity = 16;
    ARRAY.data = (Word *)malloc(ARRAY.capacity * sizeof(Word));
}

void array_push(Array *arr, Word word) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = (Word *)realloc(arr->data, arr->capacity * sizeof(Word ));
    }
    word.order = arr->size;
    arr->data[arr->size] = word;
    arr->size++;
}

void array_free() {
    for (int i = 0; i < ARRAY.size; i++) {
        free(ARRAY.data[i].word);
    }
    free(ARRAY.data);
}

int isAlphabetic(char chr) {
    if ((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z'))
        return 1;
    return 0;
}

Word writeWord(Word word, char chr) {
    if(word.length >= word.capacity){
        word.capacity *= 2;
        word.word = (char*)realloc(word.word, word.capacity * sizeof(char));
    }
    if (isAlphabetic(chr)) {
        word.word[word.length] = chr;
        word.length++;
    } else {
        word.word[word.length] = '\0';
        array_push(&ARRAY, word);
        word.length = 0;
        word.capacity = 16;
        //free(word.word);
        word.word = (char *)malloc(16 * sizeof(char)); // Reset word buffer
    }
    return word;
}

int compareWords(const void *a, const void *b) {
    Word* wordA = (Word*)a;
    Word* wordB = (Word*)b;

    int value;
    int areEquals = strcasecmp(wordA->word, wordB->word);
    if(areEquals == 0){
        if(wordA->order > wordB->order){
            value = 1;
        } else {
            value = -1;
        }
    } else {
        value = areEquals;
    }
    return value;
}

void sortWords(Array *arr){
    qsort(arr->data, arr->size, sizeof(Word), compareWords);
    for(int i = 0; i < arr->size; i++){
        //printf("Array size: %i\n", i);
        printf("  %s\n", arr->data[i].word);
    }
}

int main() {
    int inLoop = 1;

    size_t stringSize = 16;
    char *rawString = (char *)malloc(stringSize * sizeof(char));
    int length;

    array_init(); // Initialize array

    while (inLoop) {
        printf("Zadej retezce:\n");
        length = getline(&rawString, &stringSize, stdin);
        Word newWord;
        newWord.length = 0;
        newWord.capacity = 16;
        newWord.word = (char *)malloc(newWord.capacity * sizeof(char)); // Initialize word buffer
        for (int i = 0; i < length; i++) {
            newWord = writeWord(newWord, rawString[i]);
        }
        printf("Serazene:\n");
        sortWords(&ARRAY);
        if (length <= 1){ // Condition to exit loop when empty string is entered
            inLoop = 0;
        }
    }

    // Free allocated memory
    array_free();
    free(rawString);

    return 0;
}

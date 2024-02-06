#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *word;
    int length;
} Word;

typedef struct{
    int size, capacity;
    Word ** data;
} Array;
Array ARRAY;

typedef struct{
    int size, capacity;
    char * data;
} RawString;

void array_init(){
    ARRAY.size = 0;
    ARRAY.capacity = 16;
    ARRAY.data = (Word**) malloc(ARRAY.capacity * sizeof(Word*));
}

void array_push(Array* arr, Word* word){
    if(arr->size >= arr->capacity){
        arr->capacity *= 2;
        arr->data = (Word**) realloc(arr->data, arr->capacity * sizeof(Word*));
    }
    arr->data[arr->size] = word;
    arr->size++;
}

void array_free(){

}

int isAlphabetic(char chr){
    if((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')) return 1;
    return 0;
}

void writeWord(Word* word, char chr){
    if(isAlphabetic(chr)){
        word->word[word->length] = chr;
        word->length++;
    } else {
        word->word[word->length] = '\0';
        array_push(&ARRAY, word);
        printf("Successfully written word %s\n", word->word);

        word->length = 0;
        free(word->word);
    }
}

int main(){
    int inLoop = 1;

    size_t stringSize = 16;
    char *rawString = (char*) malloc(stringSize * sizeof(char));
    int length;

    while(inLoop){
        printf("Zadej retezce:\n");
        length = getline(&rawString, &stringSize, stdin);
        Word newWord;
        newWord.length = 0;
        newWord.word = (char*)malloc(16*sizeof(char));
        for(int i = 0; i < length; i++){
            writeWord(&newWord, rawString[i]);
        }
    }
    return 0;
}
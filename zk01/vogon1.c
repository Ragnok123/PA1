#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
 
#define MAX_SIZE 100
 
typedef struct TVERSE{
    char verse[MAX_SIZE + 1];
    struct TVERSE * next;
} TVERSE;
 
TVERSE * createVerse(TVERSE * next, const char * verse) {
    TVERSE * newItem = (TVERSE *) malloc(sizeof(TVERSE) );
    newItem->next = next;
    strcpy(newItem->verse, verse);
    return newItem;
}
 
void freeList(TVERSE * item) {
    TVERSE *tmp;
    while (item) {
        tmp = item;
        item = item->next;
        free(tmp);
    }
}

int pSize = 0;
int pCapacity = 16;
int *Pool;

int numericPower(const char *string){
    int num = 0;
    int len = strlen(string);
    for(int i = 0; i < len; i++){
        char ch = tolower(string[i]);
        switch(ch){
            case 'a': 
            case 'b': 
            case 'c': 
            case 'd': 
            case 'e': 
            case 'f': 
            case 'g': 
            case 'h': 
            case 'i': 
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z': num +=1; break;
        }
    }
    return num;
}
// 1 2 3 4 5 6 7 8

// 1 3 6 8
// 2 7
// 4
// 5

// 1
// 2
// 4
// 5

int isDuplicated(const char *string, const TVERSE * list){
    int duplicate = 0;
    int numPower1 = numericPower(string);
    for(const TVERSE * traverse = list; traverse; traverse = traverse->next){
        int numPower2 = numericPower(traverse->verse);
        if(numPower1 == numPower2){
            duplicate += 1;
        }
    }
    return duplicate;
}

int alreadyContains(int pole[], int size, int value){
    for(int i = 0; i < size; i++){
        if(pole[i] == value){
            return 1;
        }
    }
    return 0;
}

TVERSE * vogonPoetry(const TVERSE * list) {
    TVERSE * newNode = NULL;
    const TVERSE * tmp = list;
    int index = 0;
    printf("1 called\n");
    Pool = (int*)malloc(pCapacity* sizeof(int));
    for(; tmp; tmp = tmp->next){
        //printf("2 called");
        Pool[index] = numericPower(tmp->verse);
        printf(" - Verse %i has %i chars\n", index+1, numericPower(tmp->verse));
        index++;
    }
    tmp = list;

    int* Pool2 = (int*)malloc(index * sizeof(int));
    int pool2Idx = 0;

    int *Pool3 = (int*)malloc(index * sizeof(int));
    int size = 0;
    for(int i = 0; i < index; i++){
            // Pool[0] -> Pole
            // Pool[1] = Pool[0] ->
        if(!alreadyContains(Pool2, index, Pool[i])){
            Pool2[pool2Idx++] = Pool[i];        // 1 2 4 5
            Pool3[size++] = i;
            printf("+ Verse[%i]: %i\n", i+1, Pool[i]);
            printf("Pool[%i]: %i\n", size, i+1);
        }
    }

    size = 0;
    index = 0;
    for(; tmp; tmp = tmp->next){
        if(Pool3[size] == index){
            newNode = createVerse(newNode, tmp->verse);
            size++;
        }
        index++;
    }

    free(Pool);
    free(Pool2);
    free(Pool3);
    return newNode;
}

void printTree(TVERSE * tree){
    for(; tree; tree = tree->next){
        printf("%s -> ", tree->verse);
    }
    printf("\n");
}
 
int main() {
    // ---LVL 1---
    printf("LVL 1\n");
    TVERSE * tmp1 = createVerse(createVerse(createVerse(createVerse(createVerse(createVerse(createVerse(createVerse(NULL, "untbugglyOh freddled gr"), "cturations are toThy mi"), "reddled gruntbugglyOh f"), "on a lurgid bee"), "As plurdled gabbleblotchits"), "dled gruntbugglyOh fred"), "Thy micturations are to"), "Oh freddled gruntbuggly");
    TVERSE * lvl1 = vogonPoetry(tmp1);
    printTree(tmp1);
    printTree(lvl1);
 
    // ---LVL 2--- //
    //printf("LVL 2\n");
    TVERSE * tmp2 = createVerse(createVerse(NULL, "seMASjak*666*AhoJ"), "Ahoj, jak se mas");
    //TVERSE * lvl2 = vogonPoetry(tmp2);
 
    //assert(strcmp(lvl2->verse, "Ahoj, jak se mas") == 0
    //       && lvl2->next == NULL );
 
    // ---LVL 3--- //
    //printf("LVL 3\n");
    TVERSE * tmp3 = createVerse(createVerse(createVerse(NULL, "cbacba"), "bbb"), "abcabc");
    //TVERSE * lvl3 = vogonPoetry(tmp3);
 
    //assert(strcmp(lvl3->verse, "abcabc") == 0
    //       && strcmp(lvl3->next->verse, "bbb") == 0
    //       && lvl3->next->next == NULL );
 
    // ---LVL 4--- //
    //printf("LVL 4\n");
    TVERSE * tmp4 = createVerse(createVerse(createVerse(createVerse(createVerse(createVerse(createVerse(NULL, " AA  bbcc"), "bcab  CA"), "abca  BC"), "b aaa"), "aa  ab"), "  *"), "    ");
    //TVERSE * lvl4 = vogonPoetry(tmp4);
 
    //assert(strcmp(lvl4->verse, "    ") == 0
    //       && strcmp(lvl4->next->verse, "aa  ab") == 0
    //       && strcmp(lvl4->next->next->verse, "abca  BC") == 0
    //       && lvl4->next->next->next == NULL );
 
    // ---LVL 5--- //
    //printf("LVL 5\n");
    TVERSE * tmp5 = createVerse(createVerse(createVerse(createVerse(NULL, "prejtojeee"), "eR88*@8t*@(*(^%#*)o        EP7Je@!e      1J"), "PJEEErToej"), "Prej To JEEE");
    //TVERSE * lvl5 = vogonPoetry(tmp5);
 
    //assert(strcmp(lvl5->verse, "Prej To JEEE") == 0
    //       && lvl5->next == NULL );
 
    // END //
    freeList(tmp1);
    freeList(tmp2);
    freeList(tmp3);
    freeList(tmp4);
    freeList(tmp5);
 
    freeList(lvl1);
//    freeLis(lvl2);
//    freeLis(lvl3);
//    freeLis(lvl4);
//    freeLis(lvl5);
    return 0;
}
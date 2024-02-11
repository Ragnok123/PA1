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

//================================
// 2^n

// 1 = 2 3 4    => n-1 znamenek             4 cisla => 4 kombinace
// 1 2 = 3 4                                   5 cisel => 16
// 1 2 3 = 4

//1 znamenko: =, n-2 znamenek: +, -
//                             +, +
//                             -, -
//                             -, +

//2 znamenko: =, n-2 znamenek: +, -
//                             +, +
//                             -, -
//                             -, +

//3 znamenko: =, n-2 znamenek: +, -
//                             +, +
//                             -, -
//                             -, +

void iteruj(int pocetPrvku, int number[], int index){
    if(index >= pocetPrvku){
        for(int i = 0; i < pocetPrvku; i++){
            printf("%c", number[i]);
        }
        printf("\n");
        return;
    }
    char pole[] = {'+', '-'};
    for(int i = 0; i < 2; i++){
        number[index] = pole[i];
        iteruj(pocetPrvku, number, index+1);
    }
}

void vymena(int pocetPrvku, int index){
    char pole[] = {'+', '-'};
    int *number = (int*)malloc(sizeof(int)*pocetPrvku);
    int num = (int)pow(2,pocetPrvku);
    iteruj(pocetPrvku, number, 0);

}

void posun(int *pole, int indexRovnaSe, int vysledky){
    int n = sizeof(pole) + 1;

    if(indexRovnaSe == n-1){
        return;
    }

    int leva  ;       // n <= rovnaSe 
    int prava ;        // n > rovnaSe

    if(leva == prava){
        vysledky; // += 
    }

    posun(pole, indexRovnaSe+1, vysledky);

}

void posunTest(int *pole, int indexRovnaSe){
    posun(pole, indexRovnaSe, 0);
}

//================================

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
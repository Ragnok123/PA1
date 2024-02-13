#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*

rozdelime si retezec podle otazniku
ada??dweds?daeq
ada dweds daeq

ukladame 2 pozice pred a za
podminka: jestli ? neni nalevo nebo napravo od otazniku
    -> ano, pozice = -1 -> rekurze
    -> ne -> hledame pismenka

pole pro kazde pismenko a vybiram si tam vsechny mozne varianty

klic[a] = b,c
klic[b] = a,c,d
.
.
.
klic[z] = x,y

porovnavame leveho a praveho souseda v cyklu (for)
v prvnim cyklu hledam varianty pro prvni pismeno
podminka zda pismeno je index souseda
pokud se rovnaji => break a nahrazuji otaznikem
pokud ne => hledam dale

*/

void desifruj(char *string, int pole[], int currentIndex, int pSize, int length){

    int oneLeft = currentIndex-1;
    int twoLeft = currentIndex-2;
    int oneRight = currentIndex+1;
    int twoRight = currentIndex+2;

    if(currentIndex < 0 || currentIndex >= length){
        return;
    }
    char ch = string[currentIndex];
    if(ch == '?'){
        desifruj(string, pole, twoLeft, pSize, length);
        desifruj(string, pole, oneLeft, pSize, length);
        desifruj(string, pole, oneRight, pSize, length);
        desifruj(string, pole, twoRight, pSize, length);
    } else {

    }

    //jestli index == jeden z 4 => rekurze
    //jestli ne, 


}

int main(){
    printf("Klic:\n");
    size_t capacity = 0;
    int length;
    char *buffer;
    while((length = getline(&buffer, &capacity, stdin)) != -1){
        if(buffer[length-1] == '\n'){
            buffer[length-1] = '\0';
        }
        int pSize = 0, pCapacity = 16;
        int *pole = (int*) malloc(pCapacity * sizeof(int));

        int strIndex = 0;
        while(buffer[strIndex] != '\0'){
            char ch = buffer[strIndex];
            if(ch == '?'){
                if(pSize == pCapacity){
                    pCapacity *= 2;
                    pole = (int*)realloc(pole, pCapacity * sizeof(int));
                }
                pole[pSize++] = strIndex;
            }
            strIndex++;
        }

        // aba?ca
        desifruj(buffer, pole, pole[0], pSize, length);

        free(pole);
    }

    free(buffer);

    return 0;
}
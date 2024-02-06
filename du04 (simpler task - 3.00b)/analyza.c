#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int isDecreasing(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] <= a[i + 1]) {
            return 0;
        }
    }
    return 1; 
}

void calculateSubsequency(int values[], int length){
    if (length < 2) {
        printf("Nespravny vstup.\n");
        //printf("Malo cisel.\n");
        return;
    }

    int max_delka = 0;
    int pole[250000][2];
    int count = 0;

    if(!isDecreasing(values, length)){
        for(int i = 0; i < length; i++){
            for(int j = length - 1; j >= 0; j--){
                if(values[j] >= values[i]){
                    int delka = ((j-i)+1);
                    if (delka == max_delka) {
                        pole[count][0] = i;
                        pole[count][1] = j;
                        count++;
                    } else if (delka > max_delka) {
                        max_delka = delka;
                        count = 0;
                        pole[count][0] = i;
                        pole[count][1] = j;
                        count++;
                    }
                    //printf("Nasel jsem cislo %i\n", values[j]);
                    //printf("Sekvence: %i-%i\n", values[i], values[j]);
                    //printf("Delka sekvence: %i\n", current_length);
                    break;
                } else if(i >= j) break;
            }
        }

        for (int i = 0; i < count; i++) {
            printf("%i: %i - %i\n", max_delka, pole[i][0], pole[i][1]);
        }
        printf("Moznosti: %i\n", count);
    } else {
        printf("Nelze najit.\n");
    }
}

int main() {
    int account_values[250000];
    int length = 0;
    printf("Hodnoty:\n");
    while (scanf(" %i ", &account_values[length]) != EOF) {
        length++;
        if (length >= 250000) {
            printf("Nespravny vstup.\n");
            return 1;
        }
    }
    calculateSubsequency(account_values, length);
    return 0;
}

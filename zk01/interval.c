/**
 * 
Input: 12-19, 1-8, 5
Output: <1-8>, <12-19>

Input: 1, 3, 5
Output: <1-1>, <3-3>, <5-5>

Input: 1-5, 3-8, 7, 29-31
output: <1-8>, <29-31>

Input: 5, 6, 
                    8, 7, 
    11-29, 9-10
Output: <5-29>
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMS 100 // Maximální počet čísel, které můžeme zpracovat

typedef struct Titem{
 struct Titem *m_next;
 int m_from;
 int m_to;
} TITEM;

// Funkce pro porovnání dvou celých čísel, používá se v qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Funkce pro rozšíření intervalů a jejich přidání do pole
void addRange(int start, int end, int *nums, int *index) {
    for (int i = start; i <= end; i++) {
        nums[(*index)++] = i;
    }
}

int isAscending(int num1, int num2){
    return num1+1==num2;
}

void printInterval(int nums[], int size){
    int begin = nums[0];        //1
    int konec = nums[0];        //1
    for (int i = 1; i < size; i++) {
        if (nums[i] == nums[i-1] + 1) {
            konec = nums[i];
        } else {
            if (begin == konec) {
                printf("- %d, ", begin);
            } else {
                printf("- %d-%d, ", begin, konec);
            }
            begin = konec = nums[i];
        }
    }
    if (begin == konec) {
                printf("- %d, ", begin);
            } else {
                printf("- %d-%d, ", begin, konec);
            }
}

int main() {
    char input[100]; // Předpokládáme, že vstup nebude delší než 99 znaků
    int nums[MAX_NUMS];
    int index = 0; // Index pro ukládání čísel do pole nums
    /**
     * 
     * Zadejte vstup 1:
     * Input 1
     * input 2
     * .
     * .
     * .
     * input n
     *              (tady stisknu enter)
     * Zadejte vstup 2:
    */

    printf("Zadejte cisla a intervaly (napr. 1, 2, 5-8): ");
    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, ", ");
    while (token != NULL && index < MAX_NUMS) {
        if(strchr(token, '-')) {
            // Token je interval
            int start, end;
            sscanf(token, "%d-%d", &start, &end);
            addRange(start, end, nums, &index);
        } else {
            // Token je jednotlivé číslo
            nums[index++] = atoi(token);
        }
        token = strtok(NULL, ", "); // Spojujeme tokeny do inputu
    }

    // Seřazení čísel
    qsort(nums, index, sizeof(int), compare);

    // Výpis seřazených čísel
    for(int i = 0; i < index; i++){
        printf("%d ", nums[i]);
    }
    printf("Serazena cisla: ");
    printInterval(nums, index);


    return 0;
}
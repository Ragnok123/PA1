#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMS 100 // Maximální počet čísel, které můžeme zpracovat

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

// Funkce pro vytisknutí intervalů
void printIntervals(const int *nums, int size) {
    int start = nums[0], end = nums[0];
    for (int i = 1; i < size; i++) {
        if (nums[i] == nums[i-1] + 1) {
            end = nums[i];
        } else {
            if (start == end) {
                printf("%d, ", start);
            } else {
                printf("%d-%d, ", start, end);
            }
            start = end = nums[i];
        }
    }
    if (start == end) {
        printf("%d", start);
    } else {
        printf("%d-%d", start, end);
    }
}

int main() {
    char input[100]; // Předpokládáme, že vstup nebude delší než 99 znaků
    int nums[MAX_NUMS];
    int index = 0; // Index pro ukládání čísel do pole nums

    printf("Zadejte čísla a intervaly (např. 1, 2, 5-8): ");
    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, ", ");
    while (token != NULL && index < MAX_NUMS) {
        if (strchr(token, '-')) {
            // Token je interval
            int start, end;
            sscanf(token, "%d-%d", &start, &end);
            addRange(start, end, nums, &index);
        } else {
            // Token je jednotlivé číslo
            nums[index++] = atoi(token);
        }
        token = strtok(NULL, ", ");
    }

    // Seřazení čísel
    qsort(nums, index, sizeof(int), compare);

    // Vytvoření a výpis intervalů z seřazeného pole
    printf("Intervaly: ");
    printIntervals(nums, index);
    printf("\n");

    return 0;
}
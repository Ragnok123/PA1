#include <stdio.h>
#include <assert.h>

// Pomocná rekurzivní funkce pro hledání kombinací
void findCombinations(int *arr, int len, int sum, int index, int *currentCombination, int currentLength) {
    // Pokud jsme dosáhli konce pole
    if (index >= len) {
        // Pokud je sum rovno nule, našli jsme platnou kombinaci
        if (sum == 0) {
            // Vypíšeme aktuální kombinaci
            int localSum = 0;
            printf("%d", currentCombination[0]);
            for (int i = 1; i < currentLength; i++) {
                printf(" + %d", currentCombination[i]);
                localSum +=currentCombination[i];
            }
            printf(" = %i\n", sum);
        }
        return;
    }

    // Nezahrneme aktuální prvek
    findCombinations(arr, len, sum, index + 1, currentCombination, currentLength);

    // Zahrneme aktuální prvek a snížíme sum o hodnotu aktuálního prvku
    currentCombination[currentLength] = arr[index];
    findCombinations(arr, len, sum - arr[index], index + 1, currentCombination, currentLength + 1);
}

// Hlavní funkce pro hledání součtu prvků v poli
int sumElements(int *arr, int len, int sum) {
    int currentCombination[len]; // Pole pro ukládání aktuální kombinace
    findCombinations(arr, len, sum, 0, currentCombination, 0); // Spustíme hledání kombinací
    return 0;
}

int main() {
    int input1[] = { 4, 5, 6, 7, 8, 9, 10, 11 };
    assert(sumElements(input1, sizeof(input1) / sizeof(input1[0]), 11) == 3);

    int input2[] = {1, -1, 1, -1, 0};
    assert(sumElements(input2, sizeof(input2) / sizeof(input2[0]), 0) == 12);
    return 0;
}

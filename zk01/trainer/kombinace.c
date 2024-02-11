#include <stdio.h>

void generateCombinations(char *array, int length, int position) {
    if (position == length) {
        // Pokud jsme dosáhli konce pole, vytiskneme kombinaci
        for (int i = 0; i < length; i++) {
            printf("%c", array[i]);
        }
        printf("\n");
        return;
    }

    // Nastavte aktuální pozici na '+', a rekurzivně generujte zbytek
    array[position] = '+';
    generateCombinations(array, length, position + 1);

    // Nastavte aktuální pozici na '-', a rekurzivně generujte zbytek
    array[position] = '-';
    generateCombinations(array, length, position + 1);
}

int main() {
    int n = 3; // Velikost pole
    char array[n+1]; // Pole pro ukládání kombinací, +1 pro null terminator pro snadnější tisk

    generateCombinations(array, n, 0); // Spuštění generování kombinací

    return 0;
}

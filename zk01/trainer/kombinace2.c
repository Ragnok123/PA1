#include <stdio.h>

int main() {
    char symbols[2] = {'+', '-'};
    char array[3]; // Pole pro ukládání jednotlivých kombinací

    // Tři vnořené cykly pro každou pozici v poli
    for (int i = 0; i < 2; i++) { // První index
        array[0] = symbols[i];
        for (int j = 0; j < 2; j++) { // Druhý index
            array[1] = symbols[j];
            for (int k = 0; k < 2; k++) { // Třetí index
                array[2] = symbols[k];

                // Vytiskněte aktuální kombinaci
                printf("%c%c%c\n", array[0], array[1], array[2]);
            }
        }
    }

    return 0;
}
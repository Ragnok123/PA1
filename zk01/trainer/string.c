#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char puvodni[] = "RozdelMne"; // \0
    int delka = strlen(puvodni);
    int stred = delka / 2;

    // Alokace paměti pro obě poloviny
    char *prvniPolovina = (char *)malloc(stred + 1); // +1 pro nulový znak
    char *druhaPolovina = (char *)malloc(delka - stred + 1); // +1 pro nulový znak

    if (prvniPolovina == NULL || druhaPolovina == NULL) {
        printf("Nepodařilo se alokovat paměť.\n");
        // Uvolnění přidělené paměti v případě, že jedna z alokací selhala
        free(prvniPolovina);
        free(druhaPolovina);
        return 1;
    }

    // Kopírování první poloviny
    strncpy(prvniPolovina, puvodni, stred);
    prvniPolovina[stred] = '\0'; // Ukončení první poloviny nulovým znakem

    // Kopírování druhé poloviny
    strncpy(druhaPolovina, puvodni + stred, delka - stred);
    druhaPolovina[delka - stred] = '\0'; // Ukončení druhé poloviny nulovým znakem

    // Výpis obou polovin
    printf("První polovina: %s\n", prvniPolovina);
    printf("Druhá polovina: %s\n", druhaPolovina);

    // Uvolnění paměti
    free(prvniPolovina);
    free(druhaPolovina);

    return 0;
}
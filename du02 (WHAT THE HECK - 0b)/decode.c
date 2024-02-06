#include <stdio.h>
#include <string.h>
#include <limits.h>

// Funkce pro převod znaku na délku pulzu
int convertCharToLength(char a) {
    if (a < 'a' || a > 'z') { // Kontrola, zda je vstup platný
        return -1; // Chyba: znak není malé písmeno
    }
    return 1 << (a - 'a'); // Převod znaku na délku pulzu
}

// Funkce pro výpočet délky zprávy
int najit_delku(char *zprava) {
    int delka = 0; // Inicializace délky
    int i = 0; // Inicializace indexu
    while (zprava[i] != '|') { // Cyklus pro načtení délky před znakem '|'
        delka += convertCharToLength(zprava[i]); // Přičtení délky pulzu k délce zprávy
        i++; // Inkrementace indexu
    }
    i++; // Přeskočit znak '|'
    delka++; // Přidat časový úsek za znak '|'
    while (zprava[i] != '\0') { // Cyklus pro načtení délky po znaku '|'
        delka += convertCharToLength(zprava[i]); // Přičtení délky pulzu k délce zprávy
        i++; // Inkrementace indexu
    }
    return delka; // Vrácení délky zprávy
}

int najit_zbytek(char *zprava) {
    int delka = 0; // Inicializace délky
    int i = 0; // Inicializace indexu
    while (zprava[i] != '|') { // Cyklus pro načtení délky před znakem '|'
        delka += convertCharToLength(zprava[i]); // Přičtení délky pulzu k délce zprávy
        i++; // Inkrementace indexu
    }
    return delka; // Vrácení délky zprávy
}

// Funkce pro výpočet největšího společného násobku (LCM)
int gcd(int a, int b){
    int result = ((a < b) ? a : b); 
    while(result > 0) { 
        if (a % result == 0 && b % result == 0) { 
            break; 
        } 
        result--; 
    }
    return result; 
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

/*
Basic rovnice 
*/
int synchronize(int* delky, int* pozice, int n){
    int cas[2];
    int canStart = 0; // zprava zacina jako ea|babab, ne |babab
    int stejnePozice = 0; // babab and abaca maji ruznou hodnotu
    int stop = 0;
    for(int i = 0; i < n; i++){
        if(delky[n] == pozice[n]){
            canStart = 1;
            printf("Stejna pozice");
        }
        if(pozice[n] == 0){
            stejnePozice = 1;
            printf("Zprava zacina s |");
        }
    }
    if(canStart || stejnePozice){
        for(int i = 0; i < n; i++){
            cas[i] = 0;
        }
    } else {
        int nejmensi_gcd = delky[0];
        for (int i = 1; i < n; i++) {
            nejmensi_gcd = gcd(nejmensi_gcd, delky[i]);
        }
        if((pozice[1] - pozice[0]) % nejmensi_gcd == 0){
            for(int n1=1; n1<INT_MAX; n1++){
                int zbytek = (delky[1]*n1) + (pozice[1] - pozice[0]);
                if(zbytek % delky[0] == 0){
                    int n0 = zbytek / delky[0];
                    cas[0] = pozice[0] + n0*delky[0];
                    cas[1] = pozice[1] + n1*delky[1];
                    stop = 1;
                    break;
                }
            }
        }
    }
    if(stop){
        return cas[0];
    }
    return 0;
}

// Hlavní funkce
int main() {
    int n = 0;
    char zpravy[10][101];
    int delky[10];
    int pozice[10];
    
    // Nacteni zprav
    while (fgets(zpravy[n], 101, stdin) != NULL) {
        if (zpravy[n][0] == '\n') break; // prazdny radek ukonci vstup
        char *ukazatel = strchr(zpravy[n], '|');
        // Kontrola správného formátu zprávy
        if (ukazatel == NULL || ukazatel == zpravy[n] || ukazatel - zpravy[n] + 1 == (int)strlen(zpravy[n])) {
            printf("Nespravny vstup.\n");
            return 1;
        }
        int delka = najit_delku(zpravy[n]);
        if (delka == -1) {
            printf("Nespravny vstup.\n");
            return 1;
        }
        delky[n] = delka;
        //pozice[n] = delka - (strlen(ukazatel) + 1); // Výpočet pozice před '|'
        pozice[n] = najit_zbytek(zpravy[n]);
        printf("Delka zpravy: %i\n", delky[n]);
        printf("Pozice zpravy: %i\n", pozice[n]);
        n++;
        if (n >= 10) break; // Limit na počet zpráv
    }

    if (n < 2) { //Nevim jeste jak pro n > 2...
        printf("Nespravny vstup.\n");
        return 1;
    }

    int cas = synchronize(delky, pozice, n);
    if(cas == 0){
        printf("Nelze dosahnout.\n");
    } else {
        printf("Synchronizace za: %i\n", cas);
    }
    return 0;
}
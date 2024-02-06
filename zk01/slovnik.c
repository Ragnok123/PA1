#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
    char string[31];
    int inSlovnik;
} string_t;

typedef struct array {
    int size;
    int capacity;
    string_t * data;
} array_t;

void arrayInit (array_t * array) {
    array->size = 0;
    array->capacity = 5;
    array->data = (string_t*) malloc(array->capacity * sizeof(string_t));
}

void arrayFree (array_t * array) {
    free(array->data);
}

void arrayApend (array_t * array, string_t string) {
    if (array->size + 1 == array->capacity) {
        array->capacity *= 2;
        array->data = (string_t*) realloc(array->data, array->capacity * sizeof(string_t));
    }
    array->data[array->size] = string;
    array->size++;
}

int loadSlovnik (array_t * array) {
    printf("Slovnik:\n");
    char str[31];
    string_t stri;
    while (1) {
        int scan = scanf("%30s", str);

        if (scan == EOF)
            return 0;
        if (scan != 1)
            return 0;
        if (strcasecmp(str, "*****") == 0)
            return 1;

        strcpy(stri.string, str);
        stri.inSlovnik = 1;

        arrayApend(array, stri);
    }
    return 1;
}

int loadText (array_t * array) {
    printf("Text:\n");
    char str[31];
    string_t stri;

    while (1) {
        int scan = scanf("%30s", str);

        if (scan == EOF)
            return 1;
        if (scan != 1)
            return 0;

        strcpy(stri.string, str);
        stri.inSlovnik = 0;

        arrayApend(array, stri);
    }
    return 1;
}

void checkIfInSlovnik (array_t * slovnik, array_t * text) {
    for (int i = 0; i < text->size; i++) {
        for (int j = 0; j < slovnik->size; j++) {
            if (strcasecmp(text->data[i].string,
                        slovnik->data[j].string) == 0) {
                text->data[i].inSlovnik = 1;
                break;
            }
        }
    }
}

void printResults (array_t * array) {
    int length = 0;
    for (int i = 0; i < array->size; i++) {
        int sLen = strlen(array->data[i].string);
        if (length == 0) {
            if (array->data[i].inSlovnik) {
                printf("%s", array->data[i].string);
                length += sLen;
            }
            else {
                printf("<err>%s</err>", array->data[i].string);
                length += sLen + 12;
            }
        }
        else {
            if (array->data[i].inSlovnik) {
                if (length + sLen + 1 <= 80) {
                    printf(" %s", array->data[i].string);
                    length += sLen + 1;
                }
                else {
                    printf("\n");
                    length = 0;
                    i--;
                }
            }
            else {
                if (length + sLen + 12 <= 80) {
                    printf(" <err>%s</err>", array->data[i].string);
                    length += sLen + 12;
                }
                else {
                    printf("\n");
                    length = 0;
                    i--;
                }
            }
        }
        //printf("%d\n", length);
    }
}

int main () {
    array_t slovnik;
    arrayInit(&slovnik);

    if (!loadSlovnik(&slovnik)) {
        printf("Nespravny vstup.\n");
        arrayFree(&slovnik);
        return 1;
    }

    /*    for (int i = 0; i < slovnik.size; i++)
          printf("%s\n", slovnik.data[i].string);
          */
    array_t text;
    arrayInit(&text);

    if (!loadText(&text)) {
        printf("Nespravny vstup.\n");
        arrayFree(&text);
        return 1;
    }

    /*    for (int i = 0; i < text.size; i++)
          printf("%s\n", text.data[i].string);
          */    
    checkIfInSlovnik(&slovnik, &text);

    printResults(&text);

    arrayFree(&slovnik);
    arrayFree(&text);

    printf("\n");
    return 0;

}

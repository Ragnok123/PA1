#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUMBERS 20

typedef struct {
    char number[21];
    char *name;
    char *nameNumeric;
} Contact;

char* convertStringToT9(char* string){
    int length = strlen(string);
    char *T9 = (char*)malloc(length * sizeof(char));
    for (int i = 0; i < length; ++i) {
        char c = tolower(string[i]);
        if (c >= 'a' && c <= 'c') {
            T9[i] = 2;
        } else if (c >= 'd' && c <= 'f') {
            T9[i] = 3;
        } else if (c >= 'g' && c <= 'i') {
            T9[i] = 4;
        } else if (c >= 'j' && c <= 'l') {
            T9[i] = 5;
        } else if (c >= 'm' && c <= 'o') {
            T9[i] = 6;
        } else if (c >= 'p' && c <= 's') {
            T9[i] = 7;
        } else if (c >= 't' && c <= 'u') {
            T9[i] = 8;
        } else if (c >= 'v' && c <= 'z') {
            T9[i] = 9;
        } else if (c == ' ') {
            T9[i] = 1;
        }
    }
    return T9;
}

char* convertT9ToString(const char* t9Array, int length, char* string) {
    for (int i = 0; i < length; ++i) {
        if (t9Array[i] == 1) {
            string[i] = ' ';
        } else if (t9Array[i] >= 2 && t9Array[i] <= 9) {
            string[i] = 'a' + (t9Array[i] - 2) * 3 + (t9Array[i] > 7 ? 1 : 0);
        }
    }
    return string;
}

int startsWith(const char *string, const char *start){
   return strncmp(string, start, strlen(start)) == 0 ? 1 : 0;
}

int main(){
    int chr;
    int isValidOperation = 1;
    while ((chr = fgetc(stdin)) != EOF) {
        printf("It is a valid operation? %i\n", isValidOperation);
        printf("First character: %c\n", (chr-'0'));
        if(chr == '+' && isValidOperation){
            isValidOperation = 0;
            char number[MAX_NUMBERS];
            char *name = NULL;
            int numIndex = 0;
            int nameSize = 0;
            int spaces = 0;
            int isValid = 1;
            while ((chr = fgetc(stdin)) != '\n' && chr != EOF) {
                if(chr == ' '){
                    spaces++;
                    if(spaces > 2){
                        name = (char*)realloc(name, (nameSize + 1) * sizeof(char));
                        name[nameSize] = ' ';
                        nameSize++;
                    }
                } else if((chr - '0')>= 0 && (chr - '0') <= 9){
                    if (numIndex >= MAX_NUMBERS || spaces != 1 || chr == '\t') {
                        printf("Nespravny vstup 1.\n");
                        isValid = 0;
                    } else { 
                        number[numIndex] = (char)chr;
                        //printf("Index: %i\nCislo v indexu: %i\n", numIndex, number[numIndex]);
                        numIndex++;
                    }
                    printf("Cislo: %s\n", number);
                } else if(((chr - 'A') >= 0 && (chr - 'A') < 26 )|| ((chr - 'a') >= 0 && (chr - 'a') < 26)){
                    if(spaces < 2 || chr == '\t'){
                        printf("Nespravny vstup 2.\n");
                        isValid = 0;
                    } else {
                        printf("Kek\n");
                        name = (char*)realloc(name, (nameSize + 1) * sizeof(char));
                        name[nameSize] = (char)chr;
                        //printf("Character: %c\n", name[nameSize]);
                        nameSize++;
                    }
                } else {
                    isValid = 0;
                    printf("Zakazany symbol...\n");
                }
            }
            if(isValid || spaces >= 2 || nameSize != 0 || numIndex != 0){
                name = (char*)realloc(name, (nameSize + 1) * sizeof(char));
                name[nameSize] = '\0';
                printf("Spaces: %i\n", spaces);
                printf("Number size: %i\n", numIndex);
                printf("Delka cisla: %i\n", strlen(number));
                printf("Delka jmena: %i\n", nameSize);
                printf("Jmeno: %s\n", name);
                printf("Cislo: %s\n", number);
            }
            if(name != NULL){
                free(name);
            }
            isValidOperation = 1;
        } else if(chr == '?' && isValidOperation){
            isValidOperation = 0;
            char *query = NULL;
            int spaces = 0;
            int numIndex = 0;
            int isValid = 1;
            while ((chr = fgetc(stdin)) != '\n' && chr != EOF) {
                if(chr == ' '){
                    if(spaces == 0){
                        spaces++;
                    } else {
                        isValid = 0;
                    }
                } else if (!isdigit(chr)){
                    printf("Nespravny vstup cisel\n");
                    isValid = 0;
                } else {
                    printf("Huraaaaaa\n");
                    query = (char*)realloc(query, (numIndex+1) * sizeof(char));
                    query[numIndex] = (char)chr;
                    printf("Character: %c\n", query[numIndex]);
                    numIndex++;
                }
            }
            if(isValid){
                printf("Query: %s\n", query);
            }
            if(query != NULL){
                free(query);
            }
            isValidOperation = 1;
        } else if(chr == '\n'){
            printf("This character is pressed...\n");
            //isValidOperation = 1;
        } else {
            printf("Nespravny vstup 3.\n");
        } 
    }
    return 0;
}
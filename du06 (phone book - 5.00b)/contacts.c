#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUMBERS 20

typedef struct {
    char number[21];
    char *name;
    char *nameNumeric;
    int numSize;
    int nameSize;
} Contact;

struct Tree {
    int contacts;
    char **data;
    struct Tree* nodes[10];
};
struct Tree *root;

void clearTree(struct Tree *node){
	for(int i = 0; i < 10; i++){
		if (node->nodes[i] != NULL){
			clearTree(node->nodes[i]);
		}
	}
	for (int j = 0; j < node->contacts; j++){
		free(node->data[j]);
	}
	free(node->data);
	free(node);
}

char* convertStringToT9(char* string, int length){
    char *T9 = (char*)malloc(length * sizeof(char));
    for (int i = 0; i < length; ++i) {
        char c = tolower(string[i]);
        printf("Character is %c\n", c);
        if (c >= 'a' && c <= 'c') {
            T9[i] = '2';
        } else if (c >= 'd' && c <= 'f') {
            T9[i] = '3';
        } else if (c >= 'g' && c <= 'i') {
            T9[i] = '4';
        } else if (c >= 'j' && c <= 'l') {
            T9[i] = '5';
        } else if (c >= 'm' && c <= 'o') {
            T9[i] = '6';
        } else if (c >= 'p' && c <= 's') {
            T9[i] = '7';
        } else if (c >= 't' && c <= 'u') {
            T9[i] = '8';
        } else if (c >= 'v' && c <= 'z') {
            T9[i] = '9';
        } else if (c == ' ') {
            T9[i] = '1';
        }
    }
    T9[length] = '\0';
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

int compareStrings(char *string1, char *string2){
    return strcmp(string1, string2);
}

int startsWith(const char *string, const char *start){
   return strncmp(string, start, strlen(start)) == 0 ? 1 : 0;
}

int addContact(char *number, char *name, int numberSize, int nameSize){
    char *T9 = convertStringToT9(name, nameSize);
    return 0;
}

/**
 * This code reads command "+"
 * 
 * @param chr Character
 * @return Boolean value of successfull input reading
*/
int readAddition(int chr){
    char number[MAX_NUMBERS];
    char *name = NULL;
    int numIndex = 0;
    int nameSize = 0;
    int spaces = 0;
    int isValid = 1;
    while ((chr = fgetc(stdin)) != EOF && chr != '\n') {    /*! We are reading until end of file or next line*/
        if(chr == ' '){
            spaces++;
            printf("Pocet mezer: %i\n", spaces);
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
                numIndex++;
            }
            printf("Cislo: %s\n", number);
        } else if((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')){
            if(spaces < 2 || chr == '\t'){
                printf("Nespravny vstup 2.\n");
                isValid = 0;
            } else {
                printf("Kek\n");
                name = (char*)realloc(name, (nameSize + 1) * sizeof(char));
                name[nameSize] = (char)chr;
                nameSize++;
            }
        } else {
            isValid = 0;
            printf("Zakazany symbol...\n");
        }
    }
    if(isValid && spaces >= 2 && nameSize != 0 && numIndex != 0 && name[0] != ' ' && name[nameSize-1] != ' '){
            name = (char*)realloc(name, (nameSize + 1) * sizeof(char));
            name[nameSize] = '\0';
            number[numIndex] = '\0';
            printf("Spaces: %i\n", spaces);
            printf("Number size: %i\n", numIndex);
            printf("Delka cisla strlen: %i\n", strlen(number));
            printf("Name size: %i\n", nameSize);
            printf("Delka jmena strlen: %i\n", strlen(name));
            printf("Jmeno: %s\n", name);
            printf("T9: %s\n", convertStringToT9(name, nameSize));
            printf("Jmeno: %s\n", name);
            free(name);
            return 1;
        }
        if(name != NULL){
            free(name);
        }
    return 0;
}

/**
 * This code reads command "?"
 * 
 * @param chr Character
 * @return Boolean value of successfull input reading
*/
int readQuery(int chr){
    char *query = NULL;
    int spaces = 0;
    int numIndex = 0;
    int isValid = 1;
    while ((chr = fgetc(stdin)) != EOF && chr != '\n') {
        if(chr == ' '){
            spaces++;
            printf("Pridana mezera\n");
        } else if (!isdigit(chr)){
            printf("Nespravny vstup cisel\n");
            isValid = 0;
        } else {
            if(spaces > 1 || chr == '\t'){
                isValid = 0;
                printf("Mezery...\n");
            } else {
                printf("Huraaaaaa\n");
                query = (char*)realloc(query, (numIndex+1) * sizeof(char));
                query[numIndex] = (char)chr;
                printf("Character: %c\n", query[numIndex]);
                numIndex++;
            }
        }
    }
    printf("Pocet mezer: %i\n", spaces);
    if(isValid && spaces == 1 && numIndex != 0){
        query = (char*)realloc(query, (numIndex + 1) * sizeof(char));
        query[numIndex] = '\0';
        printf("Query: %s\n", query);
        free(query);
        return 1;
    }
    if(query != NULL){
        free(query);
    }
    return 0;
}
/**
 * This is main function
*/
int main() {
    while(1){       /*! We are looping our code, because we want to read all lines*/
        int chr;    /*! Very first character*/
        chr = fgetc(stdin);
        int success;
        if(chr == '+'){
            success = readAddition(chr);
        } else if(chr == '?'){
            success = readQuery(chr);
        } else {
            success = 1;
            if(chr == '\n'){
                success = 0;
            } else {
                while(chr != '\n' && !feof(stdin)){
                    chr = fgetc(stdin);
                }
                success = 0;
            }
        }
        if(!success){
            printf("Nespravny vstup.\n");
        }
    }
    return 0;
}
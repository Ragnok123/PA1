#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUMBERS 20

int bestMaximum = 10;
int Found = 0;
int bufferSize = 0;

typedef struct{
    char number[21];
    char *name;
    char *numericName;
    int numberSize;
    int nameSize;
} Contact;
Contact *phoneBook = NULL;
int totalContacts = 0;
int *Pool = NULL;

void clearData(){
    for(int i = 0; i < totalContacts; i++){
        free(phoneBook[i].name);
        free(phoneBook[i].numericName);
    }
    free(phoneBook);
}

/**
 * This function converts normal name into T9 palette
 * 
 * @param string String we want to convert
 * @param length String size
 * @result converted string in T9 format
*/
char* convertStringToT9(char* string, int length){
    char *T9 = (char*)malloc((length+1) * sizeof(char));
    for (int i = 0; i < length; ++i) {
        char c = tolower(string[i]);
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
        } else if (c >= 't' && c <= 'v') {
            T9[i] = '8';
        } else if (c >= 'w' && c <= 'z') {
            T9[i] = '9';
        } else if (c == ' ') {
            T9[i] = '1';
        }
    }
    T9[length] = '\0';
    return T9;
}


/**
 * This adds username T9 to our tree structure
 * 
 * @param node Root tree
 * @param number Phone number
 * @param name Username
 * @param numericName Username converted in T9
 * @param numSize Phone number or its part lfull ength
 * @param nameSize Name or its part full length
 * @result If our operation was successful, returns 1. In other case returns 0;
 */
int addContact(char* number, char* name, char *numericName, int numSize, int nameSize){
    for(int i = 0; i < totalContacts; i++){
        if(!strcmp(phoneBook[i].number, number) && !strcmp(phoneBook[i].name, name)){   //checks if our contact exists. If yes, dont add.
            return 0;
        }
    }
    phoneBook = (Contact*) realloc(phoneBook, (totalContacts+1)*sizeof(Contact));
    for(int i = 0; i < numSize; i++){
        phoneBook[totalContacts].number[i] = number[i];
    }
    phoneBook[totalContacts].number[numSize] = '\0';
    phoneBook[totalContacts].name = (char*)malloc((nameSize+1) * sizeof(char));
    for(int i = 0; i < nameSize; i++){
        phoneBook[totalContacts].name[i] = name[i];
    }
    phoneBook[totalContacts].name[nameSize] = '\0';
    phoneBook[totalContacts].numericName = (char*)malloc((nameSize+1) * sizeof(char));
    for(int i = 0; i < nameSize; i++){
        phoneBook[totalContacts].numericName[i] = numericName[i];
    }
    phoneBook[totalContacts].numericName[nameSize] = '\0';
    phoneBook[totalContacts].numberSize = numSize;
    phoneBook[totalContacts].nameSize = nameSize;

    totalContacts++;
    return 1;
}

/**
 * Checks if string contains substring
 * @param string String
 * @param start Substring
 * @result Returns 1 if string contains substring. Eitherwise returns 0
*/
int startsWith(const char *string, const char *start){
   return strncmp(string, start, strlen(start)) == 0 ? 1 : 0;
}

/**
 * Searches contacts with prefis
 * @param query Contact prefix
*/
void search(char* query){
    for(int i = 0; i < totalContacts; i++){
        if(startsWith(phoneBook[i].number, query) || startsWith(phoneBook[i].numericName, query)){
            if(Found == bestMaximum){
			    bestMaximum *= 2;
			    Pool = (int*)realloc(Pool, bestMaximum * sizeof(int));
		    }
            Pool[Found] = i;
            Found++;
        }
    }
}


/**
 * This code reads command "+"
 * 
 * @param chr Character
 * @return Boolean value of successfull input reading
*/
int readAddition(int chr){
    char number[MAX_NUMBERS + 1];
    char *name = NULL;
    int numIndex = 0;
    int nameSize = 0;
    int spaces = 0;
    int isValid = 1;
    while ((chr = fgetc(stdin)) != EOF && chr != '\n') {    /*! We are reading until end of file or next line*/
        if(chr == ' '){
            spaces++;
            if(spaces > 2){     //+ is separated with 1 space and number with second, so at least 3 whitespaces can be placed into a name
                if(nameSize == bufferSize){
                    if(bufferSize == 0){
                        bufferSize = 16;
                    } else {
                        bufferSize *= 2;
                    }
                    name = (char*)realloc(name, bufferSize+1 * sizeof(char));
                }
                name[nameSize] = ' ';
                nameSize++;
            }
        } else if((chr - '0')>= 0 && (chr - '0') <= 9){
            if (numIndex >= MAX_NUMBERS || spaces != 1 || chr == '\t') {
                isValid = 0;
            } else { 
                number[numIndex] = (char)chr;
                numIndex++;
            }
        } else if((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')){
            if(spaces < 2 || chr == '\t'){
                isValid = 0;
            } else {
                if(nameSize == bufferSize){
                    if(bufferSize == 0){
                        bufferSize = 16;
                    } else {
                        bufferSize *= 2;
                    }
                    name = (char*)realloc(name, bufferSize + 1 * sizeof(char));
                }
                name[nameSize] = (char)chr;
                nameSize++;
            }
        } else {
            isValid = 0;
        }
    }
    if(isValid && spaces >= 2 && nameSize != 0 && numIndex != 0 && name[0] != ' ' && name[nameSize-1] != ' '){
            name = (char*)realloc(name, (nameSize+1) * sizeof(char));
            name[nameSize] = '\0';
            number[numIndex] = '\0';
            char* T9 = convertStringToT9(name, nameSize);
            int success = addContact(number, name, T9, numIndex, nameSize);
            if(success){
                printf("OK\n");
            } else {
                printf("Kontakt jiz existuje.\n");
            }
            bufferSize = 0;
            free(name);
            free(T9);
            return 1;
    }
    bufferSize = 0;
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
        } else if (!isdigit(chr)){
            isValid = 0;
        } else {
            if(spaces > 1 || chr == '\t'){
                isValid = 0;
            } else {
                query = (char*)realloc(query, (numIndex+1) * sizeof(char));
                query[numIndex] = (char)chr;
                numIndex++;
            }
        }
    }
    if(isValid && spaces == 1 && numIndex != 0){
        query = (char*)realloc(query, (numIndex + 1) * sizeof(char));
        query[numIndex] = '\0';
        search(query);
        if(Found <= 10){
            for(int i = 0; i < Found; i++){
                int index = Pool[i];
                printf("%s %s",phoneBook[index].number, phoneBook[index].name);
                printf("\n");

            }
        }
        printf("Celkem: %i\n", Found);
        bestMaximum = 10;
        Found = 0;
        Pool = (int*)realloc(Pool, bestMaximum * sizeof(int));
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
    Pool = (int*)malloc(bestMaximum * sizeof(int));
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
            if(feof(stdin)){        //if we press ctrl+c or something like that, do nothing...
                free(Pool);
                clearData();
                return 0;
            }
            printf("Nespravny vstup.\n");
        }
    }
    if(feof(stdin)){
        free(Pool);
        clearData();
        return 0;
    }
    printf("Nespravny vstup.\n");
    return 0;
}
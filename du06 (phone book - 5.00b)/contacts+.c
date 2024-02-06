#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUMBERS 20
#define SONS 10

char **Pool = NULL;
int bestMaximum = 10;
int Found = 0;
int bufferSize = 0;

struct Tree {
    int contacts;
    char **data;
    struct Tree* nodes[SONS];
};
struct Tree *root;
/**
 * This function prints tree structure in debug mode
 * 
 * @param node Root tree
 * @param depth In how much we want debug
 * @result It prints tree in debug mode... 
*/
void printTree(struct Tree *node, int depth){
    if (node == NULL) return;
    int i, j;
    for (i = 0; i < depth; i++)
        printf("|-- ");
    printf("'%d'\n", depth);
    for (i = 0; i < 10; i++){
        if (node->nodes[i] != NULL)
            printTree(node->nodes[i], depth + 1);
    }
    for (j = 0; j < node->contacts; j++){
        for (i = 0; i <= depth; i++)
            printf("|   ");
        printf("-- '%s'\n", node->data[j]);
    }
}

/**
 * Clear entire tree when we shutdown program
 * 
 * @param node Root tree
 * @result Free entire tree before program end 
*/
void clearTree(struct Tree *node) {
    if (node == NULL) {
        return;
    }
    struct Tree *stack[1000];
    int last = -1;
    stack[++last] = node;
    while(last >= 0) {
        struct Tree *currentNode = stack[last--];
        for (int j = 0; j < currentNode->contacts; j++) {
            free(currentNode->data[j]);
        }
        free(currentNode->data);
        for (int i = 0; i < SONS; i++) {
            if (currentNode->nodes[i] != NULL) {
                stack[++last] = currentNode->nodes[i];
            }
        }
        free(currentNode);
    }
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
 * This function adds mobile number to our tree structure. If result is 1, it was successfully added. Either it failed.
 * 
 * @param node Root tree
 * @param number Mobile number
 * @param name User name
 * @param numSize Mobile number of its part length
 * @param nameSize Name length
 * @param fixedNumSize Entire mobile number length
 * @result  Returns if the operation was successful or not.
 */
int addNumber(struct Tree* node, char* number, char* name, int numSize, int nameSize, int fixedNumSize){
    int exists = 0;
    struct Tree* currentNode = node;
    int i = 0;
    while (i < numSize) {
        int index = number[fixedNumSize - numSize + i] - '0';
        if (currentNode->nodes[index] == NULL) {
            currentNode->nodes[index] = (struct Tree*)calloc(1, sizeof(struct Tree));
        }
        currentNode = currentNode->nodes[index];
        i++;
    }
    if (currentNode->contacts == 0) {
        currentNode->contacts++;
        currentNode->data = (char**)realloc(currentNode->data, currentNode->contacts * sizeof(currentNode->data[0]));
        currentNode->data[0] = NULL;
        currentNode->data[currentNode->contacts - 1] = (char*)realloc(
            currentNode->data[(currentNode->contacts) - 1], (fixedNumSize + 2 + nameSize) * sizeof(currentNode->data[(currentNode->contacts) - 1][0]));

        for (int j = 0; j < fixedNumSize; j++) {
            currentNode->data[currentNode->contacts - 1][j] = number[j];
        }
        currentNode->data[currentNode->contacts - 1][fixedNumSize] = ' ';
        for (int k = 0; k < nameSize; k++) {
            currentNode->data[currentNode->contacts - 1][fixedNumSize + 1 + k] = name[k];
        }
        currentNode->data[currentNode->contacts - 1][fixedNumSize + 1 + nameSize] = '\0';
        return 1;
    } else {
        for (int i = 0; i < currentNode->contacts; i++) {
            int length = strlen(currentNode->data[i]);
            if (length == (nameSize + fixedNumSize + 1)) {
                exists = 1;
                for (int j = 0; j < fixedNumSize; j++) {
                    if (currentNode->data[i][j] != number[j]) {
                        exists = 0;
                        break;
                    }
                }
                if (!exists) {
                    continue;
                }
                for (int k = 0; k < nameSize; k++) {
                    if (currentNode->data[i][k + fixedNumSize + 1] != name[k]) {
                        exists = 0;
                        break;
                    }
                    exists = 1;
                }
                if (!exists) {
                    continue;
                }
                if (exists) {
                    break;
                }
            }
        }
        if (!exists) {
            currentNode->contacts++;
            currentNode->data = (char**)realloc(currentNode->data, currentNode->contacts * sizeof(currentNode->data[0]));
            currentNode->data[currentNode->contacts - 1] = NULL;
            currentNode->data[currentNode->contacts - 1] = (char*)realloc(
                currentNode->data[(currentNode->contacts) - 1], (fixedNumSize + 2 + nameSize) * sizeof(currentNode->data[(currentNode->contacts) - 1][0]));
            for (int i = 0; i < fixedNumSize; i++) {
                currentNode->data[currentNode->contacts - 1][i] = number[i];
            }
            currentNode->data[currentNode->contacts - 1][fixedNumSize] = ' ';
            for (int j = 0; j < nameSize; j++) {
                currentNode->data[currentNode->contacts - 1][fixedNumSize + 1 + j] = name[j];
            }
            currentNode->data[currentNode->contacts - 1][fixedNumSize + 1 + nameSize] = '\0';
            return 1;
        }
        return 0;
    }
    return 1;
}

/**
 * This function adds mobile number and username T9 to our tree structure. If result is 1, it was successfully added. Either it failed.
 * 
 * @param node Root tree
 * @param number Mobile number
 * @param name User name
 * @param numericName Username converted in T9
 * @param numSize Mobile number or its part length
 * @param nameSize Name or its part length
 * @param fixedNumSize Entire mobile number length
 * @param fixedNameSize Entire name length
 * @result  Returns if operation was successful or not.
 */
int addName(struct Tree* node, char* number, char* name, char* numericName, int numSize, int nameSize, int fixedNumSize, int fixedNameSize){
    int exists = 0;
    struct Tree* currentNode = node;
    int i = 0;
    while(i < nameSize) {
        int index = numericName[fixedNameSize - nameSize + i] - '0';
        if (currentNode->nodes[index] == NULL) {
            currentNode->nodes[index] = (struct Tree*)calloc(1, sizeof(struct Tree));
        }
        currentNode = currentNode->nodes[index];
        i++;
    }
    if (currentNode->contacts == 0) {
        currentNode->contacts++;
        currentNode->data = (char**)realloc(currentNode->data, currentNode->contacts * sizeof(currentNode->data[0]));
        currentNode->data[0] = NULL;
        currentNode->data[currentNode->contacts - 1] = (char*)realloc(
            currentNode->data[(currentNode->contacts) - 1], (fixedNumSize + 2 + fixedNameSize) * sizeof(currentNode->data[(currentNode->contacts) - 1][0]));
        for (int j = 0; j < fixedNumSize; j++) {
            currentNode->data[currentNode->contacts - 1][j] = number[j];
        }
        currentNode->data[currentNode->contacts - 1][fixedNumSize] = ' ';
        for (int k = 0; k < fixedNameSize; k++) {
            currentNode->data[currentNode->contacts - 1][fixedNumSize + 1 + k] = name[k];
        }
        currentNode->data[currentNode->contacts - 1][fixedNumSize + 1 + fixedNameSize] = '\0';
        return 1;
    } else {
        for (int i = 0; i < currentNode->contacts; i++) {
            int length = strlen(currentNode->data[i]);
            if (length == (fixedNameSize + fixedNumSize + 1)) {
                exists = 1;
                for (int j = 0; j < fixedNumSize; j++) {
                    if (currentNode->data[i][j] != number[j]) {
                        exists = 0;
                        break;
                    }
                }
                if (!exists) {
                    continue;
                }
                for (int k = 0; k < fixedNameSize; k++) {
                    if (currentNode->data[i][k + fixedNumSize + 1] != name[k]) {
                        exists = 0;
                        break;
                    }

                    exists = 1;
                }
                if (!exists) {
                    continue;
                }
                if (exists) {
                    break;
                }
            }
        }
        if (!exists) {
            currentNode->contacts++;
            currentNode->data = (char**)realloc(currentNode->data, currentNode->contacts * sizeof(currentNode->data[0]));
            currentNode->data[currentNode->contacts - 1] = NULL;
            currentNode->data[currentNode->contacts - 1] = (char*)realloc(
                currentNode->data[(currentNode->contacts) - 1], (fixedNumSize + 2 + fixedNameSize) * sizeof(currentNode->data[(currentNode->contacts) - 1][0]));

            for (int i = 0; i < fixedNumSize; i++) {
                currentNode->data[currentNode->contacts - 1][i] = number[i];
            }
            currentNode->data[currentNode->contacts - 1][fixedNumSize] = ' ';
            for (int j = 0; j < fixedNameSize; j++) {
                currentNode->data[currentNode->contacts - 1][fixedNumSize + 1 + j] = name[j];
            }
            currentNode->data[currentNode->contacts - 1][fixedNumSize + 1 + fixedNameSize] = '\0';
            return 1;
        }
        return 0;
    }
    return 1;
}


/**
 * This function adds mobile number to our tree structure. If result is 1, it was successfully added. Either it failed.
 * 
 * @param node Root tree
 * @param number Mobile number
 * @param name User name
 * @param numSize Mobile number of its part length
 * @param nameSize Name length
 * @param fixedNumSize Entire mobile number length
 * @result  Returns if operation was successful or not.
*/
int addNumberOld(struct Tree* node, char* number, char* name, int numSize, int nameSize, int fixedNumSize){
    int exists = 0;
    if(numSize == 0){               // with recursion we go through all numbers and search if there is some contact or no
        if(node->contacts == 0){
            node->contacts++;
            node->data = (char**)realloc(node->data, node->contacts * sizeof(node->data[0]));   // list of all contacts with same number
            node->data[0] = NULL;
            node->data[node->contacts - 1] = (char*)realloc(node->data[(node->contacts) - 1], (fixedNumSize+2+nameSize) * sizeof(node->data[(node->contacts) - 1][0]));
            for(int i = 0; i < fixedNumSize; i++){
                node->data[node->contacts - 1][i] = number[i];
            }
            node->data[node->contacts - 1][fixedNumSize] = ' ';
            for(int j = 0; j < nameSize; j++){
                node->data[node->contacts - 1][fixedNumSize + 1 + j] = name[j];
            }
            node->data[node->contacts - 1][fixedNumSize + 1 + nameSize] = '\0';
            return 1;
        } else {
            for(int i = 0; i < node->contacts; i++){
                int length = strlen(node->data[i]);
                if(length == (nameSize+fixedNumSize+1)){    //we wanna to save entire line with mobile number and name
                    for(int j = 0; j < fixedNumSize; j++){
                        if(node->data[i][j] != number[j]){
                            exists = 0;
                            break;
                        }
                        exists = 1;
                    }
                    if(!exists){ continue;}
                    for(int k = 0; k < nameSize; k++){
                        if(node->data[i][k + fixedNumSize + 1] != name[k]){
                            exists = 0;
                            break;
                        }
                        exists = 1;
                    }
                    if(!exists) {continue;}
                    if(exists) {break;}
                }
            }
            if(!exists){
                node->contacts++;
                node->data = (char**)realloc(node->data, node->contacts * sizeof(node->data[0]));
                node->data[node->contacts-1] = NULL;
                node->data[node->contacts - 1] = (char*)realloc(node->data[(node->contacts) - 1], (fixedNumSize+2+nameSize) * sizeof(node->data[(node->contacts) - 1][0]));
                for(int i = 0; i < fixedNumSize; i++){
                    node->data[node->contacts - 1][i] = number[i];
                }
                node->data[node->contacts - 1][fixedNumSize] = ' ';
                for(int j = 0; j < nameSize; j++){
                    node->data[node->contacts - 1][fixedNumSize + 1 + j] = name[j];
                }
                node->data[node->contacts - 1][fixedNumSize + 1 + nameSize] = '\0';
                return 1;
            }
            return 0;
        }
        return 1;
    }
    int i = number[fixedNumSize - numSize] - '0';   //save our datas into a tree with our mobile number
    if(node->nodes[i] == 0){
        node->nodes[i] = (struct Tree*)calloc(1, sizeof(struct Tree));      //if there is no new node, create it
    }
    return addNumber(node->nodes[i], number, name, numSize - 1, nameSize, fixedNumSize);
}

/**
 * This function adds mobile number and username T9 to our tree structure. If result is 1, it was successfully added. Either it failed.
 * 
 * @param node Root tree
 * @param number Mobile number
 * @param name User name
 * @param numericName Username converted in T9
 * @param numSize Mobile number or its part length
 * @param nameSize Name or its part length
 * @param fixedNumSize Entire mobile number length
 * @param fixedNameSize Entire name length
 * @result  Returns if operation was successful or not.
*/
int addNameOld(struct Tree* node, char* number, char* name, char* numericName, int numSize, int nameSize, int fixedNumSize, int fixedNameSize){
    int exists = 0;
    if(nameSize == 0){
        if(node->contacts == 0){
            node->contacts++;
            node->data = (char**)realloc(node->data, node->contacts * sizeof(node->data[0]));
            node->data[0] = NULL;
            node->data[node->contacts - 1] = (char*)realloc(node->data[(node->contacts) - 1], (fixedNumSize+2+fixedNameSize) * sizeof(node->data[(node->contacts) - 1][0]));
            for(int i = 0; i < fixedNumSize; i++){
                node->data[node->contacts - 1][i] = number[i];
            }
            node->data[node->contacts - 1][fixedNumSize] = ' ';
            for(int j = 0; j < fixedNameSize; j++){
                node->data[node->contacts - 1][fixedNumSize + 1 + j] = name[j];
            }
            node->data[node->contacts - 1][fixedNumSize + 1 + fixedNameSize] = '\0';
            return 1;
        } else {
            for(int i = 0; i < node->contacts; i++){
                int length = strlen(node->data[i]);
                if(length == (fixedNameSize+fixedNumSize+1)){
                    for(int j = 0; j < fixedNumSize; j++){
                        if(node->data[i][j] != number[j]){
                            exists = 0;
                            break;
                        }
                        exists = 1;
                    }
                    if(!exists){ continue;}
                    for(int k = 0; k < fixedNameSize; k++){
                        if(node->data[i][k + fixedNumSize + 1] != name[k]){
                            exists = 0;
                            break;
                        }
                        exists = 1;
                    }
                    if(!exists) {continue;}
                    if(exists) {break;}
                }
            }
            if(!exists){
                node->contacts++;
                node->data = (char**)realloc(node->data, node->contacts * sizeof(node->data[0]));
                node->data[node->contacts-1] = NULL;
                node->data[node->contacts - 1] = (char*)realloc(node->data[(node->contacts) - 1], (fixedNumSize+2+fixedNameSize) * sizeof(node->data[(node->contacts) - 1][0]));
                for(int i = 0; i < fixedNumSize; i++){
                    node->data[node->contacts - 1][i] = number[i];
                }
                node->data[node->contacts - 1][fixedNumSize] = ' ';
                for(int j = 0; j < fixedNameSize; j++){
                    node->data[node->contacts - 1][fixedNumSize + 1 + j] = name[j];
                }
                node->data[node->contacts - 1][fixedNumSize + 1 + fixedNameSize] = '\0';
                return 1;
            }
            return 0;
        }
        return 1;
    }
    int i = numericName[fixedNameSize - nameSize] - '0';    //The only difference there is that we save only T9 name, not number
    if(node->nodes[i] == 0){
        node->nodes[i] = (struct Tree*)calloc(1, sizeof(struct Tree));
    }
    return addName(node->nodes[i], number, name, numericName, numSize, nameSize - 1, fixedNumSize, fixedNameSize);
}

/**
 * We are selecting there certain node with specific parameters.
 * 
 * @param node Root tree
 * @param query Query input (? query)
 * @param length Query length or its part in recursion
 * @param fixedLength = Query full length
*/
void collectGroup(struct Tree* node, char* query, int length, int fixedLength){
    for(int i = 0; i < SONS; i++){
        if(node->nodes[i] != NULL){
            collectGroup(node->nodes[i], query, length, fixedLength);
        } 
    }
    for(int i = 0; i < node->contacts; i++){
        int exists = 0;
        int length1 = strlen(node->data[i]);
        for(int j = 0; j < Found; j++){
            int length2 = strlen(Pool[j]);
            if(length1 == length2){     // check if our data are already in pool
                exists = 1;
                for(int k = 0; k < length1; k++){
                    if(node->data[i][k] != Pool[j][k]){     // we are also checking lines, not entire list
                        exists = 0;
                        break;
                    }
                }
            } else { exists = 0;}
            if(exists) break;
        }
        if(!exists){
            if (Found == bestMaximum){
			    bestMaximum *= 2;
			    Pool = (char**)realloc(Pool, bestMaximum * sizeof(Pool[0]));
		    }
            Pool[Found] = node->data[i];
            Found++;
        }
    }
}

/**
 * This function searches through all possible nodes.
 * 
 * @param node Root tree
 * @param query Query input (? query)
 * @param length Query length or its part in recursion
 * @param fixedLength = Query full length
*/
void search(struct Tree* node, char* query, int length, int fixedLength){
    while(length--){
        if(node->nodes[query[fixedLength - length - 1] - '0'] == NULL){
            return; //return if there are no subnodes in tree, so it will be always 0;
        }
        node = node->nodes[query[fixedLength - length - 1] - '0'];      //go into new subnode
    }
    collectGroup(node, query, length, fixedLength);
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
            int success = addNumber(root, number, name, numIndex, nameSize, numIndex);
            addName(root, number, name, T9, numIndex, nameSize, numIndex, nameSize);
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
        search(root, query, numIndex, numIndex);
        //printTree(root, 1);
        if(Found <= 10){
            for(int i = 0; i < Found; i++){
                int length = strlen(Pool[i]);
                for(int j = 0; j < length; j++){
                    printf("%c",Pool[i][j]);
                }
                printf("\n");
            }
        }
        printf("Celkem: %i\n", Found);
        bestMaximum = 10;
        Found = 0;
        Pool = (char **)realloc(Pool, bestMaximum * sizeof(Pool[0]));
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
    root = (struct Tree*)calloc(1, sizeof(struct Tree));
    Pool = (char **)malloc(bestMaximum * sizeof(Pool[0]));
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
                clearTree(root);
                return 0;
            }
            printf("Nespravny vstup.\n");
        }
    }
    if(feof(stdin)){
        free(Pool);
        clearTree(root);
        return 0;
    }
    printf("Nespravny vstup.\n");
    return 0;
}